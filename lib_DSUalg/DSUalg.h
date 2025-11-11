#pragma once
#include "dsu.h"
#include <vector>
#include <functional>

inline int countIslands(int** grid, int N) {
    if (N <= 0) return 0;

    DSU dsu(N * N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) continue;

            int currentIndex = i * N + j;

            if (j + 1 < N && grid[i][j + 1] == 1) {
                dsu.unite(currentIndex, i * N + (j + 1));
            }

            if (i + 1 < N && grid[i + 1][j] == 1) {
                dsu.unite(currentIndex, (i + 1) * N + j);
            }
        }
    }

  
    std::vector<bool> isIslandRoot(N * N, false);
    int islandCount = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 1) {
                int root = dsu.find(i * N + j);
                if (!isIslandRoot[root]) {
                    isIslandRoot[root] = true;
                    islandCount++;
                }
            }
        }
    }

    return islandCount;
}

template<int N>
inline int countIslands(int(&grid)[N][N]) {
    if (N <= 0) return 0;

    int** dynamicGrid = new int* [N];
    for (int i = 0; i < N; ++i) {
        dynamicGrid[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            dynamicGrid[i][j] = grid[i][j];
        }
    }

    int result = countIslands(dynamicGrid, N);

  
    for (int i = 0; i < N; ++i) {
        delete[] dynamicGrid[i];
    }
    delete[] dynamicGrid;

    return result;
}


inline int** createGrid(int N, std::function<int(int, int)> initFunc) {
    int** grid = new int* [N];
    for (int i = 0; i < N; ++i) {
        grid[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            grid[i][j] = initFunc(i, j);
        }
    }
    return grid;
}

inline void deleteGrid(int** grid, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}