// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_SERVER_SERVER_BASE_H_
#define SRC_SERVER_SERVER_BASE_H_

#include "request.h"
#include "responder.h"
#include "server.h"

typedef struct {
  const char* (*GetDomain)(Server self);
  void (*DoPost)(Server self, Request req, Responder r);
  void (*DoPut)(Server self, Request req, Responder r);
  void (*DoGet)(Server self, Request req, Responder r);
  void (*DoDelete)(Server self, Request req, Responder r);
} ServerBaseMethodStruct;
typedef const ServerBaseMethodStruct* ServerBaseMethod;

extern const ServerBaseMethod serverBase;

#endif  // SRC_SERVER_SERVER_BASE_H_
