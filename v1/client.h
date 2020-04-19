// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_CLIENT_H_
#define V1_CLIENT_H_

#include "request.h"

typedef struct ClientInterfaceStruct* Client;
typedef struct ClientInterfaceStruct {
  void (*Delete)(Client* self);
  void (*Do)(Client self, Request req);
} ClientInterfaceStruct;

#endif  // V1_CLIENT_H_
