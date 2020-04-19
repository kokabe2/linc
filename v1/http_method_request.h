// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_HTTP_METHOD_REQUEST_H_
#define V1_HTTP_METHOD_REQUEST_H_

#include "request.h"

typedef struct {
  Request (*New)(const char* method, const char* uri, const void* body);  //
} HttpMethodRequestMethodStruct;
typedef const HttpMethodRequestMethodStruct* HttpMethodRequestMethod;

extern const HttpMethodRequestMethod httpMethodRequest;

#endif  // V1_HTTP_METHOD_REQUEST_H_
