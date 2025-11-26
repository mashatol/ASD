#pragma once
#include <string>
#include <cmath>
#include <functional>

enum class TypeLexem {
    Constant, Variable, OpenBracket, CloseBracket,
    Function, Operator
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    std::function<double(double)> function;

    Lexem(const std::string& _name = "", TypeLexem _type = TypeLexem::Variable,
        double _value = 0.0, int _priority = -1,
        std::function<double(double)> _function = nullptr)
        : name(_name), type(_type), value(_value),
        priority(_priority), function(_function) {
    }
};

namespace MathFunctions {
    double my_sin(double x);
    double my_cos(double x);
    double my_tg(double x);
    double my_ln(double x);
    double my_exp(double x);
    double my_abs(double x);
}