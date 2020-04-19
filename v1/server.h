// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SERVER_H_
#define V1_SERVER_H_

#include "bleu/v1/runtime_error.h"

typedef struct ServerInterfaceStruct* Server;
typedef struct ServerInterfaceStruct {
  void (*Delete)(Server* self);
  RuntimeError (*ListenAndServe)(Server self);
} ServerInterfaceStruct;

#endif  // V1_SERVER_H_
