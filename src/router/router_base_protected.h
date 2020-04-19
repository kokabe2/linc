// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_ROUTER_ROUTER_BASE_PROTECTED_H_
#define SRC_ROUTER_ROUTER_BASE_PROTECTED_H_

#include "bleu/v1/list.h"
#include "router_base.h"

typedef struct {
  RouterInterfaceStruct impl;
  List handlers[4];
} RouterBaseStruct, *RouterBase;
typedef struct {
  void (*Super)(RouterBase self);  //
} RouterBaseProtectedMethodStruct;
typedef const RouterBaseProtectedMethodStruct* RouterBaseProtectedMethod;

extern const RouterBaseProtectedMethod _routerBase;

#endif  // SRC_ROUTER_ROUTER_BASE_PROTECTED_H_
