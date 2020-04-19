// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_REQUEST_DEFAULT_REQUEST_H_
#define SRC_REQUEST_DEFAULT_REQUEST_H_

#include "request.h"

typedef struct {
  Request (*New)(const char* method, const char* uri, const char* pattern, const void* body);
} DefaultRequestMethodStruct;
typedef const DefaultRequestMethodStruct* DefaultRequestMethod;

extern const DefaultRequestMethod defaultRequest;

#endif  // SRC_REQUEST_DEFAULT_REQUEST_H_
