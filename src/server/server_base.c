// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "server/server_base.h"

#include "bleu/v1/heap.h"
#include "phttp_status_code.h"
#include "server/server_base_protected.h"

static void Delete(Server* self) {
  Router router = ((ServerBase)*self)->router;
  router->Delete(&router);
  heap->Delete((void**)self);
}

static RuntimeError ListenAndServe(Server self) { return NULL; }

static void Super(ServerBase self, const char* domain, Router router) {
  self->impl.Delete = Delete;
  self->impl.ListenAndServe = ListenAndServe;
  self->domain = strings->New(domain);
  self->router = router;
}

static const ServerBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const ServerBaseProtectedMethod _serverBase = &kProtectedMethod;

static const char* GetDomain(Server self) { return ((ServerBase)self)->domain; }

static Router GetRouter(Server self) { return ((ServerBase)self)->router; }

static void SendResponse(Responder r, int status_code) {
  r->SetStatusCode(r, status_code);
  r->Send(r);
}

static void Do(Server self, Request req, Responder r) {
  const char* method = req->GetMethod(req);
  if (strings->Equals("POST", method))
    routerBase->DoPost(((ServerBase)self)->router, req, r);
  else if (strings->Equals("PUT", method))
    routerBase->DoPut(((ServerBase)self)->router, req, r);
  else if (strings->Equals("GET", method))
    routerBase->DoGet(((ServerBase)self)->router, req, r);
  else if (strings->Equals("DELETE", method))
    routerBase->DoDelete(((ServerBase)self)->router, req, r);
  else
    SendResponse(r, kStatusNotImplemented);
}

static const ServerBaseMethodStruct kTheMethod = {
    .GetDomain = GetDomain,
    .GetRouter = GetRouter,
    .Do = Do,
};

const ServerBaseMethod serverBase = &kTheMethod;
