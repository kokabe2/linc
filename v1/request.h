// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_REQUEST_H_
#define V1_REQUEST_H_

typedef struct RequestInterfaceStruct* Request;
typedef struct RequestInterfaceStruct {
  void (*Delete)(Request* self);
  const char* (*GetUri)(Request self);
  const char* (*GetDomain)(Request self);
  const char* (*GetPath)(Request self);
  const char* (*GetMethod)(Request self);
  const void* (*GetBody)(Request self);
  const char* (*GetParam)(Request self, const char* key);
  int (*ToInt)(const char* param);
} RequestInterfaceStruct;

#endif  // V1_REQUEST_H_
