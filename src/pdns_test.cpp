// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include <string.h>

#include "gtest/gtest.h"

extern "C" {
#include "default_router.h"
#include "default_server.h"
#include "pdns.h"
}

namespace {
Router r1;
Router r2;
Router r3;
Server s1;
Server s2;
Server s3;
}  // namespace

class PdnsTest : public ::testing::Test {
 protected:
  static void SetUpTestCase() {
    r1 = defaultRouter->New();
    r2 = defaultRouter->New();
    r3 = defaultRouter->New();
    s1 = defaultServer->New("api.test.domain", r1);
    s2 = defaultServer->New("foo.bar", r2);
    s3 = defaultServer->New("8080", r3);
    pdns->Register(s1);
    pdns->Register(s2);
    pdns->Register(s3);
  }
};

TEST_F(PdnsTest, Retrieve) {
  Server server = pdns->Retrieve("foo.bar");

  EXPECT_EQ(s2, server);
}

TEST_F(PdnsTest, RetrieveWhenNotExist) {
  Server server = pdns->Retrieve("deadbeaf.domain");

  EXPECT_EQ(NULL, server);
}
