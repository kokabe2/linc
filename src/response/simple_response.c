// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "simple_response.h"

#include <stddef.h>

#include "bleu/v1/heap.h"

typedef struct {
  ResponseInterfaceStruct impl;
  int status_code;
} SimpleResponseStruct, *SimpleResponse;

static void Delete(Response* self) { heap->Delete((void**)self); }

static int GetStatusCode(Response self) { return ((SimpleResponse)self)->status_code; }

static const void* GetBody(Response self) { return NULL; }

static Response New(int status_code) {
  SimpleResponse self = heap->New(sizeof(SimpleResponseStruct));
  self->impl.Delete = Delete;
  self->impl.GetStatusCode = GetStatusCode;
  self->impl.GetBody = GetBody;
  self->status_code = status_code;
  return (Response)self;
}

static const SimpleResponseMethodStruct kTheMethod = {
    .New = New,
};

const SimpleResponseMethod simpleResponse = &kTheMethod;
