#ifndef UNSORTED_TABLE_ON_ARR_H
#define UNSORTED_TABLE_ON_ARR_H

#include "ITable.h"
#include "TVector.h"
#include <iostream>

template <class TKey, class TVal>
class UnsortedTableOnArr : public ITable<TKey, TVal> {
private:
    TVector<std::pair<TKey, TVal>> _rows;

    size_t findIndex(const TKey& key) const {
        for (size_t i = 0; i < _rows.Size(); ++i)
            if (_rows[i].first == key)
                return i;
        return _rows.Size();
    }

public:
    UnsortedTableOnArr() = default;
    explicit UnsortedTableOnArr(size_t capacity) : _rows(capacity) {}

    bool Insert(const TKey& key, const TVal& value) override {
        size_t idx = findIndex(key);
        if (idx < _rows.Size()) {
            _rows[idx].second = value;
            return false; // обновление
        }
        _rows.PushBack(std::make_pair(key, value));
        return true; // новая запись
    }

    bool Delete(const TKey& key) override {
        size_t idx = findIndex(key);
        if (idx < _rows.Size()) {
            _rows.Erase(idx);
            return true;
        }
        return false;
    }

    bool Find(const TKey& key, TVal& value) const override {
        size_t idx = findIndex(key);
        if (idx < _rows.Size()) {
            value = _rows[idx].second;
            return true;
        }
        return false;
    }

    bool IsEmpty() const override { return _rows.IsEmpty(); }
    size_t Size() const override { return _rows.Size(); }
    void Clear() override { _rows.Clear(); }

    void Print() const override {
        std::cout << "Unsorted Table (" << Size() << " entries):\n";
        for (size_t i = 0; i < _rows.Size(); ++i)
            std::cout << "  [" << i << "] " << _rows[i].first << " : " << _rows[i].second << "\n";
    }

    const TVector<std::pair<TKey, TVal>>& GetRows() const { return _rows; }
};

#endif // UNSORTED_TABLE_ON_ARR_H