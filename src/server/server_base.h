// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_SERVER_SERVER_BASE_H_
#define SRC_SERVER_SERVER_BASE_H_

#include "request.h"
#include "responder.h"
#include "router/router_base.h"
#include "server.h"

typedef struct {
  const char* (*GetDomain)(Server self);
  Router (*GetRouter)(Server self);
  void (*Do)(Server self, Request req, Responder r);
} ServerBaseMethodStruct;
typedef const ServerBaseMethodStruct* ServerBaseMethod;

extern const ServerBaseMethod serverBase;

#endif  // SRC_SERVER_SERVER_BASE_H_
