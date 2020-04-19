// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_SERVER_SERVER_BASE_PROTECTED_H_
#define SRC_SERVER_SERVER_BASE_PROTECTED_H_

#include "bleu/v1/str.h"
#include "router.h"
#include "server_base.h"

typedef struct {
  ServerInterfaceStruct impl;
  Strings domain;
  Router router;
} ServerBaseStruct, *ServerBase;
typedef struct {
  void (*Super)(ServerBase self, const char* domain, Router router);  //
} ServerBaseProtectedMethodStruct;
typedef const ServerBaseProtectedMethodStruct* ServerBaseProtectedMethod;

extern const ServerBaseProtectedMethod _serverBase;

#endif  // SRC_SERVER_SERVER_BASE_PROTECTED_H_
