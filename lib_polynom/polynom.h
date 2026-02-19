#pragma once
#include "monom.h"
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

class Polynom {
private:
    std::list<Monom> monoms;

    void sortAndCombine();
    void addMonom(const Monom& m);

public:
    // Конструкторы
    Polynom();
    Polynom(const std::string& str);
    Polynom(const char* str);
    Polynom(const Polynom& other);
    ~Polynom() = default;

    // Оператор присваивания
    Polynom& operator=(const Polynom& other);

    // Арифметические операции
    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator*(double scalar) const;
    Polynom operator/(double scalar) const;
    Polynom operator-() const;

    // Операторы с присваиванием
    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(double scalar);
    Polynom& operator/=(double scalar);

    // Операторы сравнения
    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    // Вычисление значения
    double evaluate(double x, double y, double z) const;

    // Итераторы
    using iterator = std::list<Monom>::iterator;
    using const_iterator = std::list<Monom>::const_iterator;

    iterator begin() { return monoms.begin(); }
    iterator end() { return monoms.end(); }
    const_iterator begin() const { return monoms.begin(); }
    const_iterator end() const { return monoms.end(); }

    // Вспомогательные методы
    bool isEmpty() const { return monoms.empty(); }
    size_t getSize() const { return monoms.size(); }
    void clear() { monoms.clear(); }

    // Дружественные операторы
    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);
};

// Дружественные операторы для констант
Polynom operator*(double scalar, const Polynom& p);