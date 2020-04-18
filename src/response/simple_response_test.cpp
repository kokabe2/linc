// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "simple_response.h"
}

class SimpleResponseTest : public ::testing::Test {
 protected:
  Response res;

  virtual void SetUp() {}

  virtual void TearDown() { res->Delete(&res); }
};

TEST_F(SimpleResponseTest, GetStatusCode) {
  res = simpleResponse->New(404);

  EXPECT_EQ(404, res->GetStatusCode(res));
}

TEST_F(SimpleResponseTest, GetBody) {
  res = simpleResponse->New(200);

  EXPECT_EQ(NULL, res->GetBody(res));
}
