// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "default_client.h"
#include "http_method_request.h"
#include "phttp.h"
#include "responder/default_responder.h"
#include "response/default_response.h"
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

class DefaultClientTest : public ::testing::Test {
 protected:
  char dummy_data[4];
  Request req;
  Response res;
  Responder r;
  Client client;

  static void SetUpTestCase() {
    phttp->Handle("api.test.domain/v1/sample", PostHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/reports", PutHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/reports/:id", GetHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/messages/:id", DeleteHandlerSpy);
    phttp->ListenAndServe("", NULL);
  }

  virtual void SetUp() {
    memset(buf, 0, sizeof(buf));
    res = defaultResponse->New();
    r = defaultResponder->New(res);
    client = defaultClient->New(r);
  }

  virtual void TearDown() {
    client->Delete(&client);
    res->Delete(&res);
  }
};

TEST_F(DefaultClientTest, Post) {
  req = httpMethodRequest->New("POST", "api.test.domain/v1/sample", dummy_data);

  client->Do(client, req);

  EXPECT_EQ(kStatusInternalServerError, res->GetStatusCode(res));
  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(DefaultClientTest, Put) {
  req = httpMethodRequest->New("PUT", "api.test.domain/v1/users/kokabe/reports", dummy_data);

  client->Do(client, req);

  EXPECT_EQ(kStatusCreated, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe", (const char*)res->GetBody(res));
}

TEST_F(DefaultClientTest, Get) {
  req = httpMethodRequest->New("GET", "api.test.domain/v1/users/kokabe/reports/256", NULL);

  client->Do(client, req);

  EXPECT_EQ(kStatusOK, res->GetStatusCode(res));
  EXPECT_STREQ("256", (const char*)res->GetBody(res));
}

TEST_F(DefaultClientTest, Delete) {
  req = httpMethodRequest->New("DELETE", "api.test.domain/v1/users/kokabe/messages/6", NULL);

  client->Do(client, req);

  EXPECT_EQ(kStatusMethodNotAllowed, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe, 6", (const char*)res->GetBody(res));
}

TEST_F(DefaultClientTest, UseHttpMethodWithBadDomain) {
  req = httpMethodRequest->New("GET", "api.tesT.domain/v1/users/kokabe/reports/28", NULL);

  client->Do(client, req);

  EXPECT_EQ(kStatusNotFound, res->GetStatusCode(res));
  EXPECT_STREQ(NULL, (const char*)res->GetBody(res));
}
