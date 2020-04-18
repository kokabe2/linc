// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_PHTTP_H_
#define V1_PHTTP_H_

#include "bleu/v1/runtime_error.h"
#include "handler.h"
#include "response.h"

typedef struct {
  const int StatusContinue;
  const int StatusSwitchingProtocols;
  const int StatusProcessing;
  const int StatusEarlyHints;

  const int StatusOK;
  const int StatusCreated;
  const int StatusAccepted;
  const int StatusNonAuthoritativeInfo;
  const int StatusNoContent;
  const int StatusResetContent;
  const int StatusPartialContent;
  const int StatusMultiStatus;
  const int StatusAlreadyReported;
  const int StatusIMUsed;

  const int StatusMultipleChoices;
  const int StatusMovedPermanently;
  const int StatusFound;
  const int StatusSeeOther;
  const int StatusNotModified;
  const int StatusUseProxy;
  const int StatusTemporaryRedirect;
  const int StatusPermanentRedirect;

  const int StatusBadRequest;
  const int StatusUnauthorized;
  const int StatusPaymentRequired;
  const int StatusForbidden;
  const int StatusNotFound;
  const int StatusMethodNotAllowed;
  const int StatusNotAcceptable;
  const int StatusProxyAuthRequired;
  const int StatusRequestTimeout;
  const int StatusConflict;
  const int StatusGone;
  const int StatusLengthRequired;
  const int StatusPreconditionFailed;
  const int StatusRequestEntityTooLarge;
  const int StatusRequestURITooLong;
  const int StatusUnsupportedMediaType;
  const int StatusRequestedRangeNotSatisfiable;
  const int StatusExpectationFailed;
  const int StatusTeapot;
  const int StatusMisdirectedRequest;
  const int StatusUnprocessableEntity;
  const int StatusLocked;
  const int StatusFailedDependency;
  const int StatusTooEarly;
  const int StatusUpgradeRequired;
  const int StatusPreconditionRequired;
  const int StatusTooManyRequests;
  const int StatusRequestHeaderFieldsTooLarge;
  const int StatusUnavailableForLegalReasons;

  const int StatusInternalServerError;
  const int StatusNotImplemented;
  const int StatusBadGateway;
  const int StatusServiceUnavailable;
  const int StatusGatewayTimeout;
  const int StatusHTTPVersionNotSupported;
  const int StatusVariantAlsoNegotiates;
  const int StatusInsufficientStorage;
  const int StatusLoopDetected;
  const int StatusNotExtended;
  const int StatusNetworkAuthenticationRequired;

  void (*Handle)(const char* uri, PhttpHandlerDelegate handler);
  RuntimeError (*ListenAndServe)(const char* addr, void* reserved);
  Response (*POST)(const char* uri, const void* body);
  Response (*PUT)(const char* uri, const void* body);
  Response (*GET)(const char* uri);
  Response (*DELETE)(const char* uri);
} PhttpMethodStruct;
typedef const PhttpMethodStruct* PhttpMethod;

extern const PhttpMethod phttp;

#endif  // V1_PHTTP_H_
