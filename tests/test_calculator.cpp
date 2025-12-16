#include <gtest/gtest.h>
#include "Parser.h"
#include "Expression.h"
#include "Calculator.h"

TEST(ParserTest, ParseNumbers) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("5"), 5);
    EXPECT_DOUBLE_EQ(p.calculate("3.14"), 3.14);
    EXPECT_DOUBLE_EQ(p.calculate("0"), 0);
    EXPECT_DOUBLE_EQ(p.calculate("-0"), 0);
}

TEST(ParserTest, ParseOperators) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("2+2"), 4);
    EXPECT_DOUBLE_EQ(p.calculate("5-3"), 2);
    EXPECT_DOUBLE_EQ(p.calculate("4*3"), 12);
    EXPECT_DOUBLE_EQ(p.calculate("10/2"), 5);
    EXPECT_DOUBLE_EQ(p.calculate("2^3"), 8);
    EXPECT_DOUBLE_EQ(p.calculate("10%3"), 1);
}

TEST(ParserTest, ParseUnaryMinus) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("-5"), -5);
    EXPECT_DOUBLE_EQ(p.calculate("3+(-2)"), 1);
    EXPECT_DOUBLE_EQ(p.calculate("-(-5)"), 5);
    EXPECT_DOUBLE_EQ(p.calculate("-(2+3)"), -5);
}

TEST(ParserTest, ParseFunctions) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("sin(0)"), 0);
    EXPECT_DOUBLE_EQ(p.calculate("cos(0)"), 1);
    EXPECT_DOUBLE_EQ(p.calculate("tan(0)"), 0);
    EXPECT_DOUBLE_EQ(p.calculate("sqrt(4)"), 2);
    EXPECT_DOUBLE_EQ(p.calculate("abs(-5)"), 5);
    EXPECT_DOUBLE_EQ(p.calculate("log(100)"), 2);
}

TEST(ParserTest, ParseBrackets) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("(2+3)*4"), 20);
    EXPECT_DOUBLE_EQ(p.calculate("2*(3+4)"), 14);
    EXPECT_DOUBLE_EQ(p.calculate("((2+3)*4)/2"), 10);
    EXPECT_DOUBLE_EQ(p.calculate("2^(1+2)"), 8);
}

TEST(ParserTest, ParseComplexExpression) {
    Parser p;
    EXPECT_DOUBLE_EQ(p.calculate("2+3*4"), 14);
    EXPECT_DOUBLE_EQ(p.calculate("(2+3)*4^2"), 80);
    EXPECT_DOUBLE_EQ(p.calculate("sin(0)+cos(0)*2"), 2);
    EXPECT_DOUBLE_EQ(p.calculate("sqrt(9)*2+1"), 7);
}

TEST(ParserTest, ParseErrors) {
    Parser p;
    EXPECT_THROW(p.calculate("2+"), std::runtime_error);
    EXPECT_THROW(p.calculate("(2+3"), std::runtime_error);
    EXPECT_THROW(p.calculate("2++3"), std::runtime_error);
    EXPECT_THROW(p.calculate("sin"), std::runtime_error);
    EXPECT_THROW(p.calculate("sqrt(-1)"), std::runtime_error);
    EXPECT_THROW(p.calculate("10/0"), std::runtime_error);
}

TEST(ParserTest, ParseVariables) {
    Parser p;
    std::map<std::string, double> vars = { {"x", 5}, {"y", 3} };
    EXPECT_DOUBLE_EQ(p.calculate("x+y", vars), 8);
    EXPECT_DOUBLE_EQ(p.calculate("x*y", vars), 15);
    EXPECT_DOUBLE_EQ(p.calculate("x^y", vars), 125);
}

TEST(ParserTest, Validate) {
    EXPECT_TRUE(Parser::validate("2+2"));
    EXPECT_TRUE(Parser::validate("sin(3.14)"));
    EXPECT_TRUE(Parser::validate("x+y"));
    EXPECT_FALSE(Parser::validate("2+"));
    EXPECT_FALSE(Parser::validate("(2+3"));
    EXPECT_FALSE(Parser::validate("2**3"));
}

#include <gtest/gtest.h>
#include "Expression.h"
#include "Parser.h"
#include <unordered_map>

using namespace std;

TEST(ExpressionTest, Construction) {
    // Нормальное выражение
    EXPECT_NO_THROW(Expression(1, "2+2"));
    EXPECT_NO_THROW(Expression(2, "x+y"));

    // Пустое выражение
    EXPECT_NO_THROW(Expression(3, ""));

    // Некорректное выражение
    EXPECT_THROW(Expression(4, "2+"), runtime_error);
    EXPECT_THROW(Expression(5, "sin("), runtime_error);
}

TEST(ExpressionTest, Variables) {
    Expression expr(1, "x + y * z");

    // Установка переменных
    expr.setVariable("x", 2);
    expr.setVariable("y", 3);
    expr.setVariable("z", 4);

    // Вычисление с установленными переменными
    EXPECT_DOUBLE_EQ(expr.evaluate({}), 14);

    // Очистка переменных
    expr.clearVariables();

    // Вычисление с передачей переменных как параметров
    unordered_map<string, double> vars = { {"x", 2}, {"y", 3}, {"z", 4} };
    EXPECT_DOUBLE_EQ(expr.evaluate(vars), 14);
}

TEST(ExpressionTest, EvaluateSimple) {
    Expression expr(1, "2 + 3 * 4");
    EXPECT_DOUBLE_EQ(expr.evaluate({}), 14);

    Expression expr2(2, "(2+3)*4");
    EXPECT_DOUBLE_EQ(expr2.evaluate({}), 20);

    Expression expr3(3, "10 / 2");
    EXPECT_DOUBLE_EQ(expr3.evaluate({}), 5);

    Expression expr4(4, "2 ^ 3");
    EXPECT_DOUBLE_EQ(expr4.evaluate({}), 8);
}

TEST(ExpressionTest, EvaluateWithVariables) {
    Expression expr(1, "a + b * c");

    unordered_map<string, double> vars = {
        {"a", 2},
        {"b", 3},
        {"c", 4}
    };

    EXPECT_DOUBLE_EQ(expr.evaluate(vars), 14);

    // Частичная передача переменных
    expr.setVariable("a", 5);
    unordered_map<string, double> partialVars = { {"b", 3}, {"c", 4} };
    EXPECT_DOUBLE_EQ(expr.evaluate(partialVars), 17);
}

TEST(ExpressionTest, EvaluateFunctions) {
    // Проверка функций
    Expression expr1(1, "sin(0)");
    EXPECT_DOUBLE_EQ(expr1.evaluate({}), 0);

    Expression expr2(2, "cos(0)");
    EXPECT_DOUBLE_EQ(expr2.evaluate({}), 1);

    Expression expr3(3, "sqrt(4)");
    EXPECT_DOUBLE_EQ(expr3.evaluate({}), 2);

    Expression expr4(4, "abs(-5)");
    EXPECT_DOUBLE_EQ(expr4.evaluate({}), 5);
}

TEST(ExpressionTest, EvaluateComplex) {
    Expression expr1(1, "sin(0) + cos(0) * 2");
    EXPECT_DOUBLE_EQ(expr1.evaluate({}), 2);

    Expression expr2(2, "sqrt(9) * 2 + 1");
    EXPECT_DOUBLE_EQ(expr2.evaluate({}), 7);

    Expression expr3(3, "2 ^ 3 * 4 - 5 / 2");
    EXPECT_DOUBLE_EQ(expr3.evaluate({}), 29.5);
}

TEST(ExpressionTest, SetExpression) {
    Expression expr(1, "2+2");
    EXPECT_DOUBLE_EQ(expr.evaluate({}), 4);

    // Изменение выражения
    expr.setExpression("3*4");
    EXPECT_DOUBLE_EQ(expr.evaluate({}), 12);

    // Очистка выражения
    expr.setExpression("");
    EXPECT_FALSE(expr.isParsed());
    EXPECT_THROW(expr.evaluate({}), runtime_error);

    // Установка нового выражения с переменными
    expr.setExpression("x + y");
    unordered_map<string, double> vars = { {"x", 5}, {"y", 3} };
    EXPECT_DOUBLE_EQ(expr.evaluate(vars), 8);
}

TEST(ExpressionTest, ErrorHandling) {
    Expression expr(1, "2+2");

    // Корректное вычисление
    EXPECT_NO_THROW(expr.evaluate({}));

    // Деление на ноль
    expr.setExpression("5 / 0");
    EXPECT_THROW(expr.evaluate({}), runtime_error);

    // Неопределенная переменная
    expr.setExpression("x + y");
    EXPECT_THROW(expr.evaluate({}), runtime_error);

}

TEST(ExpressionTest, UnaryMinus) {
    Expression expr1(1, "-5");
    EXPECT_DOUBLE_EQ(expr1.evaluate({}), -5);

    Expression expr2(2, "3 + (-2)");
    EXPECT_DOUBLE_EQ(expr2.evaluate({}), 1);

    Expression expr3(3, "-(2+3)");
    EXPECT_DOUBLE_EQ(expr3.evaluate({}), -5);

    Expression expr4(4, "-x");
    expr4.setVariable("x", 5);
    EXPECT_DOUBLE_EQ(expr4.evaluate({}), -5);
}

TEST(ExpressionTest, FunctionComposition) {
    Expression expr1(1, "sin(cos(0))");
    EXPECT_DOUBLE_EQ(expr1.evaluate({}), sin(cos(0)));

    Expression expr2(2, "sqrt(abs(-16))");
    EXPECT_DOUBLE_EQ(expr2.evaluate({}), 4);

    Expression expr3(3, "sin(x)^2 + cos(x)^2");
    unordered_map<string, double> vars = { {"x", 1.5} };
    EXPECT_NEAR(expr3.evaluate(vars), 1.0, 1e-10);
}

TEST(ExpressionTest, MixedOperations) {
    Expression expr1(1, "2 * x + 3 * y - z");
    unordered_map<string, double> vars = { {"x", 2}, {"y", 3}, {"z", 4} };
    EXPECT_DOUBLE_EQ(expr1.evaluate(vars), 9);

    Expression expr2(2, "(a + b) * (c - d) / e");
    unordered_map<string, double> vars2 = {
        {"a", 2}, {"b", 3}, {"c", 10}, {"d", 2}, {"e", 4}
    };
    EXPECT_DOUBLE_EQ(expr2.evaluate(vars2), 10);
}

TEST(ExpressionTest, VariableManagement) {
    Expression expr(1, "x + y + z");

    // Проверка начального состояния
    EXPECT_EQ(expr.getVariableCount(), 3);

    // Установка переменных по одной
    expr.setVariable("x", 1);
    expr.setVariable("y", 2);
    expr.setVariable("z", 3);

    EXPECT_DOUBLE_EQ(expr.evaluate({}), 6);

    // Перезапись переменной
    expr.setVariable("x", 10);
    EXPECT_DOUBLE_EQ(expr.evaluate({}), 15);

    // Очистка и использование external переменных
    expr.clearVariables();
    unordered_map<string, double> extVars = { {"x", 5}, {"y", 6}, {"z", 7} };
    EXPECT_DOUBLE_EQ(expr.evaluate(extVars), 18);

    // Смешанный подход
    expr.setVariable("x", 1);
    unordered_map<string, double> partialVars = { {"y", 2}, {"z", 3} };
    EXPECT_DOUBLE_EQ(expr.evaluate(partialVars), 6);
}