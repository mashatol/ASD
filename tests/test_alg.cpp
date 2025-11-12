#include <gtest/gtest.h>
#include "alg.h"
#include "dsu.h"

TEST(BracketsTest, EmptyString) {
    EXPECT_TRUE(check_brackets(""));
}

TEST(BracketsTest, SinglePairs) {
    EXPECT_TRUE(check_brackets("()"));
    EXPECT_TRUE(check_brackets("[]"));
    EXPECT_TRUE(check_brackets("{}"));
}

TEST(BracketsTest, MultiplePairs) {
    EXPECT_TRUE(check_brackets("()[]{}"));
    EXPECT_TRUE(check_brackets("([])"));
    EXPECT_TRUE(check_brackets("{()}"));
    EXPECT_TRUE(check_brackets("[{}]"));
}

TEST(BracketsTest, NestedBrackets) {
    EXPECT_TRUE(check_brackets("({[]})"));
    EXPECT_TRUE(check_brackets("((()))"));
    EXPECT_TRUE(check_brackets("{{{}}}"));
    EXPECT_TRUE(check_brackets("[[[]]]"));
    EXPECT_TRUE(check_brackets("({[{}]})"));
}

TEST(BracketsTest, ComplexCorrectSequences) {
    EXPECT_TRUE(check_brackets("()()()()"));
    EXPECT_TRUE(check_brackets("(([]{}))"));
    EXPECT_TRUE(check_brackets("{()}[{}]"));
    EXPECT_TRUE(check_brackets("([{()()}])"));
    EXPECT_TRUE(check_brackets("((((()))))"));
}

TEST(BracketsTest, WithOtherCharacters) {
    EXPECT_TRUE(check_brackets("abc(def[ghi]jkl)mno"));
    EXPECT_TRUE(check_brackets("a + (b * [c - d])"));
    EXPECT_TRUE(check_brackets("if (x > 0) { y = [1, 2, 3]; }"));
    EXPECT_TRUE(check_brackets("function(a, b, c) { return a + b; }"));
    EXPECT_TRUE(check_brackets("array[[index]] = value;"));
}

TEST(BracketsTest, SingleUnclosed) {
    EXPECT_FALSE(check_brackets("("));
    EXPECT_FALSE(check_brackets("["));
    EXPECT_FALSE(check_brackets("{"));
    EXPECT_FALSE(check_brackets(")"));
    EXPECT_FALSE(check_brackets("]"));
    EXPECT_FALSE(check_brackets("}"));
}

TEST(BracketsTest, WrongOrder) {
    EXPECT_FALSE(check_brackets(")("));
    EXPECT_FALSE(check_brackets("]["));
    EXPECT_FALSE(check_brackets("}{"));
    EXPECT_FALSE(check_brackets("([)]"));
    EXPECT_FALSE(check_brackets("{[}]"));
    EXPECT_FALSE(check_brackets("(]"));
    EXPECT_FALSE(check_brackets("[)"));
    EXPECT_FALSE(check_brackets("{]"));
}

TEST(BracketsTest, MixedErrors) {
    EXPECT_FALSE(check_brackets("())"));
    EXPECT_FALSE(check_brackets("(()"));
    EXPECT_FALSE(check_brackets("{[}"));
    EXPECT_FALSE(check_brackets("{{}"));
    EXPECT_FALSE(check_brackets("[[]"));
    EXPECT_FALSE(check_brackets("())("));
    EXPECT_FALSE(check_brackets("{[}]"));
}

TEST(BracketsTest, OnlyOpening) {
    EXPECT_FALSE(check_brackets("(((("));
    EXPECT_FALSE(check_brackets("[[[["));
    EXPECT_FALSE(check_brackets("{{{{"));
    EXPECT_FALSE(check_brackets("(([[{{"));
}

TEST(BracketsTest, OnlyClosing) {
    EXPECT_FALSE(check_brackets("))))"));
    EXPECT_FALSE(check_brackets("]]]]"));
    EXPECT_FALSE(check_brackets("}}}}"));
    EXPECT_FALSE(check_brackets("))]]}}"));
}

TEST(BracketsTest, RealWorldExamples) {
    EXPECT_TRUE(check_brackets("(1 + [2 * {3 - 4}])"));
    EXPECT_TRUE(check_brackets("array = [1, 2, {key: value}]"));
    EXPECT_FALSE(check_brackets("if (x > 0 { y = 1; }"));
    EXPECT_FALSE(check_brackets("function(a, b] { return a + b; }"));
    EXPECT_FALSE(check_brackets("items = [1, 2, 3));"));
}

TEST(IslandCounter, EmptyGrid) {
    int** grid = nullptr;
    EXPECT_EQ(countIslands(grid, 0), 0);
}

TEST(IslandCounter, TwoIslands) {
    int grid[3][3] = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 1}
    };

    int n = 3;
    int** pgrid = new int* [n];
    for (int i = 0; i < n; i++) {
        pgrid[i] = new int[n];
        for (int j = 0; j < n; j++) {
            pgrid[i][j] = grid[i][j];
        }
    }

    EXPECT_EQ(countIslands(pgrid, n), 2);

    for (int i = 0; i < n; i++) {
        delete pgrid[i];
    }
    delete[]pgrid;
}

TEST(IslandCounter, ChessPattern) {
    int grid[3][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    int n = 3;
    int** pgrid = new int* [n];
    for (int i = 0; i < n; i++) {
        pgrid[i] = new int[n];
        for (int j = 0; j < n; j++) {
            pgrid[i][j] = grid[i][j];
        }
    }

    EXPECT_EQ(countIslands(pgrid, n), 5);

    for (int i = 0; i < n; i++) {
        delete pgrid[i];
    }
    delete[]pgrid;
}

TEST(IslandCounter, ComplexShape) {
    int grid[4][4] = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    int n = 4;
    int** pgrid = new int* [n];
    for (int i = 0; i < n; i++) {
        pgrid[i] = new int[n];
        for (int j = 0; j < n; j++) {
            pgrid[i][j] = grid[i][j];
        }
    }

    EXPECT_EQ(countIslands(pgrid, n), 2);

    for (int i = 0; i < n; i++) {
        delete pgrid[i];
    }
    delete[]pgrid;
}