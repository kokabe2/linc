// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_ROUTER_H_
#define V1_ROUTER_H_

#include "handler.h"

typedef struct RouterInterfaceStruct* Router;
typedef struct RouterInterfaceStruct {
  void (*Delete)(Router* self);
  void (*POST)(Router self, const char* pattern, PhttpHandlerDelegate handler);
  void (*PUT)(Router self, const char* pattern, PhttpHandlerDelegate handler);
  void (*GET)(Router self, const char* pattern, PhttpHandlerDelegate handler);
  void (*DELETE)(Router self, const char* pattern, PhttpHandlerDelegate handler);
} RouterInterfaceStruct;

#endif  // V1_ROUTER_H_
