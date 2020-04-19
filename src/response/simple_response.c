// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response/simple_response.h"

#include "bleu/v1/heap.h"
#include "response/response_base_protected.h"

static Response New(int status_code) {
  ResponseBase self = heap->New(sizeof(ResponseBaseStruct));
  _responseBase->Super(self);
  responseBase->SetStatusCode((Response)self, status_code);
  return (Response)self;
}

static const SimpleResponseMethodStruct kTheMethod = {
    .New = New,
};

const SimpleResponseMethod simpleResponse = &kTheMethod;
