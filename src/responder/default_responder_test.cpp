// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "responder/default_responder.h"
#include "response/default_response.h"
}

namespace {
bool was_ran;

void DeleteSpy(void** body) { was_ran = true; }
}  // namespace

class DefaultResponderTest : public ::testing::Test {
 protected:
  bool sent;
  Response res;
  Responder r;

  virtual void SetUp() {
    was_ran = false;
    sent = false;
    res = defaultResponse->New();
    r = defaultResponder->New(res);
  }

  virtual void TearDown() {
    if (!sent) r->Send(r);
    if (res != NULL) res->Delete(&res);
  }

  void Send() {
    r->Send(r);
    sent = true;
  }
};

TEST_F(DefaultResponderTest, SetStatusCode) {
  r->SetStatusCode(r, 404);

  EXPECT_EQ(404, res->GetStatusCode(res));
}

TEST_F(DefaultResponderTest, SetBody) {
  char dummy_data[8];

  r->SetBody(r, dummy_data);

  EXPECT_EQ(dummy_data, res->GetBody(res));
}

TEST_F(DefaultResponderTest, SetBodyDeleter) {
  r->SetBodyDeleter(r, DeleteSpy);

  res->Delete(&res);

  EXPECT_TRUE(was_ran);
}

TEST_F(DefaultResponderTest, Send) {
  r->SetBodyDeleter(r, DeleteSpy);

  Send();
}
