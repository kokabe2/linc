// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "name_resolution_helper.h"

#include "bleu/v1/path.h"
#include "default_router.h"
#include "default_server.h"

static Server Retrieve(const char* uri) {
  Path p = path->New(uri);
  const char* domain = path->Directory(p, 0);
  Server s = pdns->Retrieve(domain);
  path->Delete(&p);
  return s;
}

inline static Server NewServer(const char* uri) {
  Router r = defaultRouter->New();
  Server s = defaultServer->New(uri, r);
  pdns->Register(s);
  return s;
}

static Server RetrieveOrNewIfNotFound(const char* uri) {
  Path p = path->New(uri);
  const char* domain = path->Directory(p, 0);
  Server s = pdns->Retrieve(domain);
  if (s == NULL) s = NewServer(domain);
  path->Delete(&p);
  return s;
}

static const NameResolutionHelperMethodStruct kTheMethod = {
    .Retrieve = Retrieve,
    .RetrieveOrNewIfNotFound = RetrieveOrNewIfNotFound,
};

const NameResolutionHelperMethod nameResolutionHelper = &kTheMethod;
