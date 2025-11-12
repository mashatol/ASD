#include <gtest/gtest.h>
#include "stackL.h"

TEST(StackTest, EmptyStack) {
    StackList<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushIncreasesSize) {
    StackList<int> stack;
    stack.push(1);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);

    stack.push(2);
    EXPECT_EQ(stack.size(), 2);
}

TEST(StackTest, TopReturnsLastPushed) {
    StackList<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.top(), 20);

    stack.push(30);
    EXPECT_EQ(stack.top(), 30);
}

TEST(StackTest, PopDecreasesSize) {
    StackList<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, LIFOOrder) {
    StackList<int> stack;

    // Push 1, 2, 3
    for (int i = 1; i <= 3; ++i) {
        stack.push(i);
    }

    // Should pop 3, 2, 1
    EXPECT_EQ(stack.top(), 3);
    stack.pop();

    EXPECT_EQ(stack.top(), 2);
    stack.pop();

    EXPECT_EQ(stack.top(), 1);
    stack.pop();

    EXPECT_TRUE(stack.empty());
}

TEST(StackTest, TopThrowsWhenEmpty) {
    StackList<int> stack;
    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackTest, PopThrowsWhenEmpty) {
    StackList<int> stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTest, ClearEmptiesStack) {
    StackList<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.size(), 3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, StringStack) {
    StackList<std::string> stack;
    stack.push("hello");
    stack.push("world");

    EXPECT_EQ(stack.top(), "world");
    stack.pop();
    EXPECT_EQ(stack.top(), "hello");
}

TEST(StackTest, LargeNumberOfElements) {
    StackList<int> stack;
    const int COUNT = 1000;

    for (int i = 0; i < COUNT; ++i) {
        stack.push(i);
    }

    EXPECT_EQ(stack.size(), COUNT);

    for (int i = COUNT - 1; i >= 0; --i) {
        EXPECT_EQ(stack.top(), i);
        stack.pop();
    }

    EXPECT_TRUE(stack.empty());
}