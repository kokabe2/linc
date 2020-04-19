// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "response/default_response.h"
#include "response/response_base.h"
}

namespace {
void* given_body;

void DeleteSpy(void** body) { given_body = *body; }
}  // namespace

class DefaultResponseTest : public ::testing::Test {
 protected:
  Response res;

  virtual void SetUp() {
    given_body = NULL;
    res = defaultResponse->New();
  }

  virtual void TearDown() {
    if (res != NULL) res->Delete(&res);
  }
};

TEST_F(DefaultResponseTest, GetStatusCodeBeforeSet) { EXPECT_EQ(200, res->GetStatusCode(res)); }

TEST_F(DefaultResponseTest, GetBodyBeforeSet) { EXPECT_EQ(NULL, res->GetBody(res)); }

TEST_F(DefaultResponseTest, SetStatusCode) {
  responseBase->SetStatusCode(res, 404);

  EXPECT_EQ(404, res->GetStatusCode(res));
}

TEST_F(DefaultResponseTest, SetBody) {
  char dummy_data[8];

  responseBase->SetBody(res, dummy_data);

  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(DefaultResponseTest, SetBodyDeleter) {
  char dummy_data[8];
  responseBase->SetBody(res, dummy_data);

  responseBase->SetBodyDeleter(res, DeleteSpy);
  res->Delete(&res);

  EXPECT_EQ(dummy_data, given_body);
}
