#include <gtest/gtest.h>
#include "List.h"
#include "Stack.h"
#include "TVector.h"
#include "Expression.h"
#include "Parser.h"
#include "Calculator.h"


TEST(ParserTest, InvalidExpression) {
    EXPECT_THROW(Parser::parse("2 + * 3"), std::runtime_error);
    EXPECT_THROW(Parser::parse("sin(x"), std::runtime_error);
}

// Тесты для преобразования в обратную польскую запись
TEST(ParserTest, ToPostfixSimple) {
    List<Lexem> infix = Parser::parse("2 + 3 * 4");
    List<Lexem> postfix = Parser::to_postfix(infix);
    EXPECT_GT(postfix.get_size(), 0);
}

TEST(ParserTest, ToPostfixWithFunctions) {
    List<Lexem> infix = Parser::parse("sin(0) + cos(1)");
    List<Lexem> postfix = Parser::to_postfix(infix);
    EXPECT_GT(postfix.get_size(), 0);
}

// Тесты для вычисления выражений
TEST(CalculatorTest, EvaluateSimple) {
    List<Lexem> infix = Parser::parse("2 + 3 * 4");
    List<Lexem> postfix = Parser::to_postfix(infix);
    double result = Parser::evaluate(postfix, {});
    EXPECT_DOUBLE_EQ(result, 14.0);
}

TEST(CalculatorTest, EvaluateWithVariables) {
    List<Lexem> infix = Parser::parse("x + y * 2");
    List<Lexem> postfix = Parser::to_postfix(infix);

    std::unordered_map<std::string, double> vars = { {"x", 5}, {"y", 3} };
    double result = Parser::evaluate(postfix, vars);
    EXPECT_DOUBLE_EQ(result, 11.0);
}

TEST(CalculatorTest, EvaluateWithFunctions) {
    List<Lexem> infix = Parser::parse("sin(0) + cos(0)");
    List<Lexem> postfix = Parser::to_postfix(infix);

    double result = Parser::evaluate(postfix, {});
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(CalculatorTest, EvaluateComplex) {
    List<Lexem> infix = Parser::parse("(x + y) * (x - y)");
    List<Lexem> postfix = Parser::to_postfix(infix);

    std::unordered_map<std::string, double> vars = { {"x", 5}, {"y", 3} };
    double result = Parser::evaluate(postfix, vars);
    EXPECT_DOUBLE_EQ(result, 16.0);
}

TEST(CalculatorTest, ExpressionClass) {
    Expression expr(1, "x + 2 * y");
    expr.set_infix_notation(Parser::parse("x + 2 * y"));
    expr.set_postfix_notation(Parser::to_postfix(expr.get_infix_notation()));

    expr.set_variable("x", 3);
    expr.set_variable("y", 4);

    double result = Parser::evaluate(expr.get_postfix_notation(), expr.get_variables());
    EXPECT_DOUBLE_EQ(result, 11.0);

    EXPECT_EQ(expr.get_id(), 1);
    EXPECT_EQ(expr.get_expression(), "x + 2 * y");
    EXPECT_TRUE(expr.has_variable("x"));
    EXPECT_FALSE(expr.has_variable("z"));
}

TEST(CalculatorTest, DivisionByZero) {
    List<Lexem> infix = Parser::parse("1 / 0");
    List<Lexem> postfix = Parser::to_postfix(infix);

    EXPECT_THROW(Parser::evaluate(postfix, {}), std::runtime_error);
}

TEST(CalculatorTest, UndefinedVariable) {
    List<Lexem> infix = Parser::parse("x + 1");
    List<Lexem> postfix = Parser::to_postfix(infix);

    EXPECT_THROW(Parser::evaluate(postfix, {}), std::runtime_error);
}

// Интеграционный тест - полный цикл
TEST(IntegrationTest, FullCalculatorWorkflow) {
    // Создаем выражение
    Expression expr(1, "a * b + sin(c)");

    // Парсим
    expr.set_infix_notation(Parser::parse(expr.get_expression()));

    // Преобразуем в обратную польскую запись
    expr.set_postfix_notation(Parser::to_postfix(expr.get_infix_notation()));

    // Задаем переменные
    expr.set_variable("a", 2);
    expr.set_variable("b", 3);
    expr.set_variable("c", 0);

    // Вычисляем
    double result = Parser::evaluate(expr.get_postfix_notation(), expr.get_variables());

    // Проверяем: 2*3 + sin(0) = 6 + 0 = 6
    EXPECT_DOUBLE_EQ(result, 6.0);
}

TEST(IntegrationTest, ComplexExpression) {
    List<Lexem> infix = Parser::parse("(sin(x) + cos(y)) * 2");
    List<Lexem> postfix = Parser::to_postfix(infix);

    std::unordered_map<std::string, double> vars = { {"x", 0}, {"y", 0} };
    double result = Parser::evaluate(postfix, vars);

    // (sin(0) + cos(0)) * 2 = (0 + 1) * 2 = 2
    EXPECT_DOUBLE_EQ(result, 2.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}