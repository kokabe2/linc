// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DEFAULT_ROUTER_H_
#define V1_DEFAULT_ROUTER_H_

#include "router.h"

typedef struct {
  Router (*New)(void);  //
} DefaultRouterMethodStruct;
typedef const DefaultRouterMethodStruct* DefaultRouterMethod;

extern const DefaultRouterMethod defaultRouter;

#endif  // V1_DEFAULT_ROUTER_H_
