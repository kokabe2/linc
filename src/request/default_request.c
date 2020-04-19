// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "request/default_request.h"

#include "bleu/v1/heap.h"
#include "request/request_base_protected.h"

static Request New(const char* method, const char* uri, const char* pattern, const void* body) {
  RequestBase self = heap->New(sizeof(RequestBaseStruct));
  _requestBase->Super(self, method, uri, pattern);
  requestBase->SetBody((Request)self, body);
  return (Request)self;
}

static const DefaultRequestMethodStruct kTheMethod = {
    .New = New,
};

const DefaultRequestMethod defaultRequest = &kTheMethod;
