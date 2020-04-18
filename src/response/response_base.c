// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response_base.h"

#include "bleu/v1/heap.h"

typedef struct {
  ResponseInterfaceStruct impl;
  int status_code;
  void* body;
  DeleteDelegate Delete;
} ResponseBaseStruct, *ResponseBase;

static void Delete(Response* base) {
  ResponseBase self = (ResponseBase)*base;
  self->Delete(&self->body);
  heap->Delete((void**)base);
}

static int GetStatusCode(Response self) { return ((ResponseBase)self)->status_code; }

static const void* GetBody(Response self) { return ((ResponseBase)self)->body; }

static void DummyDeleter(void** body) {}

static Response New(void) {
  ResponseBase self = heap->New(sizeof(ResponseBaseStruct));
  self->impl.Delete = Delete;
  self->impl.GetStatusCode = GetStatusCode;
  self->impl.GetBody = GetBody;
  self->status_code = 200;
  self->Delete = DummyDeleter;
  return (Response)self;
}

static void SetStatusCode(Response self, int status_code) { ((ResponseBase)self)->status_code = status_code; }

static void SetBody(Response self, void* body) { ((ResponseBase)self)->body = body; }

static void SetBodyDeleter(Response self, DeleteDelegate delegate) { ((ResponseBase)self)->Delete = delegate; }

static const ResponseBaseMethodStruct kTheMethod = {
    .New = New,
    .SetStatusCode = SetStatusCode,
    .SetBody = SetBody,
    .SetBodyDeleter = SetBodyDeleter,
};

const ResponseBaseMethod responseBase = &kTheMethod;
