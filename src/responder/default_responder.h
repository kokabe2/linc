// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONDER_DEFAULT_RESPONDER_H_
#define SRC_RESPONDER_DEFAULT_RESPONDER_H_

#include "responder.h"
#include "response.h"

typedef struct {
  Responder (*New)(Response res);  //
} DefaultResponderMethodStruct;
typedef const DefaultResponderMethodStruct* DefaultResponderMethod;

extern const DefaultResponderMethod defaultResponder;

#endif  // SRC_RESPONDER_DEFAULT_RESPONDER_H_
