#pragma once
#include <stdexcept>

template<typename T>
class StackList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value, Node* next_node = nullptr) : data(value), next(next_node) {}
    };

    Node* top_node;
    size_t stack_size;

public:
    StackList() : top_node(nullptr), stack_size(0) {}

    ~StackList() {
        clear();
    }
    StackList(const StackList&) = delete;
    StackList& operator=(const StackList&) = delete;

    StackList(StackList&& other) noexcept : top_node(other.top_node), stack_size(other.stack_size) {
        other.top_node = nullptr;
        other.stack_size = 0;
    }

    StackList& operator=(StackList&& other) noexcept {
        if (this != &other) {
            clear();
            top_node = other.top_node;
            stack_size = other.stack_size;
            other.top_node = nullptr;
            other.stack_size = 0;
        }
        return *this;
    }

    void push(const T& value) {
        top_node = new Node(value, top_node);
        stack_size++;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop from empty stack");
        }
        Node* temp = top_node;
        top_node = top_node->next;
        delete temp;
        stack_size--;
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("top from empty stack");
        }
        return top_node->data;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top from empty stack");
        }
        return top_node->data;
    }

    bool empty() const {
        return stack_size == 0;
    }

    size_t size() const {
        return stack_size;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }
};