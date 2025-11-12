#pragma once
#include "list.h"

template<typename T>
class StackList {
private:
    List<T> list;

public:
    StackList() = default;

    // Конструктор копирования
    StackList(const StackList& other) : list(other.list) {}

    // Оператор присваивания
    StackList& operator=(const StackList& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    // Конструктор перемещения
    StackList(StackList&& other) noexcept : list(std::move(other.list)) {}

    // Оператор перемещения
    StackList& operator=(StackList&& other) noexcept {
        if (this != &other) {
            list = std::move(other.list);
        }
        return *this;
    }

    void push(const T& value) {
        list.push_front(value);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop from empty stack");
        }
        list.pop_front();
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("top from empty stack");
        }
        return list.front();
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top from empty stack");
        }
        return list.front();
    }

    bool empty() const {
        return list.empty();
    }

    size_t size() const {
        return list.get_size();
    }

    void clear() {
        list.clear();
    }
};