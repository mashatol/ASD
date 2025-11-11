#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    T* data;
    int capacity;
    int frontIndex;
    int backIndex;
    int size;

public:
    Queue();
    explicit Queue(int initialCapacity);
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();
    void push(const T& value);
    void pop();
    T front() const;
    T back() const;
    bool empty() const;
    int getSize() const;
    int getCapacity() const;
    void clear();
};

template <typename T>
Queue<T>::Queue() : capacity(10), frontIndex(0), backIndex(-1), size(0) {
    data = new T[capacity];
}

template <typename T>
Queue<T>::Queue(int initialCapacity) : capacity(initialCapacity > 0 ? initialCapacity : 10),
frontIndex(0), backIndex(-1), size(0) {
    data = new T[capacity];
}

template <typename T>
Queue<T>::Queue(const Queue& other) : capacity(other.capacity), frontIndex(other.frontIndex),
backIndex(other.backIndex), size(other.size) {
    data = new T[capacity];
    for (int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;
        size = other.size;
        data = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue() {
    delete[] data;
}

template <typename T>
void Queue<T>::push(const T& value) {
    if (size == capacity) {
        throw std::runtime_error("Queue is full");
    }
    backIndex = (backIndex + 1) % capacity;
    data[backIndex] = value;
    size++;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    frontIndex = (frontIndex + 1) % capacity;
    size--;
}

template <typename T>
T Queue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[frontIndex];
}

template <typename T>
T Queue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data[backIndex];
}

template <typename T>
bool Queue<T>::empty() const {
    return size == 0;
}

template <typename T>
int Queue<T>::getSize() const {
    return size;
}

template <typename T>
int Queue<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void Queue<T>::clear() {
    frontIndex = 0;
    backIndex = -1;
    size = 0;
}

#endif // QUEUE_H