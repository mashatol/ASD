#pragma once
#include "TVector.h"
#include "Expression.h"
#include "Parser.h"
#include <iostream>
#include <string>

class Calculator {
private:
    TVector<Expression> expressions;
    int next_id;

public:
    Calculator() : next_id(1), expressions(TVector<Expression>()) {}

    void run();
private:
    void show_menu();
    void create_expression();
    void delete_expression();
    void set_variables();
    void evaluate_expression();
    void show_expressions();
    int get_choice();
    void add_expression(const Expression& expr);
};