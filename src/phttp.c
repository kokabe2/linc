// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "phttp.h"

#include <string.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/list.h"
#include "bleu/v1/path.h"
#include "request/default_request.h"
#include "responder/default_responder.h"
#include "response/default_response.h"
#include "response/simple_response.h"

typedef struct {
  Strings uri;
  PhttpHandlerDelegate handler;
} HandlerNodeStruct, *HandlerNode;
typedef struct PhttpStruct {
  List handlers;
} PhttpStruct, *Phttp;

static Phttp INSTANCE = NULL;

inline static bool IsNamedParameter(Strings s) { return s[0] == ':'; }

inline static int CompareResource(Path pattern, Path requested) {
  int result = path->Count(pattern) - path->Count(requested);
  for (int i = 0; i < path->Count(pattern) && result == 0; ++i) {
    const char* s1 = path->Directory(pattern, i);
    const char* s2 = path->Directory(requested, i);
    if (!IsNamedParameter(s1)) result = strcmp(s1, s2);
  }
  return result;
}

static int HandlerComparer(const void* node, const void* uri) {
  Path pattern = path->New(((HandlerNode)node)->uri);
  Path requested = path->New(uri);
  int result = CompareResource(pattern, requested);
  path->Delete(&pattern);
  path->Delete(&requested);
  return result;
}

inline static Phttp New(void) {
  Phttp self = heap->New(sizeof(PhttpStruct));
  self->handlers = list->New();
  list->SetItemComparer(self->handlers, HandlerComparer);
  return self;
}

inline static Phttp GetInstance(void) {
  if (INSTANCE == NULL) INSTANCE = New();
  return INSTANCE;
}

inline static bool Exists(const char* uri) {
  Phttp self = GetInstance();
  return list->Find(self->handlers, uri) != NULL;
}

inline static HandlerNode NewHandlerNode(const char* uri, PhttpHandlerDelegate handler) {
  HandlerNode self = heap->New(sizeof(HandlerNodeStruct));
  self->uri = strings->New(uri);
  self->handler = handler;
  return self;
}

inline static void AddHandler(const char* uri, PhttpHandlerDelegate handler) {
  Phttp self = GetInstance();
  HandlerNode node = NewHandlerNode(uri, handler);
  list->Add(self->handlers, node);
}

static void Handle(const char* uri, PhttpHandlerDelegate handler) {
  if (!Exists(uri)) AddHandler(uri, handler);
}

static RuntimeError ListenAndServe(const char* addr, void* reserved) { return NULL; }

inline static const char* GetPattern(HandlerNode node) {
  int index = strings->Index(node->uri, "/");
  return &node->uri[index];
}

inline static Response HttpMethodTemplate(const char* method, const char* uri, const void* body) {
  Phttp self = GetInstance();
  HandlerNode node = list->Find(self->handlers, uri);
  if (node != NULL) {
    Request req = defaultRequest->New(method, uri, GetPattern(node), body);
    Response res = defaultResponse->New();
    Responder r = defaultResponder->New(res);
    node->handler(req, r);
    req->Delete(&req);
    return res;
  } else {
    return simpleResponse->New(kStatusNotFound);
  }
}

static Response POST(const char* uri, const void* body) { return HttpMethodTemplate("POST", uri, body); }

static Response PUT(const char* uri, const void* body) { return HttpMethodTemplate("PUT", uri, body); }

static Response GET(const char* uri) { return HttpMethodTemplate("GET", uri, NULL); }

static Response DELETE(const char* uri) { return HttpMethodTemplate("DELETE", uri, NULL); }

static const PhttpMethodStruct kTheMethod = {
    .Handle = Handle,
    .ListenAndServe = ListenAndServe,
    .POST = POST,
    .PUT = PUT,
    .GET = GET,
    .DELETE = DELETE,
};

const PhttpMethod phttp = &kTheMethod;
