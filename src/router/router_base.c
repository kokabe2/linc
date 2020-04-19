// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "router/router_base.h"

#include <string.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/path.h"
#include "phttp_status_code.h"
#include "request/request_base.h"
#include "router/router_base_protected.h"

#define COUNTOF(x) (sizeof(x) / sizeof(x[0]))

enum HandlersIndex {
  kPost = 0,
  kPut = 1,
  kGet = 2,
  kDelete = 3,
};

typedef struct {
  Strings str_pattern;
  Path path_pattern;
  PhttpHandlerDelegate handler;
} HandlerNodeStruct, *HandlerNode;

static void Delete(Router* base) {
  RouterBase self = (RouterBase)*base;
  for (int i = 0; i < COUNTOF(self->handlers); ++i) list->Delete(&self->handlers[i]);
  heap->Delete((void**)base);
}

inline static bool Exists(List handlers, const char* pattern) { return list->Find(handlers, pattern) != NULL; }

inline static HandlerNode NewHandlerNode(const char* pattern, PhttpHandlerDelegate handler) {
  HandlerNode self = heap->New(sizeof(HandlerNodeStruct));
  self->str_pattern = strings->New(pattern);
  self->path_pattern = path->New(pattern);
  self->handler = handler;
  return self;
}

inline static void AddHandler(List handlers, const char* pattern, PhttpHandlerDelegate handler) {
  HandlerNode node = NewHandlerNode(pattern, handler);
  list->Add(handlers, node);
}

static void POST(Router self, const char* pattern, PhttpHandlerDelegate handler) {
  List handlers = ((RouterBase)self)->handlers[kPost];
  if (!Exists(handlers, pattern)) AddHandler(handlers, pattern, handler);
}

static void PUT(Router self, const char* pattern, PhttpHandlerDelegate handler) {
  List handlers = ((RouterBase)self)->handlers[kPut];
  if (!Exists(handlers, pattern)) AddHandler(handlers, pattern, handler);
}

static void GET(Router self, const char* pattern, PhttpHandlerDelegate handler) {
  List handlers = ((RouterBase)self)->handlers[kGet];
  if (!Exists(handlers, pattern)) AddHandler(handlers, pattern, handler);
}

static void DELETE(Router self, const char* pattern, PhttpHandlerDelegate handler) {
  List handlers = ((RouterBase)self)->handlers[kDelete];
  if (!Exists(handlers, pattern)) AddHandler(handlers, pattern, handler);
}

inline static bool IsNamedParameter(Strings s) { return s[0] == ':'; }

inline static int CompareResource(Path reference, Path requested) {
  int result = path->Count(reference) - path->Count(requested);
  for (int i = 0; i < path->Count(reference) && result == 0; ++i) {
    const char* s1 = path->Directory(reference, i);
    const char* s2 = path->Directory(requested, i);
    if (!IsNamedParameter(s1)) result = strcmp(s1, s2);
  }
  return result;
}

static int HandlerComparer(const void* node, const void* pattern) {
  Path requested = path->New(pattern);
  int result = CompareResource(((HandlerNode)node)->path_pattern, requested);
  path->Delete(&requested);
  return result;
}

static void HandlerDeleter(void** x) {
  HandlerNode self = (HandlerNode)*x;
  strings->Delete(&self->str_pattern);
  path->Delete(&self->path_pattern);
  heap->Delete(x);
}

static void Super(RouterBase self) {
  self->impl.Delete = Delete;
  self->impl.POST = POST;
  self->impl.PUT = PUT;
  self->impl.GET = GET;
  self->impl.DELETE = DELETE;
  for (int i = 0; i < COUNTOF(self->handlers); ++i) {
    self->handlers[i] = list->New();
    list->SetItemComparer(self->handlers[i], HandlerComparer);
    list->SetItemDeleter(self->handlers[i], HandlerDeleter);
  }
}

static const RouterBaseProtectedMethodStruct kProtectedMethod = {
    .Super = Super,
};

const RouterBaseProtectedMethod _routerBase = &kProtectedMethod;

inline static void Do(List handlers, Request req, Responder r) {
  HandlerNode node = list->Find(handlers, req->GetPath(req));
  if (node != NULL) {
    requestBase->SetPattern(req, node->str_pattern);
    node->handler(req, r);
  } else {
    r->SetStatusCode(r, kStatusNotFound);
    r->Send(r);
  }
  req->Delete(&req);
}

static void DoPost(Router self, Request req, Responder r) { Do(((RouterBase)self)->handlers[kPost], req, r); }

static void DoPut(Router self, Request req, Responder r) { Do(((RouterBase)self)->handlers[kPut], req, r); }

static void DoGet(Router self, Request req, Responder r) { Do(((RouterBase)self)->handlers[kGet], req, r); }

static void DoDelete(Router self, Request req, Responder r) { Do(((RouterBase)self)->handlers[kDelete], req, r); }

static const RouterBaseMethodStruct kTheMethod = {
    .DoPost = DoPost,
    .DoPut = DoPut,
    .DoGet = DoGet,
    .DoDelete = DoDelete,
};

const RouterBaseMethod routerBase = &kTheMethod;
