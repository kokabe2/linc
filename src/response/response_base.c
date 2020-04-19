// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response/response_base.h"

#include "bleu/v1/heap.h"
#include "phttp_status_code.h"
#include "response/response_base_protected.h"

static void Delete(Response* base) {
  ResponseBase self = (ResponseBase)*base;
  self->DeleteBody(&self->body);
  heap->Delete((void**)base);
}

static int GetStatusCode(Response self) { return ((ResponseBase)self)->status_code; }

static const void* GetBody(Response self) { return ((ResponseBase)self)->body; }

static void DummyDeleter(void** body) {}

static void Super(ResponseBase self) {
  self->impl.Delete = Delete;
  self->impl.GetStatusCode = GetStatusCode;
  self->impl.GetBody = GetBody;
  self->status_code = kStatusOK;
  self->DeleteBody = DummyDeleter;
}

static const ResponseBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const ResponseBaseProtectedMethod _responseBase = &kProtectedMethod;

static void SetStatusCode(Response self, int status_code) { ((ResponseBase)self)->status_code = status_code; }

static void SetBody(Response self, void* body) { ((ResponseBase)self)->body = body; }

static void SetBodyDeleter(Response self, DeleteDelegate delegate) { ((ResponseBase)self)->DeleteBody = delegate; }

static const ResponseBaseMethodStruct kTheMethod = {
    .SetStatusCode = SetStatusCode,
    .SetBody = SetBody,
    .SetBodyDeleter = SetBodyDeleter,
};

const ResponseBaseMethod responseBase = &kTheMethod;
