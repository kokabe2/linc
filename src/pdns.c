// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "pdns.h"

#include <string.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/list.h"

typedef struct PdnsStruct {
  List servers;
} PdnsStruct, *Pdns;

static Pdns INSTANCE = NULL;

static int ServerComparer(const void* server, const void* domain) {
  return strcmp(serverBase->GetDomain((Server)server), domain);
}

inline static Pdns New(void) {
  Pdns self = heap->New(sizeof(PdnsStruct));
  self->servers = list->New();
  list->SetItemComparer(self->servers, ServerComparer);
  return self;
}

inline static Pdns GetInstance(void) {
  if (INSTANCE == NULL) INSTANCE = New();
  return INSTANCE;
}

static void Register(Server server) {
  Pdns self = GetInstance();
  list->Add(self->servers, server);
}

static Server Retrieve(const char* domain) {
  Pdns self = GetInstance();
  return list->Find(self->servers, domain);
}

static const PdnsMethodStruct kTheMethod = {
    .Register = Register,
    .Retrieve = Retrieve,
};

const PdnsMethod pdns = &kTheMethod;
