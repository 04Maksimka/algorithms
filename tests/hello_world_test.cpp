const char* hello() {
    return "Hello, World!";
}

#include <gtest/gtest.h>

TEST(HelloWorldTest, BasicAssertions) {
    EXPECT_STREQ(hello(), "Hello, World!");
}