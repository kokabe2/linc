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

inline static Response HttpMethodTemplate(const char* method, const char* uri, const void* body) {
  Phttp self = GetInstance();
  HandlerNode node = list->Find(self->handlers, uri);
  if (node != NULL) {
    Request req = defaultRequest->New(method, uri, node->uri);
    defaultRequest->SetBody(req, body);
    Response res = defaultResponse->New();
    Responder r = defaultResponder->New(res);
    node->handler(req, r);
    req->Delete(&req);
    return res;
  } else {
    return simpleResponse->New(phttp->StatusNotFound);
  }
}

static Response POST(const char* uri, const void* body) { return HttpMethodTemplate("POST", uri, body); }

static Response PUT(const char* uri, const void* body) { return HttpMethodTemplate("PUT", uri, body); }

static Response GET(const char* uri) { return HttpMethodTemplate("GET", uri, NULL); }

static Response DELETE(const char* uri) { return HttpMethodTemplate("DELETE", uri, NULL); }

static const PhttpMethodStruct kTheMethod = {
    .StatusContinue = 100,
    .StatusSwitchingProtocols = 101,
    .StatusProcessing = 102,
    .StatusEarlyHints = 103,
    .StatusOK = 200,
    .StatusCreated = 201,
    .StatusAccepted = 202,
    .StatusNonAuthoritativeInfo = 203,
    .StatusNoContent = 204,
    .StatusResetContent = 205,
    .StatusPartialContent = 206,
    .StatusMultiStatus = 207,
    .StatusAlreadyReported = 208,
    .StatusIMUsed = 226,
    .StatusMultipleChoices = 300,
    .StatusMovedPermanently = 301,
    .StatusFound = 302,
    .StatusSeeOther = 303,
    .StatusNotModified = 304,
    .StatusUseProxy = 305,
    .StatusTemporaryRedirect = 307,
    .StatusPermanentRedirect = 308,
    .StatusBadRequest = 400,
    .StatusUnauthorized = 401,
    .StatusPaymentRequired = 402,
    .StatusForbidden = 403,
    .StatusNotFound = 404,
    .StatusMethodNotAllowed = 405,
    .StatusNotAcceptable = 406,
    .StatusProxyAuthRequired = 407,
    .StatusRequestTimeout = 408,
    .StatusConflict = 409,
    .StatusGone = 410,
    .StatusLengthRequired = 411,
    .StatusPreconditionFailed = 412,
    .StatusRequestEntityTooLarge = 413,
    .StatusRequestURITooLong = 414,
    .StatusUnsupportedMediaType = 415,
    .StatusRequestedRangeNotSatisfiable = 416,
    .StatusExpectationFailed = 417,
    .StatusTeapot = 418,
    .StatusMisdirectedRequest = 421,
    .StatusUnprocessableEntity = 422,
    .StatusLocked = 423,
    .StatusFailedDependency = 424,
    .StatusTooEarly = 425,
    .StatusUpgradeRequired = 426,
    .StatusPreconditionRequired = 428,
    .StatusTooManyRequests = 429,
    .StatusRequestHeaderFieldsTooLarge = 431,
    .StatusUnavailableForLegalReasons = 451,
    .StatusInternalServerError = 500,
    .StatusNotImplemented = 501,
    .StatusBadGateway = 502,
    .StatusServiceUnavailable = 503,
    .StatusGatewayTimeout = 504,
    .StatusHTTPVersionNotSupported = 505,
    .StatusVariantAlsoNegotiates = 506,
    .StatusInsufficientStorage = 507,
    .StatusLoopDetected = 508,
    .StatusNotExtended = 510,
    .StatusNetworkAuthenticationRequired = 511,
    .Handle = Handle,
    .ListenAndServe = ListenAndServe,
    .POST = POST,
    .PUT = PUT,
    .GET = GET,
    .DELETE = DELETE,
};

const PhttpMethod phttp = &kTheMethod;
