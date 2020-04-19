// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "server/server_base.h"

#include "bleu/v1/heap.h"
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

static void DoPost(Server self, Request req, Responder r) { routerBase->DoPost(((ServerBase)self)->router, req, r); }

static void DoPut(Server self, Request req, Responder r) { routerBase->DoPut(((ServerBase)self)->router, req, r); }

static void DoGet(Server self, Request req, Responder r) { routerBase->DoGet(((ServerBase)self)->router, req, r); }

static void DoDelete(Server self, Request req, Responder r) {
  routerBase->DoDelete(((ServerBase)self)->router, req, r);
}

static const ServerBaseMethodStruct kTheMethod = {
    .GetDomain = GetDomain,
    .GetRouter = GetRouter,
    .DoPost = DoPost,
    .DoPut = DoPut,
    .DoGet = DoGet,
    .DoDelete = DoDelete,
};

const ServerBaseMethod serverBase = &kTheMethod;
