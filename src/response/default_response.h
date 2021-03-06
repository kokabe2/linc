﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONSE_DEFAULT_RESPONSE_H_
#define SRC_RESPONSE_DEFAULT_RESPONSE_H_

#include "response.h"

typedef struct {
  Response (*New)(void);  //
} DefaultResponseMethodStruct;
typedef const DefaultResponseMethodStruct* DefaultResponseMethod;

extern const DefaultResponseMethod defaultResponse;

#endif  // SRC_RESPONSE_DEFAULT_RESPONSE_H_
