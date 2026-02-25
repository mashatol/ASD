#ifndef TABLE_H
#define TABLE_H

#include <vector>

template <class TKey, class TVal>
class ITable {
public:
    virtual ~ITable() = default;

    virtual bool Insert(const TKey& key, const TVal& value) = 0;
    virtual bool Delete(const TKey& key) = 0;
    virtual bool Find(const TKey& key, TVal& value) const = 0; // true если найден, value заполняется

    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    virtual void Clear() = 0;

    virtual void Print() const = 0;
};

#endif // TABLE_H