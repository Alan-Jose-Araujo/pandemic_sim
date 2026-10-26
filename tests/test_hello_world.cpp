#include <gtest/gtest.h>
#include <example/HelloWorld.hpp>

TEST(HelloWorldTest, SayHello) {
    HelloWorld hello;
    testing::internal::CaptureStdout();
    hello.sayHello();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello World!\n");
}