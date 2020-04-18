// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_RESPONDER_H_
#define V1_RESPONDER_H_

#include "bleu/v1/delegate_definition.h"

typedef struct ResponderInterfaceStruct* Responder;
typedef struct ResponderInterfaceStruct {
  void (*SetStatusCode)(Responder self, int status_code);
  void (*SetBody)(Responder self, const void* body);
  void (*SetBodyDeleter)(Responder self, DeleteDelegate delegate);
  void (*Send)(Responder self);  // The Responder instance will be automatically destroyed.
} ResponderInterfaceStruct;

#endif  // V1_RESPONDER_H_
