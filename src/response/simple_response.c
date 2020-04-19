// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "response/simple_response.h"

#include "bleu/v1/heap.h"

static Response New(int status_code) {
  Response self = responseBase->New();
  responseBase->SetStatusCode(self, status_code);
  return self;
}

static const SimpleResponseMethodStruct kTheMethod = {
    .New = New,
};

const SimpleResponseMethod simpleResponse = &kTheMethod;
