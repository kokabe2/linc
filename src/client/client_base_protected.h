// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_CLIENT_CLIENT_BASE_PROTECTED_H_
#define SRC_CLIENT_CLIENT_BASE_PROTECTED_H_

#include "client.h"
#include "responder.h"

typedef struct {
  ClientInterfaceStruct impl;
  Responder responder;
} ClientBaseStruct, *ClientBase;
typedef struct {
  void (*Super)(ClientBase self, Responder r);  //
} ClientBaseProtectedMethodStruct;
typedef const ClientBaseProtectedMethodStruct* ClientBaseProtectedMethod;

extern const ClientBaseProtectedMethod _clientBase;

#endif  // SRC_CLIENT_CLIENT_BASE_PROTECTED_H_
