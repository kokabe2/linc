// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "default_router.h"
#include "default_server.h"
#include "http_method_request.h"
#include "phttp_status_code.h"
#include "responder/default_responder.h"
#include "response/default_response.h"
#include "server/server_base.h"
}

namespace {
char buf[128];

void PostHandlerSpy(Request req, Responder r) {
  r->SetStatusCode(r, kStatusInternalServerError);
  r->SetBody(r, (void*)req->GetBody(req));
  r->Send(r);
}

void PutHandlerSpy(Request req, Responder r) {
  snprintf(buf, sizeof(buf), "%s", req->GetParam(req, "username"));
  r->SetStatusCode(r, kStatusCreated);
  r->SetBody(r, buf);
  r->Send(r);
}

void GetHandlerSpy(Request req, Responder r) {
  snprintf(buf, sizeof(buf), "%s", req->GetParam(req, "id"));
  r->SetStatusCode(r, kStatusOK);
  r->SetBody(r, buf);
  r->Send(r);
}

void DeleteHandlerSpy(Request req, Responder r) {
  snprintf(buf, sizeof(buf), "%s, %s", req->GetParam(req, "username"), req->GetParam(req, "id"));
  r->SetStatusCode(r, kStatusMethodNotAllowed);
  r->SetBody(r, buf);
  r->Send(r);
}
}  // namespace

class DefaultServerTest : public ::testing::Test {
 protected:
  char dummy_data[4];
  Request req;
  Response res;
  Responder r;
  Router router;
  Server server;

  virtual void SetUp() {
    memset(buf, 0, sizeof(buf));
    res = defaultResponse->New();
    r = defaultResponder->New(res);
    router = defaultRouter->New();
    router->POST(router, "/v1/sample", PostHandlerSpy);
    router->PUT(router, "/v1/users/:username/reports", PutHandlerSpy);
    router->GET(router, "/v1/users/:username/reports/:id", GetHandlerSpy);
    router->DELETE(router, "/v1/users/:username/reports/:id", DeleteHandlerSpy);
    server = defaultServer->New("api.test.domain", router);
  }

  virtual void TearDown() {
    server->Delete(&server);
    res->Delete(&res);
  }
};

TEST_F(DefaultServerTest, GetDomain) { EXPECT_STREQ("api.test.domain", serverBase->GetDomain(server)); }

TEST_F(DefaultServerTest, Post) {
  req = httpMethodRequest->New("POST", "api.test.domain/v1/sample", dummy_data);

  serverBase->DoPost(server, req, r);

  EXPECT_EQ(kStatusInternalServerError, res->GetStatusCode(res));
  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(DefaultServerTest, Put) {
  req = httpMethodRequest->New("PUT", "api.test.domain/v1/users/kokabe/reports", dummy_data);

  serverBase->DoPut(server, req, r);

  EXPECT_EQ(kStatusCreated, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe", (const char*)res->GetBody(res));
}

TEST_F(DefaultServerTest, Get) {
  req = httpMethodRequest->New("GET", "api.test.domain/v1/users/kokabe/reports/256", NULL);

  serverBase->DoGet(server, req, r);

  EXPECT_EQ(kStatusOK, res->GetStatusCode(res));
  EXPECT_STREQ("256", (const char*)res->GetBody(res));
}

TEST_F(DefaultServerTest, Delete) {
  req = httpMethodRequest->New("DELETE", "api.test.domain/v1/users/kokabe/reports/6", NULL);

  serverBase->DoDelete(server, req, r);

  EXPECT_EQ(kStatusMethodNotAllowed, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe, 6", (const char*)res->GetBody(res));
}

TEST_F(DefaultServerTest, UseHttpMethodWithBadUri) {
  req = httpMethodRequest->New("GET", "api.test.domain/v1/users/kokabe/stars/28", NULL);

  serverBase->DoGet(server, req, r);

  EXPECT_EQ(kStatusNotFound, res->GetStatusCode(res));
  EXPECT_STREQ(NULL, (const char*)res->GetBody(res));
}
