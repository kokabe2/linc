// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DEFAULT_SERVER_H_
#define V1_DEFAULT_SERVER_H_

#include "router.h"
#include "server.h"

typedef struct {
  Server (*New)(const char* domain, Router router);  //
} DefaultServerMethodStruct;
typedef const DefaultServerMethodStruct* DefaultServerMethod;

extern const DefaultServerMethod defaultServer;

#endif  // V1_DEFAULT_SERVER_H_
