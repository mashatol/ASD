#pragma once

#include <string>
#include <vector>
#include <functional>

#include "stack.h"
#include "dsu.h"
#include "list.h"

int countIslands(int** grid, int N);
bool check_brackets(const std::string& str);


template<typename T>
bool hasCycleFloyd(List<T>& list) {
    if (list.empty() || list.get_size() == 1) {
        return false;
    }

    typename List<T>::Iterator slow = list.begin();
    typename List<T>::Iterator fast = list.begin();
    typename List<T>::Iterator end = list.end();

    while (fast != end && fast.get_node()->next != nullptr) {
        slow = slow.get_node()->next;
        fast = fast.get_node()->next->next;

        if (slow.get_node() == fast.get_node()) {
            return true;
        }
    }

    return false;
}

template<typename T>
bool hasCycleReverse(List<T>& list) {
    if (list.empty() || list.get_size() == 1) {
        return false;
    }

    typename List<T>::Node* prev = nullptr;
    typename List<T>::Node* current = list.begin().get_node();
    typename List<T>::Node* next = nullptr;

    typename List<T>::Node* start = current;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;

        if (current == start) {
            return true;
        }
    }

    return false;
}

template<typename T>
typename List<T>::Iterator findCycleStart(List<T>& list) {
    if (list.empty() || list.get_size() == 1) {
        return list.end();
    }

    typename List<T>::Iterator slow = list.begin();
    typename List<T>::Iterator fast = list.begin();
    typename List<T>::Iterator end = list.end();

    bool cycle_detected = false;

    while (fast != end && fast.get_node()->next != nullptr) {
        slow = slow.get_node()->next;
        fast = fast.get_node()->next->next;

        if (slow.get_node() == fast.get_node()) {
            cycle_detected = true;
            break;
        }
    }

    if (!cycle_detected) {
        return end;
    }

    slow = list.begin();
    while (slow.get_node() != fast.get_node()) {
        slow = slow.get_node()->next;
        fast = fast.get_node()->next;
    }

    return slow;
}

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

