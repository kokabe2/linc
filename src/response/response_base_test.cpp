// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "response/response_base.h"
}

namespace {
void* given_body;

void DeleteSpy(void** body) { given_body = *body; }
}  // namespace

class ResponseBaseTest : public ::testing::Test {
 protected:
  Response res;

  virtual void SetUp() {
    given_body = NULL;
    res = responseBase->New();
  }

  virtual void TearDown() {
    if (res != NULL) res->Delete(&res);
  }
};

TEST_F(ResponseBaseTest, GetStatusCodeBeforeSet) { EXPECT_EQ(200, res->GetStatusCode(res)); }

TEST_F(ResponseBaseTest, GetBodyBeforeSet) { EXPECT_EQ(NULL, res->GetBody(res)); }

TEST_F(ResponseBaseTest, SetStatusCode) {
  responseBase->SetStatusCode(res, 404);

  EXPECT_EQ(404, res->GetStatusCode(res));
}

TEST_F(ResponseBaseTest, SetBody) {
  char dummy_data[8];

  responseBase->SetBody(res, dummy_data);

  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(ResponseBaseTest, SetBodyDeleter) {
  char dummy_data[8];
  responseBase->SetBody(res, dummy_data);

  responseBase->SetBodyDeleter(res, DeleteSpy);
  res->Delete(&res);

  EXPECT_EQ(dummy_data, given_body);
}
