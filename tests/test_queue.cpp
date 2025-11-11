#include <gtest/gtest.h>
#include "Queue.h"
#include <string>


TEST(QueueTest, DefaultConstructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.getSize(), 0);
    EXPECT_EQ(queue.getCapacity(), 10);
}

TEST(QueueTest, SizeConstructor) {
    Queue<int> queue(5);
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.getSize(), 0);
    EXPECT_EQ(queue.getCapacity(), 5);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);
    queue1.push(3);

    Queue<int> queue2(queue1);
    EXPECT_EQ(queue2.getSize(), 3);
    EXPECT_EQ(queue2.front(), 1);
    EXPECT_EQ(queue2.back(), 3);
}

TEST(QueueTest, AssignmentOperator) {
    Queue<int> queue1;
    queue1.push(10);
    queue1.push(20);

    Queue<int> queue2;
    queue2 = queue1;

    EXPECT_EQ(queue2.getSize(), 2);
    EXPECT_EQ(queue2.front(), 10);
    EXPECT_EQ(queue2.back(), 20);
}


TEST(QueueTest, PushOperation) {
    Queue<int> queue(3);

    queue.push(1);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 1);

    queue.push(2);
    queue.push(3);
    EXPECT_EQ(queue.getSize(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
}


TEST(QueueTest, PopOperation) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.front(), 1);
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}


TEST(QueueTest, CircularBuffer) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);

    
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);

    queue.pop(); 
    queue.push(4); 


    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);

    queue.pop();
    queue.push(5); 


    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.back(), 5);
}


TEST(QueueTest, ClearOperation) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_FALSE(queue.empty());
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.getSize(), 0);
}

TEST(QueueTest, PopEmptyQueueException) {
    Queue<int> queue;

    EXPECT_THROW({
        queue.pop();
        }, std::runtime_error);
}


TEST(QueueTest, FrontEmptyQueueException) {
    Queue<int> queue;

    EXPECT_THROW({
        queue.front();
        }, std::runtime_error);
}


TEST(QueueTest, BackEmptyQueueException) {
    Queue<int> queue;

    EXPECT_THROW({
        queue.back();
        }, std::runtime_error);
}

TEST(QueueTest, PushFullQueueException) {
    Queue<int> queue(2);
    queue.push(1);
    queue.push(2);

    EXPECT_THROW({
        queue.push(3);
        }, std::runtime_error);
}

TEST(QueueTest, DoubleType) {
    Queue<double> queue;
    queue.push(3.14);
    queue.push(2.71);

    EXPECT_DOUBLE_EQ(queue.front(), 3.14);
    EXPECT_DOUBLE_EQ(queue.back(), 2.71);
}

