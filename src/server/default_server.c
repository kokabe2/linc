// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "default_server.h"

#include "bleu/v1/heap.h"
#include "server/server_base_protected.h"

static Server New(const char* domain, Router router) {
  ServerBase self = heap->New(sizeof(ServerBaseStruct));
  _serverBase->Super(self, domain, router);
  return (Server)self;
}

static const DefaultServerMethodStruct kTheMethod = {
    .New = New,
};

const DefaultServerMethod defaultServer = &kTheMethod;
