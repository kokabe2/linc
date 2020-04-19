// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DEFAULT_CLIENT_H_
#define V1_DEFAULT_CLIENT_H_

#include "client.h"
#include "responder.h"

typedef struct {
  Client (*New)(Responder r);  //
} DefaultClientMethodStruct;
typedef const DefaultClientMethodStruct* DefaultClientMethod;

extern const DefaultClientMethod defaultClient;

#endif  // V1_DEFAULT_CLIENT_H_
