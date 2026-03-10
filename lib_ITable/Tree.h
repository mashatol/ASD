#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

template<typename T>
class Tree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& value, Node* p = nullptr)
            : data(value), left(nullptr), right(nullptr), parent(p) {
        }
    };

private:
    Node* root;
    size_t count;

    // Вспомогательные методы
    void clearRecursive(Node* node) {
        if (node) {
            clearRecursive(node->left);
            clearRecursive(node->right);
            delete node;
        }
    }

    Node* copyRecursive(Node* node, Node* parent_node = nullptr) {
        if (!node) return nullptr;
        Node* new_node = new Node(node->data, parent_node);
        new_node->left = copyRecursive(node->left, new_node);
        new_node->right = copyRecursive(node->right, new_node);
        return new_node;
    }

    // Поиск позиции для вставки (обход в ширину)
    Node* findInsertPosition() {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (!current->left) return current;
            if (!current->right) return current;

            q.push(current->left);
            q.push(current->right);
        }
        return nullptr;
    }

    // Поиск последнего узла на последнем уровне
    Node* findLastNode() {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);
        Node* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.pop();

            if (last->left) q.push(last->left);
            if (last->right) q.push(last->right);
        }
        return last;
    }

public:
    Tree() : root(nullptr), count(0) {}

    Tree(const Tree& other) : root(nullptr), count(other.count) {
        if (other.root) {
            root = copyRecursive(other.root);
        }
    }

    Tree& operator=(const Tree& other) {
        if (this != &other) {
            clear();
            count = other.count;
            if (other.root) {
                root = copyRecursive(other.root);
            }
        }
        return *this;
    }

    ~Tree() {
        clear();
    }

    // Вставка элемента
    void insert(const T& value) {
        if (!root) {
            root = new Node(value);
            count = 1;
            return;
        }

        Node* pos = findInsertPosition();
        if (pos) {
            if (!pos->left) {
                pos->left = new Node(value, pos);
            }
            else {
                pos->right = new Node(value, pos);
            }
            count++;
        }
    }

    // Удаление элемента по значению
    bool erase(const T& value) {
        if (!root) return false;

        // Находим узел с данным значением
        Node* target = findNode(value);
        if (!target) return false;

        // Если это единственный узел
        if (count == 1) {
            delete root;
            root = nullptr;
            count = 0;
            return true;
        }

        // Находим последний узел
        Node* last = findLastNode();

        // Заменяем данные target на данные last
        target->data = last->data;

        // Удаляем последний узел
        Node* parent = last->parent;
        if (parent) {
            if (parent->left == last) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        delete last;
        count--;

        return true;
    }

    // Поиск узла по значению
    Node* findNode(const T& value) {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->data == value) {
                return current;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    // Поиск узла по значению (константная версия)
    const Node* findNode(const T& value) const {
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->data == value) {
                return current;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return nullptr;
    }

    // Проверка наличия элемента
    bool contains(const T& value) const {
        return findNode(value) != nullptr;
    }

    // Получение элемента по значению (для TableItem)
    T* getValue(const T& value) {
        Node* node = findNode(value);
        return node ? &(node->data) : nullptr;
    }

    const T* getValue(const T& value) const {
        const Node* node = findNode(value);
        return node ? &(node->data) : nullptr;
    }

    // Размер дерева
    size_t size() const {
        return count;
    }

    // Проверка на пустоту
    bool empty() const {
        return count == 0;
    }

    // Очистка дерева
    void clear() {
        clearRecursive(root);
        root = nullptr;
        count = 0;
    }

    // Методы обхода

    // 1. Прямой обход (Корень-Левый-Правый) - рекурсивно
    void preOrder(std::ostream& os = std::cout) const {
        preOrderHelper(root, os);
    }

    // 2. Симметричный обход (Левый-Корень-Правый) - рекурсивно
    void inOrder(std::ostream& os = std::cout) const {
        inOrderHelper(root, os);
    }

    // 3. Обратный обход (Левый-Правый-Корень) - рекурсивно
    void postOrder(std::ostream& os = std::cout) const {
        postOrderHelper(root, os);
    }

    // 4. Обход в ширину (уровневый)
    void levelOrder(std::ostream& os = std::cout) const {
        if (!root) return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            os << current->data << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        os << std::endl;
    }

    // Красивый вывод дерева
    void prettyPrint(std::ostream& os = std::cout) const {
        if (!root) {
            os << "Empty tree" << std::endl;
            return;
        }
        printTreeHelper(root, 0, os);
    }

    // Вывод всеми обходами
    void printAllOrders(std::ostream& os = std::cout) const {
        os << "Pre-order: ";
        preOrder(os);
        os << std::endl;

        os << "In-order: ";
        inOrder(os);
        os << std::endl;

        os << "Post-order: ";
        postOrder(os);
        os << std::endl;

        os << "Level-order: ";
        levelOrder(os);
    }

private:
    void preOrderHelper(Node* node, std::ostream& os) const {
        if (!node) return;
        os << node->data << " ";
        preOrderHelper(node->left, os);
        preOrderHelper(node->right, os);
    }

    void inOrderHelper(Node* node, std::ostream& os) const {
        if (!node) return;
        inOrderHelper(node->left, os);
        os << node->data << " ";
        inOrderHelper(node->right, os);
    }

    void postOrderHelper(Node* node, std::ostream& os) const {
        if (!node) return;
        postOrderHelper(node->left, os);
        postOrderHelper(node->right, os);
        os << node->data << " ";
    }

    void printTreeHelper(Node* node, int level, std::ostream& os) const {
        if (!node) return;

        printTreeHelper(node->right, level + 1, os);

        for (int i = 0; i < level; i++) {
            os << "    ";
        }
        os << node->data << std::endl;

        printTreeHelper(node->left, level + 1, os);
    }
};