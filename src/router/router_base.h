// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_ROUTER_ROUTER_BASE_H_
#define SRC_ROUTER_ROUTER_BASE_H_

#include "router.h"

typedef struct {
  void (*DoPost)(Router self, Request req, Responder r);
  void (*DoPut)(Router self, Request req, Responder r);
  void (*DoGet)(Router self, Request req, Responder r);
  void (*DoDelete)(Router self, Request req, Responder r);
} RouterBaseMethodStruct;
typedef const RouterBaseMethodStruct* RouterBaseMethod;

extern const RouterBaseMethod routerBase;

#endif  // SRC_ROUTER_ROUTER_BASE_H_
