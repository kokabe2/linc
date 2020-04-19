// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response/default_response.h"

#include "bleu/v1/heap.h"

static Response New(void) {
  Response self = responseBase->New();
  return self;
}

static const DefaultResponseMethodStruct kTheMethod = {
    .New = New,
};

const DefaultResponseMethod defaultResponse = &kTheMethod;
