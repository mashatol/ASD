#include <gtest/gtest.h>
#include "queueL.h"

TEST(QueueTest, EmptyQueue) {
    QueueList<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, PushIncreasesSize) {
    QueueList<int> queue;
    queue.push(1);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);

    queue.push(2);
    EXPECT_EQ(queue.size(), 2);
}

TEST(QueueTest, FrontAndBack) {
    QueueList<int> queue;
    queue.push(10);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10);

    queue.push(20);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 20);

    queue.push(30);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);
}

TEST(QueueTest, PopDecreasesSize) {
    QueueList<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.pop();
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 3);

    queue.pop();
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 3);
    EXPECT_EQ(queue.back(), 3);

    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, FIFOOrder) {
    QueueList<int> queue;

    // Push 1, 2, 3
    for (int i = 1; i <= 3; ++i) {
        queue.push(i);
    }

    // Should dequeue 1, 2, 3
    EXPECT_EQ(queue.front(), 1);
    queue.pop();

    EXPECT_EQ(queue.front(), 2);
    queue.pop();

    EXPECT_EQ(queue.front(), 3);
    queue.pop();

    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, FrontThrowsWhenEmpty) {
    QueueList<int> queue;
    EXPECT_THROW(queue.front(), std::out_of_range);
}

TEST(QueueTest, BackThrowsWhenEmpty) {
    QueueList<int> queue;
    EXPECT_THROW(queue.back(), std::out_of_range);
}

TEST(QueueTest, PopThrowsWhenEmpty) {
    QueueList<int> queue;
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(QueueTest, ClearEmptiesQueue) {
    QueueList<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.size(), 3);
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, StringQueue) {
    QueueList<std::string> queue;
    queue.push("hello");
    queue.push("world");

    EXPECT_EQ(queue.front(), "hello");
    EXPECT_EQ(queue.back(), "world");
    queue.pop();
    EXPECT_EQ(queue.front(), "world");
}

TEST(QueueTest, LargeNumberOfElements) {
    QueueList<int> queue;
    const int COUNT = 1000;

    for (int i = 0; i < COUNT; ++i) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), COUNT);

    for (int i = 0; i < COUNT; ++i) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, MixedOperations) {
    QueueList<int> queue;

    // Добавляем 3 элемента
    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 30);

    // Удаляем один
    queue.pop();
    EXPECT_EQ(queue.front(), 20);
    EXPECT_EQ(queue.back(), 30);

    // Добавляем еще
    queue.push(40);
    EXPECT_EQ(queue.front(), 20);
    EXPECT_EQ(queue.back(), 40);

    // Удаляем все
    queue.pop();
    queue.pop();
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, SingleElementQueue) {
    QueueList<int> queue;
    queue.push(42);

    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 42);
    EXPECT_EQ(queue.back(), 42);

    queue.pop();
    EXPECT_TRUE(queue.empty());
}