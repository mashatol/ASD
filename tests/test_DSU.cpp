#include <gtest/gtest.h>
#include "dsu.h"
#include <iostream>

TEST(DSUTest, Initialization) {
    DSU dsu(5);
    EXPECT_EQ(dsu.size(), 5);
    EXPECT_EQ(dsu.sets_count(), 5);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(DSUTest, BasicUnionFind) {
    DSU dsu(5);

    dsu.unite(0, 1);
    EXPECT_TRUE(dsu.same(0, 1));
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.sets_count(), 4);

    dsu.unite(2, 3);
    EXPECT_TRUE(dsu.same(2, 3));
    EXPECT_EQ(dsu.find(2), dsu.find(3));
    EXPECT_EQ(dsu.sets_count(), 3);

    EXPECT_FALSE(dsu.same(0, 2));
    EXPECT_FALSE(dsu.same(1, 3));
}

TEST(DSUTest, TransitiveUnion) {
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    EXPECT_TRUE(dsu.same(0, 2));
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(1), dsu.find(2));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.sets_count(), 3);
}

TEST(DSUTest, MultipleUnions) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(4, 5);

    EXPECT_EQ(dsu.sets_count(), 2);
    EXPECT_TRUE(dsu.same(0, 2));
    EXPECT_TRUE(dsu.same(3, 5));
    EXPECT_FALSE(dsu.same(0, 3));

    dsu.unite(2, 3);
    EXPECT_TRUE(dsu.same(0, 5));
    EXPECT_TRUE(dsu.same(1, 4));
    EXPECT_EQ(dsu.find(0), dsu.find(5));
    EXPECT_EQ(dsu.sets_count(), 1);
}

TEST(DSUTest, SelfUnion) {
    DSU dsu(3);

    dsu.unite(0, 0);
    dsu.unite(1, 1);

    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_FALSE(dsu.same(0, 1));
    EXPECT_EQ(dsu.sets_count(), 3);
}

TEST(DSUTest, PathCompression) {
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    int root = dsu.find(4);

    EXPECT_EQ(dsu.find(0), root);
    EXPECT_EQ(dsu.find(1), root);
    EXPECT_EQ(dsu.find(2), root);
    EXPECT_EQ(dsu.find(3), root);
    EXPECT_EQ(dsu.find(4), root);
}

TEST(DSUTest, MoveSemantics) {
    DSU dsu1(5);
    dsu1.unite(0, 1);
    dsu1.unite(2, 3);

    DSU dsu2 = std::move(dsu1);

    EXPECT_EQ(dsu2.size(), 5);
    EXPECT_TRUE(dsu2.same(0, 1));
    EXPECT_TRUE(dsu2.same(2, 3));
    EXPECT_FALSE(dsu2.same(0, 2));
}

TEST(DSUTest, OutOfRange) {
    DSU dsu(3);

    EXPECT_THROW(dsu.find(-1), std::out_of_range);
    EXPECT_THROW(dsu.find(3), std::out_of_range);
    EXPECT_THROW(dsu.find(100), std::out_of_range);

    EXPECT_THROW(dsu.unite(-1, 0), std::out_of_range);
    EXPECT_THROW(dsu.unite(0, 5), std::out_of_range);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}