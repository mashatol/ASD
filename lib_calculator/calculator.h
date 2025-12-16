#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Expression.h"
#include "TVector.h"
#include <string>

class Calculator {
    TVector<Expression> exprs;
    int nextId;

    void showAll() const;
    void createExpr();
    void deleteExpr();
    void setVars();
    void evalExpr();

public:
    Calculator() : nextId(1) {}
    void run();
};

#endif