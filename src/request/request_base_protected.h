// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_REQUEST_REQUEST_BASE_PROTECTED_H_
#define SRC_REQUEST_REQUEST_BASE_PROTECTED_H_

#include "bleu/v1/path.h"
#include "request/request_base.h"

typedef struct {
  RequestInterfaceStruct impl;
  Strings requested;
  Strings method;
  Path uri;
  Path pattern;
  const void* body;
} RequestBaseStruct, *RequestBase;
typedef struct {
  void (*Super)(RequestBase self, const char* method, const char* uri, const char* pattern);
} RequestBaseProtectedMethodStruct;
typedef const RequestBaseProtectedMethodStruct* RequestBaseProtectedMethod;

extern const RequestBaseProtectedMethod _requestBase;

#endif  // SRC_REQUEST_REQUEST_BASE_PROTECTED_H_
