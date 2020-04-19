// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONSE_SIMPLE_RESPONSE_H_
#define SRC_RESPONSE_SIMPLE_RESPONSE_H_

#include "response.h"

typedef struct {
  Response (*New)(int status_code);  //
} SimpleResponseMethodStruct;
typedef const SimpleResponseMethodStruct* SimpleResponseMethod;

extern const SimpleResponseMethod simpleResponse;

#endif  // SRC_RESPONSE_SIMPLE_RESPONSE_H_
