// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONDER_RESPONDER_BASE_PROTECTED_H_
#define SRC_RESPONDER_RESPONDER_BASE_PROTECTED_H_

#include "responder.h"
#include "response.h"

typedef struct {
  ResponderInterfaceStruct impl;
  Response res;
} ResponderBaseStruct, *ResponderBase;
typedef struct {
  void (*Super)(ResponderBase self, Response res);  //
} ResponderBaseProtectedMethodStruct;
typedef const ResponderBaseProtectedMethodStruct* ResponderBaseProtectedMethod;

extern const ResponderBaseProtectedMethod _responderBase;

#endif  // SRC_RESPONDER_RESPONDER_BASE_PROTECTED_H_
