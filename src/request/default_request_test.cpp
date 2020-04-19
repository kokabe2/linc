// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "default_request.h"
}

class DefaultRequestTest : public ::testing::Test {
 protected:
  Request req;

  virtual void SetUp() {
    req = defaultRequest->New("GET", "api.test.domain/v1.1/users/kokabe/reports/256",
                              "api.test.domain/v1.1/users/:username/reports/:id");
  }

  virtual void TearDown() { req->Delete(&req); }
};

TEST_F(DefaultRequestTest, GetUri) { EXPECT_STREQ("api.test.domain/v1.1/users/kokabe/reports/256", req->GetUri(req)); }

TEST_F(DefaultRequestTest, GetDomain) { EXPECT_STREQ("api.test.domain", req->GetDomain(req)); }

TEST_F(DefaultRequestTest, GetPath) { EXPECT_STREQ("/v1.1/users/kokabe/reports/256", req->GetPath(req)); }

TEST_F(DefaultRequestTest, GetMethod) { EXPECT_STREQ("GET", req->GetMethod(req)); }

TEST_F(DefaultRequestTest, GetBodyWhenNotSet) { EXPECT_EQ(NULL, req->GetBody(req)); }

TEST_F(DefaultRequestTest, GetBody) {
  char dummy_data[8];

  defaultRequest->SetBody(req, dummy_data);

  EXPECT_EQ(dummy_data, req->GetBody(req));
}

TEST_F(DefaultRequestTest, GetParam) { EXPECT_STREQ("kokabe", req->GetParam(req, "username")); }

TEST_F(DefaultRequestTest, ToInt) {
  int id = req->ToInt(req->GetParam(req, "id"));

  EXPECT_EQ(256, id);
}
