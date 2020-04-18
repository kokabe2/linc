// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_RESPONSE_RESPONSE_BASE_H_
#define SRC_RESPONSE_RESPONSE_BASE_H_

#include "bleu/v1/delegate_definition.h"
#include "response.h"


typedef struct {
  Response (*New)(void);
  void (*SetStatusCode)(Response self, int status_code);
  void (*SetBody)(Response self, void* body);
  void (*SetBodyDeleter)(Response self, DeleteDelegate delegate);
} ResponseBaseMethodStruct;
typedef const ResponseBaseMethodStruct* ResponseBaseMethod;

extern const ResponseBaseMethod responseBase;

#endif  // SRC_RESPONSE_RESPONSE_BASE_H_
