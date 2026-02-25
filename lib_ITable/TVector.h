#ifndef TVECTOR_H
#define TVECTOR_H

#include <stdexcept>
#include <algorithm>

template <class T>
class TVector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i)
            new_data[i] = std::move(_data[i]);
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    TVector() : _data(nullptr), _size(0), _capacity(0) {}
    explicit TVector(size_t capacity) : _size(0), _capacity(capacity) {
        _data = new T[_capacity];
    }
    ~TVector() { delete[] _data; }

    TVector(const TVector& other) : _size(other._size), _capacity(other._capacity) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }

    TVector& operator=(const TVector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i)
                _data[i] = other._data[i];
        }
        return *this;
    }

    TVector(TVector&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    TVector& operator=(TVector&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return _data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return _data[index];
    }

    void PushBack(const T& value) {
        if (_size >= _capacity) {
            size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
            resize(new_capacity);
        }
        _data[_size++] = value;
    }

    void PushBack(T&& value) {
        if (_size >= _capacity) {
            size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
            resize(new_capacity);
        }
        _data[_size++] = std::move(value);
    }

    void Erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < _size - 1; ++i)
            _data[i] = std::move(_data[i + 1]);
        --_size;
    }

    size_t Find(const T& value) const {
        for (size_t i = 0; i < _size; ++i)
            if (_data[i] == value) return i;
        return _size;
    }

    size_t Size() const { return _size; }
    size_t Capacity() const { return _capacity; }
    bool IsEmpty() const { return _size == 0; }
    void Clear() { _size = 0; }

    T* begin() { return _data; }
    T* end() { return _data + _size; }
    const T* begin() const { return _data; }
    const T* end() const { return _data + _size; }
};

#endif // TVECTOR_H