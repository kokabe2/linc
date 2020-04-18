// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_RESPONSE_H_
#define V1_RESPONSE_H_

typedef struct ResponseInterfaceStruct* Response;
typedef struct ResponseInterfaceStruct {
  void (*Delete)(Response* self);
  int (*GetStatusCode)(Response self);
  const void* (*GetBody)(Response self);
} ResponseInterfaceStruct;

#endif  // V1_RESPONSE_H_
