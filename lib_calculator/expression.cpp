#include "Expression.h"
#include "Parser.h"
#include "stack.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace std;

Expression::Expression(int _id, const string& expr) : id(_id), exprStr(expr), parsed(false) {
    if (!expr.empty()) parse();
}
void Expression::parse() {
    try {
        // Вместо Parser::parse(exprStr) - создаем объект Parser
        Parser parser;

        // Парсим выражение для валидации
        parser.calculate(exprStr);

        // Для RPN нужно либо:
        // 1. Переделать Parser чтобы он возвращал RPN
        // 2. Убрать RPN и вычислять через Parser напрямую
        // 3. Или сделать так:

        // Если нужно сохранить RPN - создаем простую реализацию
        // Но для начала просто проверяем парсинг
        parsed = true;

        // Простая логика для извлечения переменных (если нужно)
        // Можно парсить вручную для поиска переменных
        for (size_t i = 0; i < exprStr.length(); i++) {
            if (isalpha(exprStr[i])) {
                size_t start = i;
                while (i < exprStr.length() && (isalnum(exprStr[i]) || exprStr[i] == '_')) {
                    i++;
                }
                string varName = exprStr.substr(start, i - start);
                vars[varName] = 0.0;
                i--; // компенсируем инкремент в цикле while
            }
        }

    }
    catch (const exception& e) {
        parsed = false;
        throw runtime_error("Parse error: " + string(e.what()));
    }
}

double Expression::evaluate(const unordered_map<string, double>& extraVars) {
    if (!parsed) throw runtime_error("Not parsed");

    // Создаем Parser
    Parser parser;

    // Конвертируем unordered_map в map (если Parser использует map)
    map<string, double> allVars;

    // Копируем vars (внутренние переменные)
    for (const auto& v : vars) {
        allVars[v.first] = v.second;
    }

    // Добавляем/перезаписываем extraVars
    for (const auto& v : extraVars) {
        allVars[v.first] = v.second;
    }

    try {
        // Попробуй разные варианты вызова:

        // Вариант 1: С двумя параметрами
        return parser.calculate(exprStr, allVars);

        // ИЛИ Вариант 2: Сначала установить переменные, потом вычислить
        // parser.setVariables(allVars);
        // return parser.calculate(exprStr);

        // ИЛИ Вариант 3: Другой метод
        // return parser.evaluate(exprStr, allVars);
    }
    catch (const exception& e) {
        throw runtime_error("Evaluation error: " + string(e.what()));
    }
}
void Expression::setExpression(const string& expr) {
    exprStr = expr;
    if (!expr.empty()) parse();
    else { parsed = false; infix.clear(); rpn.clear(); vars.clear(); }
}

void Expression::setVariable(const string& name, double value) {
    vars[name] = value;
}

void Expression::clearVariables() {
    vars.clear();
}