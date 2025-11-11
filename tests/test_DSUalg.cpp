#include <gtest/gtest.h>
#include "dsualg.h"

TEST(IslandCounter, EmptyGrid) {
    int** grid = nullptr;
    EXPECT_EQ(countIslands(grid, 0), 0);
}

TEST(IslandCounter, SingleCellLand) {
    int** grid = createGrid(1, [](int, int) { return 1; });
    EXPECT_EQ(countIslands(grid, 1), 1);
    deleteGrid(grid, 1);
}

TEST(IslandCounter, SingleCellWater) {
    int** grid = createGrid(1, [](int, int) { return 0; });
    EXPECT_EQ(countIslands(grid, 1), 0);
    deleteGrid(grid, 1);
}

TEST(IslandCounter, AllWater) {
    int** grid = createGrid(3, [](int, int) { return 0; });
    EXPECT_EQ(countIslands(grid, 3), 0);
    deleteGrid(grid, 3);
}

TEST(IslandCounter, AllLand) {
    int** grid = createGrid(3, [](int, int) { return 1; });
    EXPECT_EQ(countIslands(grid, 3), 1);
    deleteGrid(grid, 3);
}

TEST(IslandCounter, TwoIslands) {
    int grid[3][3] = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 1}
    };
    EXPECT_EQ(countIslands(grid), 2);
}

TEST(IslandCounter, ChessPattern) {
    int grid[3][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };
    EXPECT_EQ(countIslands(grid), 5);
}

TEST(IslandCounter, ComplexShape) {
    int grid[4][4] = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };
    EXPECT_EQ(countIslands(grid), 2);
}