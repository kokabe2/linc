// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "responder/default_responder.h"

#include "bleu/v1/heap.h"
#include "responder/responder_base_protected.h"
#include "response/response_base.h"

static Responder New(Response res) {
  ResponderBase self = heap->New(sizeof(ResponderBaseStruct));
  _responderBase->Super(self, res);
  return (Responder)self;
}

static const DefaultResponderMethodStruct kTheMethod = {
    .New = New,
};

const DefaultResponderMethod defaultResponder = &kTheMethod;
