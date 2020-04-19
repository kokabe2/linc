// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "phttp.h"

#include <string.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/list.h"
#include "bleu/v1/path.h"
#include "http_method_request.h"
#include "responder/default_responder.h"
#include "response/default_response.h"
#include "response/simple_response.h"
#include "router/router_base.h"
#include "util/name_resolution_helper.h"

inline static const char* GetPattern(const char* uri) { return &uri[strings->Index(uri, "/")]; }

static void Handle(const char* uri, PhttpHandlerDelegate handler) {
  const char* pattern = GetPattern(uri);
  Server s = nameResolutionHelper->RetrieveOrNewIfNotFound(uri);
  Router r = serverBase->GetRouter(s);
  r->POST(r, pattern, handler);
  r->PUT(r, pattern, handler);
  r->GET(r, pattern, handler);
  r->DELETE(r, pattern, handler);
}

static RuntimeError ListenAndServe(const char* addr, void* reserved) { return NULL; }

inline static Response HttpMethodTemplate(const char* method, const char* uri, const void* body) {
  Server s = nameResolutionHelper->Retrieve(uri);
  if (s != NULL) {
    Request req = httpMethodRequest->New(method, uri, body);
    Response res = defaultResponse->New();
    Responder r = defaultResponder->New(res);
    serverBase->Do(s, req, r);
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
