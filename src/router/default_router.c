// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "default_router.h"

#include "bleu/v1/heap.h"
#include "router/router_base_protected.h"

static Router New(void) {
  RouterBase self = heap->New(sizeof(RouterBaseStruct));
  _routerBase->Super(self);
  return (Router)self;
}

static const DefaultRouterMethodStruct kTheMethod = {
    .New = New,
};

const DefaultRouterMethod defaultRouter = &kTheMethod;
