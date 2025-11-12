#include "alg.h"

int countIslands(int** grid, int N) {
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

bool check_brackets(const std::string& str) {
    Stack<char> brackets;

    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
        }
        else if (c == ')') {
            if (brackets.is_empty() || brackets.top() != '(') {
                return false;
            }
            brackets.pop();
        }
        else if (c == ']') {
            if (brackets.is_empty() || brackets.top() != '[') {
                return false;
            }
            brackets.pop();
        }
        else if (c == '}') {
            if (brackets.is_empty() || brackets.top() != '{') {
                return false;
            }
            brackets.pop();
        }
    }

    return brackets.is_empty();
}