# Linc [![pipeline status](https://gitlab.com/kokabe/linc/badges/master/pipeline.svg)](https://gitlab.com/kokabe/linc/commits/master) [![coverage report](https://gitlab.com/kokabe/linc/badges/master/coverage.svg)](https://gitlab.com/kokabe/linc/commits/master) [![License](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)

Linc is not Web API, but internal API among static components.

## Overview

- Written in C
- For embedded systems
- Every feature comes with tests
- Developer Friendly
- MIT license

## How To Use

This is just a example.

### Server Side

#### Primer

```c
#include "linc/v1/phttp.h"

static void handler(Request req, Responder r) {
  // Do something
}

void main(void) {
  phttp->Handle("api.test.domain/v1/sample", handler);
  phttp->ListenAndServe("", NULL);
}
```

#### Advanced

```c
#include "linc/v1/default_server.h"
#include "linc/v1/default_router.h"

static void handler1(Request req, Responder r) {
  // Do something
}

static void handler2(Request req, Responder r) {
  // Do something
}

void main(void) {
  Router router = defaultRouter->New();
  router->GET(router, "/v1/sample", handler1);
  router->PUT(router, "/v1/users/:id", handler2);
  Server server = defaultServer->New("api.test.domain", router);
  RuntimeError e = server->ListenAndServe(server);
  if (e != NULL) log.Fatal(e);
}
```

### Client Side

#### Primer

```c
#include "linc/v1/phttp.h"
#include "sample_resource.h"

void main(void) {
  SampleRequestStruct body = {6, "param"};
  Response res = phttp->POST("api.test.domain/v1/sample", &body);
}
```

#### Advanced

```c
#include "linc/v1/http_method_request.h"
#include "linc/v1/default_client.h"
#include "test_responder.h"
#include "sample_resource.h"

static void SendDelegate(int status, const void*response) {
  // Do something.
}

void main(void) {
  SampleRequestStruct body = {6, "param"};
  Request req = httpMethodRequest->New("POST", "api.test.domain/v1/sample", &body);
  Responder r = testResponder->New();
  Client client = defaultClient->New(r);
  client->Do(client, req);
}
```

### URI

#### Structure

```c
[Domain]/[API Version]/[Path]
```

#### Example

```c
api.test.domain/v1/sample/foo
```
