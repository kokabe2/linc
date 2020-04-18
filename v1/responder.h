// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_RESPONDER_H_
#define V1_RESPONDER_H_

typedef struct ResponderInterfaceStruct* Responder;
typedef struct ResponderInterfaceStruct {
  void (*SetStatusCode)(Responder self, int status_code);
  void (*SetBody)(Responder self, const void* body);
  void (*Send)(Responder self);  // The Responder instance will be automatically destroyed.
} ResponderInterfaceStruct;

#endif  // V1_RESPONDER_H_
