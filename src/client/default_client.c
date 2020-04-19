// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "default_client.h"

#include "bleu/v1/heap.h"
#include "client/client_base_protected.h"

static Client New(Responder r) {
  ClientBase self = heap->New(sizeof(ClientBaseStruct));
  _clientBase->Super(self, r);
  return (Client)self;
}

static const DefaultClientMethodStruct kTheMethod = {
    .New = New,
};

const DefaultClientMethod defaultClient = &kTheMethod;
