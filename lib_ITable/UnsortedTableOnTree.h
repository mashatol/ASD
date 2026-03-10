#pragma once
#include "itable.h"
#include "Tree.h"
#include <iostream>

template<typename TKey, typename TVal>
class UnsortedTableOnTree : public ITable<TKey, TVal> {
private:
    struct TableItem {
        TKey key;
        TVal value;

        TableItem() : key(TKey()), value(TVal()) {}

        TableItem(const TKey& k, const TVal& v) : key(k), value(v) {}

        bool operator==(const TableItem& other) const {
            return key == other.key;
        }

        bool operator==(const TKey& k) const {
            return key == k;
        }

        friend std::ostream& operator<<(std::ostream& os, const TableItem& item) {
            os << item.key << ":" << item.value;
            return os;
        }
    };

    Tree<TableItem> data;

    // Вспомогательный метод для поиска по ключу
    TableItem* findItem(const TKey& key) {
        // Создаем временный элемент для поиска
        TableItem temp(key, TVal());
        return data.getValue(temp);
    }

    const TableItem* findItem(const TKey& key) const {
        TableItem temp(key, TVal());
        return data.getValue(temp);
    }

public:
    UnsortedTableOnTree() = default;

    UnsortedTableOnTree(const UnsortedTableOnTree& other) : data(other.data) {}

    UnsortedTableOnTree& operator=(const UnsortedTableOnTree& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    ~UnsortedTableOnTree() = default;

    bool Insert(const TKey& key, const TVal& value) override {
        TableItem* existing = findItem(key);

        if (existing) {
            // Обновляем существующее значение
            existing->value = value;
            return true;
        }
        else {
            // Вставляем новый элемент
            data.insert(TableItem(key, value));
            return true;
        }
    }

    bool Delete(const TKey& key) override {
        TableItem temp(key, TVal());
        return data.erase(temp);
    }

    bool Find(const TKey& key, TVal& value) const override {
        const TableItem* found = const_cast<UnsortedTableOnTree*>(this)->findItem(key);
        if (found) {
            value = found->value;
            return true;
        }
        return false;
    }

    bool IsEmpty() const override {
        return data.empty();
    }

    size_t Size() const override {
        return data.size();
    }

    void Clear() override {
        data.clear();
    }

    void Print() const override {
        std::cout << "\n=== UnsortedTableOnTree contents (size: " << Size() << ") ===" << std::endl;
        std::cout << "Tree structure:" << std::endl;
        data.prettyPrint();

        std::cout << "\nAll traversals:" << std::endl;
        data.printAllOrders();
        std::cout << std::endl;
    }
};