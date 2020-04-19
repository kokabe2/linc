// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONSE_RESPONSE_BASE_PROTECTED_H_
#define SRC_RESPONSE_RESPONSE_BASE_PROTECTED_H_

#include "response/response_base.h"

typedef struct {
  ResponseInterfaceStruct impl;
  int status_code;
  void* body;
  DeleteDelegate DeleteBody;
} ResponseBaseStruct, *ResponseBase;
typedef struct {
  void (*Super)(ResponseBase self);  //
} ResponseBaseProtectedMethodStruct;
typedef const ResponseBaseProtectedMethodStruct* ResponseBaseProtectedMethod;

extern const ResponseBaseProtectedMethod _responseBase;

#endif  // SRC_RESPONSE_RESPONSE_BASE_PROTECTED_H_
