#pragma once 
#define STEP_OF_CAPACITY 15 

#include <iostream>
#include <stdexcept>

template <typename T>
class TVector {
    T* _data; // указатель на массив элементов
    int _size;
    int _capacity;

    void resize(int new_capacity);

public:
    TVector();
    TVector(int size);
    TVector(const TVector<T>& other); // конструктор копирования
    TVector(std::initializer_list<T> data); // конструктора из списка инициализации

    ~TVector();

    inline T& front(); 
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;
    inline T* data() const noexcept;
    inline int size() const noexcept;
    inline int capacity() const noexcept; 

    inline TVector<T>& operator=(const TVector<T>& other);

    inline T& operator[](int indx);
    inline const T& operator[](int indx) const;

  
    void push(const T& value);
    void pop();
    void clear();
    bool empty() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& ostr, TVector<U>& v);

    template<typename U>
    friend std::istream& operator>>(std::istream& istr, TVector<U>& v);
};


template <typename T>
void TVector<T>::resize(int new_capacity) {
    T* new_data = new T[new_capacity];
    for (int i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

template <typename T>
void TVector<T>::push(const T& value) {
    if (_size == _capacity) {
        int new_capacity = (_capacity == 0) ? STEP_OF_CAPACITY : _capacity + STEP_OF_CAPACITY;
        resize(new_capacity);
    }
    _data[_size] = value;
    _size++;
}

template <typename T>
void TVector<T>::pop() {
    if (_size == 0) {
        throw std::out_of_range("pop from empty TVector");
    }
    _size--;
}

template <typename T>
void TVector<T>::clear() {
    _size = 0;
}

template <typename T>
bool TVector<T>::empty() const {
    return _size == 0;
}

template <typename T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(0) {}

template <typename T>
TVector<T>::TVector(int size) {
    _capacity = (size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _size = size;
    _data = new T[_capacity];
    for (int i = 0; i < size; i++) {
        _data[i] = T();
    }
}

template <typename T>
TVector<T>::TVector(const TVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template <typename T>
TVector<T>::TVector(std::initializer_list<T> data) {
    _size = static_cast<int>(data.size());
    _capacity = (_size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    int i = 0;
    for (const auto& item : data) {
        _data[i++] = item;
    }
}

template <typename T>
TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
    }
}

template <typename T>
T& TVector<T>::front() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
T& TVector<T>::back() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
const T& TVector<T>::front() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
const T& TVector<T>::back() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
T* TVector<T>::data() const noexcept {
    return _data;
}

template <typename T>
int TVector<T>::size() const noexcept {
    return _size;
}

template <typename T>
int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <typename T>
T& TVector<T>::operator[](int indx) {
    if (indx < 0 || indx >= _size) {
        throw std::out_of_range("TVector index out of range");
    }
    return _data[indx];
}

template <typename T>
const T& TVector<T>::operator[](int indx) const {
    if (indx < 0 || indx >= _size) {
        throw std::out_of_range("TVector index out of range");
    }
    return _data[indx];
}

// Дружественные функции
template <typename T>
std::ostream& operator<<(std::ostream& ostr, TVector<T>& v) {
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << ' ';
    return ostr;
}

template <typename T>
std::istream& operator>>(std::istream& istr, TVector<T>& v) {
    for (int i = 0; i < v.size(); i++)
        istr >> v[i];
    return istr;
}

