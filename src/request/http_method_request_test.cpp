// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "http_method_request.h"
}

class HttpMethodRequestTest : public ::testing::Test {
 protected:
  char dummy_data[8];
  Request req;

  virtual void SetUp() {
    req = httpMethodRequest->New("PUT", "api.test.domain/v1.1/users/kokabe/issues/1024", dummy_data);
  }

  virtual void TearDown() { req->Delete(&req); }
};

TEST_F(HttpMethodRequestTest, GetUri) {
  EXPECT_STREQ("api.test.domain/v1.1/users/kokabe/issues/1024", req->GetUri(req));
}

TEST_F(HttpMethodRequestTest, GetDomain) { EXPECT_STREQ("api.test.domain", req->GetDomain(req)); }

TEST_F(HttpMethodRequestTest, GetPath) { EXPECT_STREQ("/v1.1/users/kokabe/issues/1024", req->GetPath(req)); }

TEST_F(HttpMethodRequestTest, GetMethod) { EXPECT_STREQ("PUT", req->GetMethod(req)); }

TEST_F(HttpMethodRequestTest, GetBody) { EXPECT_EQ(dummy_data, req->GetBody(req)); }
