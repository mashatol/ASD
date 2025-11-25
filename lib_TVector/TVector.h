#pragma once 
#define STEP_OF_CAPACITY 15 

#include <iostream> 


template <typename T>
class TVector {
    T* _data; // указатель на массив элементов
    int _size;
    int _capacity;
public:
    TVector();
    TVector(int size);
    TVector(const TVector<T>& other); // конструктор копирования
    TVector(std::initializer_list<T> data); // конструктора из списка инициализации - позволяет создавать вектор с помощью синтаксиса фигурных скобок: TVector<int> v{1, 2, 3};

    ~TVector();

    inline T& front(); // код метода непосредственно в место вызова
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;
    inline T* data() const noexcept;
    inline int size() const noexcept;
    inline int capacity() const noexcept; // гарантирует, что метод не выбрасывает исключений

    inline TVector<T>& operator=(const TVector<T>& other);

    inline T& operator[](int indx) noexcept;
    inline const T& operator[](int indx) const noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& ostr, TVector<U>& v);

    template<typename U>
    friend std::istream& operator>>(std::istream& istr, TVector<U>& v);
};

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
TVector<T>::TVector(std::initializer_list<T> data) { // массивы с опр типом данных
    _size = static_cast<int>(data.size());
    _capacity = (_size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;  // Теперь используем _size
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = *(data.begin() + i);
    }
}

template <typename T>
TVector<T>:: ~TVector() {
    if (_data != nullptr) {
        delete[] _data;
    }
}

template <typename T>
inline T& TVector<T>::front() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
inline T& TVector<T>::back() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
inline const T& TVector<T>::front() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
inline const T& TVector<T>::back() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
inline T* TVector<T>::data() const noexcept {
    return _data;
}

template <typename T>
inline int TVector<T>::size() const noexcept {
    return _size;
}

template <typename T>
inline int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
inline TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this; // возвращаем ссылку на текущий объект (для цепочек: a = b = c)
}

template <typename T>
inline T& TVector<T>::operator[](int indx) noexcept {
    return _data[indx];
}

template <typename T>
inline const T& TVector<T>::operator[](int indx) const noexcept {
    return _data[indx];
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, TVector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << ' ';
    return ostr; // возвращаем поток
}

template <typename T>
std::istream& operator>>(std::istream& istr, TVector<T>& v)
{
    for (int i = 0; i < v.size(); i++)
        istr >> v[i];
    return istr;
}