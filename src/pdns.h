// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_PDNS_H_
#define SRC_PDNS_H_

#include "server/server_base.h"

typedef struct {
  void (*Register)(Server server);
  Server (*Retrieve)(const char* domain);
} PdnsMethodStruct;
typedef const PdnsMethodStruct* PdnsMethod;

extern const PdnsMethod pdns;

#endif  // SRC_PDNS_H_
