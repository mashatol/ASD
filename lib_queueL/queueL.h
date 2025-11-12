#pragma once
#include "list.h"

template<typename T>
class QueueList {
private:
    List<T> list;

public:
    QueueList() = default;

    // Конструктор копирования
    QueueList(const QueueList& other) : list(other.list) {}

    // Оператор присваивания
    QueueList& operator=(const QueueList& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    // Конструктор перемещения
    QueueList(QueueList&& other) noexcept : list(std::move(other.list)) {}

    // Оператор перемещения
    QueueList& operator=(QueueList&& other) noexcept {
        if (this != &other) {
            list = std::move(other.list);
        }
        return *this;
    }

    void push(const T& value) {
        list.push_back(value);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop from empty queue");
        }
        list.pop_front();
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front from empty queue");
        }
        return list.front();
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("front from empty queue");
        }
        return list.front();
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("back from empty queue");
        }
        return list.back();
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("back from empty queue");
        }
        return list.back();
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