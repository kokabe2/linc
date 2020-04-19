// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "http_method_request.h"

#include "bleu/v1/heap.h"
#include "request/request_base_protected.h"

static Request New(const char* method, const char* uri, const void* body) {
  RequestBase self = heap->New(sizeof(RequestBaseStruct));
  _requestBase->Super(self, method, uri);
  requestBase->SetBody((Request)self, body);
  return (Request)self;
}

static const HttpMethodRequestMethodStruct kTheMethod = {
    .New = New,
};

const HttpMethodRequestMethod httpMethodRequest = &kTheMethod;
