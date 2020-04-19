// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "request/request_base.h"

#include <stdlib.h>

#include "bleu/v1/heap.h"
#include "request/request_base_protected.h"

static void Delete(Request* base) {
  RequestBase self = (RequestBase)*base;
  strings->Delete(&self->requested);
  strings->Delete(&self->method);
  path->Delete(&self->uri);
  path->Delete(&self->pattern);
  heap->Delete((void**)base);
}

static const char* GetUri(Request self) { return ((RequestBase)self)->requested; }

static const char* GetDomain(Request self) { return path->Directory(((RequestBase)self)->uri, 0); }

static const char* GetPath(Request base) {
  RequestBase self = (RequestBase)base;
  int index = strings->Index(self->requested, "/");
  return &self->requested[index];
}

static const char* GetMethod(Request self) { return ((RequestBase)self)->method; }

static const void* GetBody(Request self) { return ((RequestBase)self)->body; }

inline static bool IsNamedParameter(Strings s) { return s[0] == ':'; }

static const char* GetParam(Request base, const char* key) {
  RequestBase self = (RequestBase)base;
  const char* value = NULL;
  for (int i = 2; i < path->Count(self->uri) && value == NULL; ++i) {
    const char* s = path->Directory(self->pattern, i);
    if (IsNamedParameter(s) && strings->Equals(key, &s[1])) value = path->Directory(self->uri, i);
  }
  return value;
}

static int ToInt(const char* param) { return atoi(param); }

inline static void InstallInterface(RequestBase self) {
  self->impl.Delete = Delete;
  self->impl.GetUri = GetUri;
  self->impl.GetDomain = GetDomain;
  self->impl.GetPath = GetPath;
  self->impl.GetMethod = GetMethod;
  self->impl.GetBody = GetBody;
  self->impl.GetParam = GetParam;
  self->impl.ToInt = ToInt;
}

static void Super(RequestBase self, const char* method, const char* uri, const char* pattern) {
  InstallInterface(self);
  self->method = strings->New(method);
  self->requested = strings->New(uri);
  self->uri = path->New(uri);
  self->pattern = path->New(pattern);
}

static const RequestBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const RequestBaseProtectedMethod _requestBase = &kProtectedMethod;

static void SetBody(Request self, const void* body) { ((RequestBase)self)->body = body; }

static const RequestBaseMethodStruct kTheMethod = {
    .SetBody = SetBody,
};

const RequestBaseMethod requestBase = &kTheMethod;
