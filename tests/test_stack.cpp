#include <gtest/gtest.h>
#include "Stack.h"

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_EQ(stack.count(), 0);
    EXPECT_EQ(stack.capacity(), 10);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(StackTest, SizeConstructor) {
    Stack<int> stack(5);
    EXPECT_EQ(stack.count(), 0);
    EXPECT_EQ(stack.capacity(), 5);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(StackTest, PushOperations) {
    Stack<int> stack(3);

    stack.push(10);
    EXPECT_EQ(stack.count(), 1);
    EXPECT_EQ(stack.top(), 10);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());

    stack.push(20);
    stack.push(30);
    EXPECT_EQ(stack.count(), 3);
    EXPECT_EQ(stack.top(), 30);
    EXPECT_TRUE(stack.is_full());
}

TEST(StackTest, PopOperations) {
    Stack<int> stack(3);
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.pop();
    EXPECT_EQ(stack.count(), 2);
    EXPECT_EQ(stack.top(), 20);
    EXPECT_FALSE(stack.is_full());

    stack.pop();
    EXPECT_EQ(stack.top(), 10);

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, ClearOperation) {
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.count(), 3);
    stack.clear();
    EXPECT_EQ(stack.count(), 0);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.capacity(), 5); // Емкость не меняется
}

TEST(StackTest, CopyConstructor) {
    Stack<int> stack1(3);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2(stack1);
    EXPECT_EQ(stack2.count(), 3);
    EXPECT_EQ(stack2.capacity(), 3);
    EXPECT_EQ(stack2.top(), 3);

  
    stack2.pop();
    EXPECT_EQ(stack2.top(), 2);
    EXPECT_EQ(stack1.top(), 3); // Исходный стек не изменился
}


TEST(StackTest, AssignmentOperator) {
    Stack<int> stack1(3);
    stack1.push(10);
    stack1.push(20);

    Stack<int> stack2;
    stack2 = stack1;

    EXPECT_EQ(stack2.count(), 2);
    EXPECT_EQ(stack2.capacity(), 3);
    EXPECT_EQ(stack2.top(), 20);

    stack2.pop();
    EXPECT_EQ(stack2.top(), 10);
    EXPECT_EQ(stack1.top(), 20); // Исходный стек не изменился
}


TEST(StackTest, EmptyStackPopException) {
    Stack<int> stack;

    EXPECT_THROW({
        stack.pop();
        }, std::runtime_error);
}

TEST(StackTest, EmptyStackTopException) {
    Stack<int> stack;

    EXPECT_THROW({
        stack.top();
        }, std::runtime_error);
}

TEST(StackTest, FullStackPushException) {
    Stack<int> stack(2);
    stack.push(1);
    stack.push(2);

    EXPECT_THROW({
        stack.push(3);
        }, std::runtime_error);
}

