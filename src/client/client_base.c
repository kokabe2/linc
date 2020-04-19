// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "bleu/v1/heap.h"
#include "client/client_base_protected.h"
#include "pdns.h"
#include "phttp_status_code.h"

inline static void Delete(Client* self) { heap->Delete((void**)self); }

inline static void SendResponse(Responder r, int status_code) {
  r->SetStatusCode(r, status_code);
  r->Send(r);
}

static void Do(Client base, Request req) {
  ClientBase self = (ClientBase)base;
  Server s = pdns->Retrieve(req->GetDomain(req));
  if (s != NULL)
    serverBase->Do(s, req, self->responder);
  else
    SendResponse(self->responder, kStatusNotFound);
}

static void Super(ClientBase self, Responder r) {
  self->impl.Delete = Delete;
  self->impl.Do = Do;
  self->responder = r;
}

static const ClientBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const ClientBaseProtectedMethod _clientBase = &kProtectedMethod;
