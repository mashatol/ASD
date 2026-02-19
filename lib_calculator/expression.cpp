//#include "Expression.h"
//#include "Parser.h"
//#include "stack.h"
//#include <stdexcept>
//#include <cmath>
//#include <iostream>
//
//using namespace std;
//
//Expression::Expression(int _id, const string& expr)
//    : id(_id), exprStr(expr), parsed(false) {
//    if (!expr.empty()) {
//        parse();
//    }
//}
//
//void Expression::parse() {
//    infix.clear();
//    rpn.clear();
//    vars.clear();
//    parsed = false;
//
//    if (exprStr.empty()) {
//        return;  // Пустое выражение - не ошибка
//    }
//
//    try {
//        infix = Parser::parse(exprStr);
//
//        if (infix.empty()) {
//            throw runtime_error("Empty expression after parsing");
//        }
//
//        rpn = Parser::toRPN(infix);
//        extractVariables();
//        parsed = true;
//
//    }
//    catch (const exception& e) {
//        infix.clear();
//        rpn.clear();
//        vars.clear();
//        parsed = false;
//
//        throw runtime_error("Parse error in expression '" + exprStr + "': " + e.what());
//    }
//}
//
//void Expression::extractVariables() { // автоматическое управление переменными
//    vars.clear();
//
//    for (List<Lexem>::ConstIterator it = infix.cbegin(); it != infix.cend(); ++it) {
//        if (it->type == Variable) {
//            vars[it->name] = 0.0; // добавляет или обновляет запись в unordered_map (ключ - значение)
//        }
//    }
//}
//
//void Expression::setExpression(const string& expr) {
//    exprStr = expr;
//    if (!expr.empty()) {
//        parse();  
//    }
//    else {
//        infix.clear();
//        rpn.clear();
//        vars.clear();
//        parsed = false;
//    }
//}
//
//double Expression::evaluate(const unordered_map<string, double>& extraVars) {
//    if (!parsed) {
//        throw runtime_error("Cannot evaluate: expression is not parsed");
//    }
//
//    unordered_map<string, double> allVars = vars; // новый список с основными переменными
//
//    for (unordered_map<string, double>::const_iterator var_it = extraVars.begin(); // объединяет доп переменные с основными
//        var_it != extraVars.end(); ++var_it) {
//        allVars[var_it->first] = var_it->second;
//        // Если ключ есть - значение перезаписывается
//        // Если ключа нет - создается новая пара
//    }
//
//    Stack<double> stack(100);
//
//    for (List<Lexem>::Iterator it = rpn.begin(); it != rpn.end(); ++it) {
//        const Lexem& lex = *it;
//
//        switch (lex.type) {
//        case Constant:
//            stack.push(lex.value);
//            break;
//
//        case Variable: {
//            unordered_map<string, double>::iterator varIt = allVars.find(lex.name);
//            if (varIt == allVars.end()) {
//                throw runtime_error("Variable '" + lex.name + "' is not defined");
//            }
//            stack.push(varIt->second);
//            break;
//        }
//
//        case Operator: {
//            if (stack.count() < 2) {
//                throw runtime_error("Not enough operands for operator '" + lex.name + "'");
//            }
//
//            double b = stack.top();
//            stack.pop();
//            double a = stack.top();
//            stack.pop();
//            double result;
//
//            if (lex.name == "+") {
//                result = a + b;
//            }
//            else if (lex.name == "-") {
//                result = a - b;
//            }
//            else if (lex.name == "*") {
//                result = a * b;
//            }
//            else if (lex.name == "/") {
//                if (b == 0.0) {
//                    throw runtime_error("Division by zero");
//                }
//                result = a / b;
//            }
//            else if (lex.name == "^") {
//                result = pow(a, b);
//            }
//            else {
//                throw runtime_error("Unknown operator: '" + lex.name + "'");
//            }
//
//            stack.push(result);
//            break;
//        }
//
//        case UnOperator: {
//            if (stack.count() < 1) {
//                throw runtime_error("Not enough operands for unary operator");
//            }
//
//            double a = stack.top(); stack.pop();
//            double result;
//
//            if (lex.name == "u-") {
//                result = -a;
//            }
//            else {
//                throw runtime_error("Unknown unary operator: '" + lex.name + "'");
//            }
//
//            stack.push(result);
//            break;
//        }
//
//        case Function: {
//            if (stack.count() < 1) {
//                throw runtime_error("Not enough arguments for function '" + lex.name + "'");
//            }
//
//            double arg = stack.top(); 
//            stack.pop();
//
//            if (!lex.function) { // если у лексемы не установлена функция
//                throw runtime_error("Function '" + lex.name + "' is not implemented");
//            }
//
//            double result = lex.function(arg);
//            stack.push(result);
//            break;
//        }
//
//        default:
//            throw runtime_error("Unexpected lexem type in RPN");
//        }
//    }
//
//    if (stack.count() != 1) {
//        throw runtime_error("Invalid expression format");
//    }
//
//    return stack.top();
//}
//
//void Expression::setVariable(const string& name, double value) {
//    bool isNew = (vars.find(name) == vars.end());  // проверяем
//    vars[name] = value;  // устанавливаем
//
//    if (isNew) {
//        cout << "Added new variable : " << name << " = " << value << endl;
//    }
//    else {
//        cout << "An existing variable has been changed: " << name << " = " << value << endl;
//    }
//}
//void Expression::clearVariables() {
//    for (unordered_map<string, double>::iterator it = vars.begin();it != vars.end(); ++it) 
//    {
//        it->second = 0.0;
//    }
//}