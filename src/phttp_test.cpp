// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "phttp.h"
}

namespace {
char buf[128];

void PostHandlerSpy(Request req, Responder r) {
  if (strcmp("POST", req->GetMethod(req)) == 0) {
    r->SetStatusCode(r, kStatusInternalServerError);
    r->SetBody(r, (void*)req->GetBody(req));
  }
}

void PutHandlerSpy(Request req, Responder r) {
  if (strcmp("PUT", req->GetMethod(req)) == 0) {
    snprintf(buf, sizeof(buf), "%s", req->GetParam(req, "username"));
    r->SetStatusCode(r, kStatusCreated);
    r->SetBody(r, buf);
  }
}

void GetHandlerSpy(Request req, Responder r) {
  if (strcmp("GET", req->GetMethod(req)) == 0) {
    snprintf(buf, sizeof(buf), "%s", req->GetParam(req, "id"));
    r->SetStatusCode(r, kStatusOK);
    r->SetBody(r, buf);
  }
}

void DeleteHandlerSpy(Request req, Responder r) {
  if (strcmp("DELETE", req->GetMethod(req)) == 0) {
    snprintf(buf, sizeof(buf), "%s, %s", req->GetParam(req, "username"), req->GetParam(req, "id"));
    r->SetStatusCode(r, kStatusMethodNotAllowed);
    r->SetBody(r, buf);
  }
}
}  // namespace

class PhttpTest : public ::testing::Test {
 protected:
  Response res;

  virtual void SetUp() {
    memset(buf, 0, sizeof(buf));
    phttp->Handle("api.test.domain/v1/sample", PostHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/reports", PutHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/reports/:id", GetHandlerSpy);
    phttp->Handle("api.test.domain/v1/users/:username/messages/:id", DeleteHandlerSpy);
    phttp->ListenAndServe("", NULL);
  }

  virtual void TearDown() { res->Delete(&res); }
};

TEST_F(PhttpTest, Post) {
  char dummy_data[4];

  res = phttp->POST("api.test.domain/v1/sample", dummy_data);

  EXPECT_EQ(kStatusInternalServerError, res->GetStatusCode(res));
  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(PhttpTest, Put) {
  char dummy_data[4];

  res = phttp->PUT("api.test.domain/v1/users/kokabe/reports", dummy_data);

  EXPECT_EQ(kStatusCreated, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe", (const char*)res->GetBody(res));
}

TEST_F(PhttpTest, Get) {
  char dummy_data[4];

  res = phttp->GET("api.test.domain/v1/users/kokabe/reports/256");

  EXPECT_EQ(kStatusOK, res->GetStatusCode(res));
  EXPECT_STREQ("256", (const char*)res->GetBody(res));
}

TEST_F(PhttpTest, Delete) {
  res = phttp->DELETE("api.test.domain/v1/users/kokabe/messages/6");

  EXPECT_EQ(kStatusMethodNotAllowed, res->GetStatusCode(res));
  EXPECT_STREQ("kokabe, 6", (const char*)res->GetBody(res));
}

TEST_F(PhttpTest, UseHttpMethodWithBadUri) {
  res = phttp->GET("api.test.domain/v1/users/kokabe/stars/28");

  EXPECT_EQ(kStatusNotFound, res->GetStatusCode(res));
  EXPECT_STREQ(NULL, (const char*)res->GetBody(res));
}
