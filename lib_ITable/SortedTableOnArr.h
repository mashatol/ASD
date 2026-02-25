#ifndef SORTED_TABLE_ON_ARR_H
#define SORTED_TABLE_ON_ARR_H

#include "ITable.h"
#include "TVector.h"
#include <iostream>
#include <functional>

template <class TKey, class TVal>
class SortedTableOnArr : public ITable<TKey, TVal> {
private:
    TVector<std::pair<TKey, TVal>> _rows;
    std::function<bool(const TKey&, const TKey&)> _comparator;

    size_t binarySearch(const TKey& key, bool& found) const {
        size_t left = 0, right = _rows.Size();
        found = false;
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            if (_comparator(_rows[mid].first, key))
                left = mid + 1;
            else if (_comparator(key, _rows[mid].first))
                right = mid;
            else {
                found = true;
                return mid;
            }
        }
        return left;
    }

public:
    SortedTableOnArr() : _comparator(std::less<TKey>()) {}
    explicit SortedTableOnArr(std::function<bool(const TKey&, const TKey&)> comp) : _comparator(comp) {}
    explicit SortedTableOnArr(size_t capacity) : _rows(capacity), _comparator(std::less<TKey>()) {}

    bool Insert(const TKey& key, const TVal& value) override {
        bool found;
        size_t pos = binarySearch(key, found);
        if (found) {
            _rows[pos].second = value;
            return false;
        }
        TVector<std::pair<TKey, TVal>> newRows(_rows.Size() + 1);
        for (size_t i = 0; i < pos; ++i)
            newRows.PushBack(_rows[i]);
        newRows.PushBack(std::make_pair(key, value));
        for (size_t i = pos; i < _rows.Size(); ++i)
            newRows.PushBack(_rows[i]);
        _rows = std::move(newRows);
        return true;
    }

    bool Delete(const TKey& key) override {
        bool found;
        size_t pos = binarySearch(key, found);
        if (found) {
            _rows.Erase(pos);
            return true;
        }
        return false;
    }

    bool Find(const TKey& key, TVal& value) const override {
        bool found;
        size_t pos = binarySearch(key, found);
        if (found) {
            value = _rows[pos].second;
            return true;
        }
        return false;
    }

    bool IsEmpty() const override { return _rows.IsEmpty(); }
    size_t Size() const override { return _rows.Size(); }
    void Clear() override { _rows.Clear(); }

    void Print() const override {
        std::cout << "Sorted Table (" << Size() << " entries):\n";
        for (size_t i = 0; i < _rows.Size(); ++i)
            std::cout << "  [" << i << "] " << _rows[i].first << " : " << _rows[i].second << "\n";
    }

    const TVector<std::pair<TKey, TVal>>& GetRows() const { return _rows; }
};

#endif // SORTED_TABLE_ON_ARR_H