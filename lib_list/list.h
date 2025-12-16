#pragma once
#include <iostream>
#include <stdexcept>
#include <iterator>

template<typename T>
class List {
public: 
    struct Node {
    T value;
    Node* next;

    Node(const T& val, Node* next_node = nullptr)
        : value(val), next(next_node) {
    }
};
private:

    Node* head;
    Node* tail;
    size_t size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            Node* new_Node = new Node(current->value); //

            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->value); //
                current = current->next;
            }
        }
        return *this;
    }

    ~List() {
        clear();
    }

    // Основные операции
    void push_front(const T& value) {
        head = new Node(value, head);
        if (tail == nullptr) {
            tail = head;
        }
        size++;
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front from empty list");
        }

        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back from empty list");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front from empty list");
        }
        return head->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("front from empty list");
        }
        return head->value;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("back from empty list");
        }
        return tail->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("back from empty list");
        }
        return tail->value;
    }

    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    void clear() {
        while (!empty()) {
            pop_front(); //
        }
    }

   
    class Iterator {
    private:
        Node* current;

    public:
        Node* get_node() const { return current; };
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* node = nullptr) : current(node) {}

       
        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        reference operator*() {
            if (current == nullptr) {
                throw std::out_of_range("dereferencing end iterator");
            }
            return current->value;
        }

        pointer operator->() {
            if (current == nullptr) {
                throw std::out_of_range("accessing member through end iterator");
            }
            return &(current->value);
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    
    class ConstIterator {
    private:
        const Node* current;

    public:
        const Node* get_node() const { return current; }
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const Node* node = nullptr) : current(node) {}

        ConstIterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        reference operator*() const {
            if (current == nullptr) {
                throw std::out_of_range("dereferencing end iterator");
            }
            return current->value;
        }

        pointer operator->() const {
            if (current == nullptr) {
                throw std::out_of_range("accessing member through end iterator");
            }
            return &(current->value);
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ConstIterator& other) const {
            return !(*this == other);
        }
    };


    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator begin() const {
        return ConstIterator(head);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }

    ConstIterator cbegin() const {
        return ConstIterator(head);
    }

    ConstIterator cend() const {
        return ConstIterator(nullptr);
    }
};