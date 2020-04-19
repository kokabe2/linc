// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "default_request.h"

#include <stdlib.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/path.h"

typedef struct {
  RequestInterfaceStruct impl;
  Strings requested;
  Strings method;
  Path uri;
  Path pattern;
  const void* body;
} DefaultRequestStruct, *DefaultRequest;

static void Delete(Request* base) {
  DefaultRequest self = (DefaultRequest)*base;
  strings->Delete(&self->requested);
  strings->Delete(&self->method);
  path->Delete(&self->uri);
  path->Delete(&self->pattern);
  heap->Delete((void**)base);
}

static const char* GetUri(Request self) { return ((DefaultRequest)self)->requested; }

static const char* GetDomain(Request self) { return path->Directory(((DefaultRequest)self)->uri, 0); }

static const char* GetPath(Request base) {
  DefaultRequest self = (DefaultRequest)base;
  int index = strings->Index(self->requested, "/");
  return &self->requested[index];
}

static const char* GetMethod(Request self) { return ((DefaultRequest)self)->method; }

static const void* GetBody(Request self) { return ((DefaultRequest)self)->body; }

inline static bool IsNamedParameter(Strings s) { return s[0] == ':'; }

static const char* GetParam(Request base, const char* key) {
  DefaultRequest self = (DefaultRequest)base;
  const char* value = NULL;
  for (int i = 2; i < path->Count(self->uri) && value == NULL; ++i) {
    const char* s = path->Directory(self->pattern, i);
    if (IsNamedParameter(s) && strings->Equals(key, &s[1])) value = path->Directory(self->uri, i);
  }
  return value;
}

static int ToInt(const char* param) { return atoi(param); }

inline static void InstallInterface(DefaultRequest self) {
  self->impl.Delete = Delete;
  self->impl.GetUri = GetUri;
  self->impl.GetDomain = GetDomain;
  self->impl.GetPath = GetPath;
  self->impl.GetMethod = GetMethod;
  self->impl.GetBody = GetBody;
  self->impl.GetParam = GetParam;
  self->impl.ToInt = ToInt;
}

static Request New(const char* method, const char* uri, const char* pattern) {
  DefaultRequest self = heap->New(sizeof(DefaultRequestStruct));
  InstallInterface(self);
  self->method = strings->New(method);
  self->requested = strings->New(uri);
  self->uri = path->New(uri);
  self->pattern = path->New(pattern);
  return (Request)self;
}

static void SetBody(Request self, const void* body) { ((DefaultRequest)self)->body = body; }

static const DefaultRequestMethodStruct kTheMethod = {
    .New = New,
    .SetBody = SetBody,
};

const DefaultRequestMethod defaultRequest = &kTheMethod;
