// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_REQUEST_REQUEST_BASE_H_
#define SRC_REQUEST_REQUEST_BASE_H_

#include "bleu/v1/delegate_definition.h"
#include "request.h"

typedef struct {
  void (*SetBody)(Request self, const void* body);  //
} RequestBaseMethodStruct;
typedef const RequestBaseMethodStruct* RequestBaseMethod;

extern const RequestBaseMethod requestBase;

#endif  // SRC_REQUEST_REQUEST_BASE_H_
