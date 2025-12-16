#ifndef LEXEM_H
#define LEXEM_H

#include <string>
#include <functional>

enum TypeLexem {
    Constant,
    Variable,
    OpenBracket,
    CloseBracket,
    Function,
    Operator,
    UnOperator,
    OpenedAbs,
    ClosedAbs
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    std::function<double(double)> function;

    // Конструкторы
    Lexem();
    Lexem(std::string _name, TypeLexem _type);
    Lexem(double val);
    Lexem(std::string _name, TypeLexem _type, int _priority);
    Lexem(std::string _name, std::function<double(double)> func);

    // Методы
    bool isOperator() const;
    bool isFunction() const;
    bool isBracket() const;
    bool isAbs() const;
};

#endif