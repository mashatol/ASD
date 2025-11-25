#pragma once

#include <string>
#include <vector>
#include <functional>

#include "stack.h"
#include "dsu.h"

int countIslands(int** grid, int N);
bool check_brackets(const std::string& str);

//int countIslands(int** grid, int N) {
//    if (N <= 0) return 0;
//
//    int** dynamicGrid = new int* [N];
//    for (int i = 0; i < N; ++i) {
//        dynamicGrid[i] = new int[N];
//        for (int j = 0; j < N; ++j) {
//            dynamicGrid[i][j] = grid[i][j];
//        }
//    }
//
//    int result = countIslands(dynamicGrid, N);
//
//
//    for (int i = 0; i < N; ++i) {
//        delete[] dynamicGrid[i];
//    }
//    delete[] dynamicGrid;
//
//    return result;
//}


//inline int** createGrid(int N, ) {
//    int** grid = new int* [N];
//    for (int i = 0; i < N; ++i) {
//        grid[i] = new int[N];
//        for (int j = 0; j < N; ++j) {
//            grid[i][j] = initFunc(i, j);
//        }
//    }
//    return grid;
//}
//
//inline void deleteGrid(int** grid, int N) {
//    for (int i = 0; i < N; ++i) {
//        delete[] grid[i];
//    }
//    delete[] grid;
//}

