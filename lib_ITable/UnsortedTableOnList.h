#pragma once
#include "itable.h" // Подключаем интерфейс
#include "List.h"
#include <iostream>

// Неупорядоченная таблица на списке
template<typename TKey, typename TVal>
class UnsortedTableOnList : public ITable<TKey, TVal> {
private:
    // Структура для хранения пары ключ-значение
    struct TableItem {
        TKey key;
        TVal value;

        TableItem(const TKey& k, const TVal& v) : key(k), value(v) {}
    };

    List<TableItem> data; // Хранилище данных

public:
    // Конструкторы
    UnsortedTableOnList() = default;

    UnsortedTableOnList(const UnsortedTableOnList& other) : data(other.data) {}

    UnsortedTableOnList& operator=(const UnsortedTableOnList& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Деструктор
    ~UnsortedTableOnList() = default;

    // Реализация методов интерфейса ITable
    bool Insert(const TKey& key, const TVal& value) override {
        // Проверяем, существует ли уже такой ключ
        for (auto& item : data) {
            if (item.key == key) {
                item.value = value; // Обновляем значение
                return true; // Вставка/обновление успешно
            }
        }
        // Если ключ не найден, добавляем новый элемент
        data.push_back(TableItem(key, value));
        return true;
    }

    bool Delete(const TKey& key) override {
        if (data.empty()) return false;

        // Удаление первого элемента
        if (data.begin().get_node()->value.key == key) {
            data.pop_front();
            return true;
        }

        // Поиск элемента для удаления
        auto prev = data.begin();
        auto curr = prev;
        ++curr;

        while (curr != data.end()) {
            if (curr.get_node()->value.key == key) {
                // Удаляем текущий элемент через новый метод erase_after
                data.erase_after(prev.get_node());
                return true;
            }
            ++prev;
            ++curr;
        }

        return false; // Ключ не найден
    }

    bool Find(const TKey& key, TVal& value) const override {
        for (const auto& item : data) {
            if (item.key == key) {
                value = item.value;
                return true;
            }
        }
        return false; // Ключ не найден
    }

    bool IsEmpty() const override {
        return data.empty();
    }

    size_t Size() const override {
        return data.get_size();
    }

    void Clear() override {
        data.clear();
    }

    void Print() const override {
        std::cout << "UnsortedTableOnList contents (" << Size() << " items):" << std::endl;
        for (const auto& item : data) {
            std::cout << "  " << item.key << " -> " << item.value << std::endl;
        }
    }
};