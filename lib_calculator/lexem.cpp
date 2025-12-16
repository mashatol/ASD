#include "Lexem.h"

// Конструктор по умолчанию
Lexem::Lexem() : name(""), type(Constant), value(0.0), priority(-1), function(nullptr) {}

// Конструктор для констант, переменных, скобок
Lexem::Lexem(std::string _name, TypeLexem _type)
    : name(_name), type(_type), value(0.0), priority(-1), function(nullptr) {
}

// Конструктор для чисел
Lexem::Lexem(double val)
    : name(""), type(Constant), value(val), priority(-1), function(nullptr) {
}

// Конструктор для операторов
Lexem::Lexem(std::string _name, TypeLexem _type, int _priority)
    : name(_name), type(_type), value(0.0), priority(_priority), function(nullptr) {
}

// Конструктор для функций
Lexem::Lexem(std::string _name, std::function<double(double)> func)
    : name(_name), type(Function), value(0.0), priority(4), function(func) {
}

bool Lexem::isOperator() const {
    return type == Operator || type == UnOperator;
}

bool Lexem::isFunction() const {
    return type == Function;
}

bool Lexem::isBracket() const {
    return type == OpenBracket || type == CloseBracket;
}

bool Lexem::isAbs() const {
    return type == OpenedAbs || type == ClosedAbs;
}