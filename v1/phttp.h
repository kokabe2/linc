// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_PHTTP_H_
#define V1_PHTTP_H_

#include "bleu/v1/runtime_error.h"
#include "handler.h"
#include "phttp_status_code.h"
#include "response.h"

typedef struct {
  void (*Handle)(const char* uri, PhttpHandlerDelegate handler);
  RuntimeError (*ListenAndServe)(const char* addr, void* reserved);
  Response (*POST)(const char* uri, const void* body);
  Response (*PUT)(const char* uri, const void* body);
  Response (*GET)(const char* uri);
  Response (*DELETE)(const char* uri);
} PhttpMethodStruct;
typedef const PhttpMethodStruct* PhttpMethod;

extern const PhttpMethod phttp;

#endif  // V1_PHTTP_H_
