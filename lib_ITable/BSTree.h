#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template<typename T>
class BSTree {
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

    // Поиск минимального элемента в поддереве
    Node* findMin(Node* node) const {
        if (!node) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // Поиск максимального элемента в поддереве
    Node* findMax(Node* node) const {
        if (!node) return nullptr;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

public:
    BSTree() : root(nullptr), count(0) {}

    BSTree(const BSTree& other) : root(nullptr), count(other.count) {
        if (other.root) {
            root = copyRecursive(other.root);
        }
    }

    BSTree& operator=(const BSTree& other) {
        if (this != &other) {
            clear();
            count = other.count;
            if (other.root) {
                root = copyRecursive(other.root);
            }
        }
        return *this;
    }

    ~BSTree() {
        clear();
    }

    // Вставка элемента в BST
    void insert(const T& value) {
        if (!root) {
            root = new Node(value);
            count = 1;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                // Элемент уже существует - обновляем или ничего не делаем
                // В нашем случае для таблицы будем обновлять значение
                current->data = value;
                return;
            }
        }

        if (value < parent->data) {
            parent->left = new Node(value, parent);
        }
        else {
            parent->right = new Node(value, parent);
        }
        count++;
    }

    // Удаление элемента из BST
    bool erase(const T& value) {
        Node* node = findNode(value);
        if (!node) return false;

        // Случай 1: удаление листа (нет детей)
        if (!node->left && !node->right) {
            if (node == root) {
                delete root;
                root = nullptr;
            }
            else {
                Node* parent = node->parent;
                if (parent->left == node) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
                delete node;
            }
            count--;
            return true;
        }

        // Случай 2: есть только правый потомок
        if (!node->left && node->right) {
            if (node == root) {
                root = node->right;
                root->parent = nullptr;
            }
            else {
                Node* parent = node->parent;
                if (parent->left == node) {
                    parent->left = node->right;
                }
                else {
                    parent->right = node->right;
                }
                node->right->parent = parent;
            }
            delete node;
            count--;
            return true;
        }

        // Случай 3: есть только левый потомок
        if (node->left && !node->right) {
            if (node == root) {
                root = node->left;
                root->parent = nullptr;
            }
            else {
                Node* parent = node->parent;
                if (parent->left == node) {
                    parent->left = node->left;
                }
                else {
                    parent->right = node->left;
                }
                node->left->parent = parent;
            }
            delete node;
            count--;
            return true;
        }

        // Случай 4: есть оба потомка
        // Находим максимальный элемент в левом поддереве
        Node* maxLeft = findMax(node->left);

        // Копируем данные
        node->data = maxLeft->data;

        // Удаляем узел с максимальным значением
        if (maxLeft->parent->right == maxLeft) {
            maxLeft->parent->right = maxLeft->left;
        }
        else {
            maxLeft->parent->left = maxLeft->left;
        }
        if (maxLeft->left) {
            maxLeft->left->parent = maxLeft->parent;
        }

        delete maxLeft;
        count--;
        return true;
    }

    // Поиск узла по значению
    Node* findNode(const T& value) {
        Node* current = root;
        while (current) {
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return nullptr;
    }

    // Поиск узла по значению (константная версия)
    const Node* findNode(const T& value) const {
        Node* current = root;
        while (current) {
            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return nullptr;
    }

    // Проверка наличия элемента
    bool contains(const T& value) const {
        return findNode(value) != nullptr;
    }

    // Получение элемента по значению
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

    // 1. Прямой обход (Корень-Левый-Правый)
    void preOrder(std::ostream& os = std::cout) const {
        preOrderHelper(root, os);
        os << std::endl;
    }

    // 2. Симметричный обход (Левый-Корень-Правый) - для упорядоченного вывода
    void inOrder(std::ostream& os = std::cout) const {
        inOrderHelper(root, os);
        os << std::endl;
    }

    // 3. Обратный обход (Левый-Правый-Корень)
    void postOrder(std::ostream& os = std::cout) const {
        postOrderHelper(root, os);
        os << std::endl;
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

        os << "In-order: ";
        inOrder(os);

        os << "Post-order: ";
        postOrder(os);

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