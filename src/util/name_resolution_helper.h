// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_UTIL_NAME_RESOLUTION_HELPER_H_
#define SRC_UTIL_NAME_RESOLUTION_HELPER_H_

#include "pdns.h"

typedef struct {
  Server (*Retrieve)(const char* uri);
  Server (*RetrieveOrNewIfNotFound)(const char* uri);
} NameResolutionHelperMethodStruct;
typedef const NameResolutionHelperMethodStruct* NameResolutionHelperMethod;

extern const NameResolutionHelperMethod nameResolutionHelper;

#endif  // SRC_UTIL_NAME_RESOLUTION_HELPER_H_
