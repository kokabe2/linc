// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response/default_response.h"

#include "bleu/v1/heap.h"
#include "response/response_base_protected.h"

static Response New(void) {
  ResponseBase self = heap->New(sizeof(ResponseBaseStruct));
  _responseBase->Super(self);
  return (Response)self;
}

static const DefaultResponseMethodStruct kTheMethod = {
    .New = New,
};

const DefaultResponseMethod defaultResponse = &kTheMethod;
