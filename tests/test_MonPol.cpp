#include <gtest/gtest.h>
#include "polynom.h"

// Тесты для класса Monom
TEST(MonomTest, DefaultConstructor) {
    Monom m;
    EXPECT_EQ(m.getCoef(), 0);
    EXPECT_EQ(m.getPx(), 0);
    EXPECT_EQ(m.getPy(), 0);
    EXPECT_EQ(m.getPz(), 0);
    EXPECT_TRUE(m.isZero());
}

TEST(MonomTest, ParameterConstructor) {
    Monom m(2.5, 1, 2, 3);
    EXPECT_DOUBLE_EQ(m.getCoef(), 2.5);
    EXPECT_EQ(m.getPx(), 1);
    EXPECT_EQ(m.getPy(), 2);
    EXPECT_EQ(m.getPz(), 3);
    EXPECT_FALSE(m.isZero());
}

TEST(MonomTest, CopyConstructor) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(m1);
    EXPECT_EQ(m2, m1);
}

TEST(MonomTest, Similarity) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);
    Monom m3(1.0, 2, 2, 3);

    EXPECT_TRUE(m1.isSimilar(m2));
    EXPECT_FALSE(m1.isSimilar(m3));
}

TEST(MonomTest, Comparison) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(2.5, 1, 2, 3);
    Monom m3(3.0, 1, 2, 3);

    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);
}

TEST(MonomTest, Addition) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);
    Monom result = m1 + m2;

    EXPECT_DOUBLE_EQ(result.getCoef(), 5.5);
    EXPECT_EQ(result.getPx(), 1);
    EXPECT_EQ(result.getPy(), 2);
    EXPECT_EQ(result.getPz(), 3);
}

TEST(MonomTest, Subtraction) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);
    Monom result = m1 - m2;

    EXPECT_DOUBLE_EQ(result.getCoef(), -0.5);
    EXPECT_EQ(result.getPx(), 1);
    EXPECT_EQ(result.getPy(), 2);
    EXPECT_EQ(result.getPz(), 3);
}

TEST(MonomTest, Multiplication) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 2, 1, 1);
    Monom result = m1 * m2;

    EXPECT_DOUBLE_EQ(result.getCoef(), 7.5);
    EXPECT_EQ(result.getPx(), 3);
    EXPECT_EQ(result.getPy(), 3);
    EXPECT_EQ(result.getPz(), 4);
}

TEST(MonomTest, Division) {
    Monom m1(7.5, 3, 3, 4);
    Monom m2(2.5, 1, 2, 3);
    Monom result = m1 / m2;

    EXPECT_DOUBLE_EQ(result.getCoef(), 3.0);
    EXPECT_EQ(result.getPx(), 2);
    EXPECT_EQ(result.getPy(), 1);
    EXPECT_EQ(result.getPz(), 1);
}

TEST(MonomTest, MultiplyByScalar) {
    Monom m(2.5, 1, 2, 3);
    Monom result = m * 2.0;

    EXPECT_DOUBLE_EQ(result.getCoef(), 5.0);
    EXPECT_EQ(result.getPx(), 1);
    EXPECT_EQ(result.getPy(), 2);
    EXPECT_EQ(result.getPz(), 3);
}

TEST(MonomTest, DivideByScalar) {
    Monom m(2.5, 1, 2, 3);
    Monom result = m / 2.0;

    EXPECT_DOUBLE_EQ(result.getCoef(), 1.25);
    EXPECT_EQ(result.getPx(), 1);
    EXPECT_EQ(result.getPy(), 2);
    EXPECT_EQ(result.getPz(), 3);
}

TEST(MonomTest, UnaryMinus) {
    Monom m(2.5, 1, 2, 3);
    Monom result = -m;

    EXPECT_DOUBLE_EQ(result.getCoef(), -2.5);
    EXPECT_EQ(result.getPx(), 1);
    EXPECT_EQ(result.getPy(), 2);
    EXPECT_EQ(result.getPz(), 3);
}

TEST(MonomTest, AddAssign) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);
    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.getCoef(), 5.5);
}

TEST(MonomTest, SubtractAssign) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 1, 2, 3);
    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.getCoef(), -0.5);
}

TEST(MonomTest, MultiplyAssign) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 2, 1, 1);
    m1 *= m2;

    EXPECT_DOUBLE_EQ(m1.getCoef(), 7.5);
    EXPECT_EQ(m1.getPx(), 3);
    EXPECT_EQ(m1.getPy(), 3);
    EXPECT_EQ(m1.getPz(), 4);
}

TEST(MonomTest, DivideAssign) {
    Monom m1(7.5, 3, 3, 4);
    Monom m2(2.5, 1, 2, 3);
    m1 /= m2;

    EXPECT_DOUBLE_EQ(m1.getCoef(), 3.0);
    EXPECT_EQ(m1.getPx(), 2);
    EXPECT_EQ(m1.getPy(), 1);
    EXPECT_EQ(m1.getPz(), 1);
}

TEST(MonomTest, MultiplyByScalarAssign) {
    Monom m(2.5, 1, 2, 3);
    m *= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoef(), 5.0);
}

TEST(MonomTest, DivideByScalarAssign) {
    Monom m(2.5, 1, 2, 3);
    m /= 2.0;

    EXPECT_DOUBLE_EQ(m.getCoef(), 1.25);
}

TEST(MonomTest, Assignment) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2;
    m2 = m1;

    EXPECT_EQ(m2, m1);
}

TEST(MonomTest, Evaluate) {
    Monom m(2.5, 2, 1, 3);
    double result = m.evaluate(2, 3, 4);
    double expected = 2.5 * 4 * 3 * 64; // 2^2=4, 3^1=3, 4^3=64
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(MonomTest, DivisionByZeroThrows) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(0, 1, 2, 3);

    EXPECT_THROW(m1 / m2, std::invalid_argument);
    EXPECT_THROW(m1 /= m2, std::invalid_argument);
}

TEST(MonomTest, DissimilarAdditionThrows) {
    Monom m1(2.5, 1, 2, 3);
    Monom m2(3.0, 2, 2, 3);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
    EXPECT_THROW(m1 += m2, std::invalid_argument);
}

// Тесты для класса Polynom
TEST(PolynomTest, DefaultConstructor) {
    Polynom p;
    EXPECT_TRUE(p.isEmpty());
    EXPECT_EQ(p.getSize(), 0);
}

TEST(PolynomTest, StringConstructor) {
    Polynom p("x^2 + 2y^3z - 4z^5");
    EXPECT_EQ(p.getSize(), 3);
}

TEST(PolynomTest, CharConstructor) {
    Polynom p("x^2 + 2y^3z - 4z^5");
    EXPECT_EQ(p.getSize(), 3);
}

TEST(PolynomTest, CopyConstructor) {
    Polynom p1("x^2 + 2y");
    Polynom p2(p1);
    EXPECT_EQ(p2, p1);
}

TEST(PolynomTest, Assignment) {
    Polynom p1("x^2 + 2y");
    Polynom p2;
    p2 = p1;
    EXPECT_EQ(p2, p1);
}

TEST(PolynomTest, EmptyStringConstructor) {
    Polynom p("");
    EXPECT_TRUE(p.isEmpty());
}

TEST(PolynomTest, ConstantPolynom) {
    Polynom p("-5");
    EXPECT_EQ(p.getSize(), 1);

    auto it = p.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), -5);
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 0);
    EXPECT_EQ(it->getPz(), 0);
}

TEST(PolynomTest, Sorting) {
    Polynom p("y^2z^3 + 2y^2 + xy + 6");

    auto it = p.begin();
    // xy
    EXPECT_EQ(it->getPx(), 1);
    EXPECT_EQ(it->getPy(), 1);
    EXPECT_EQ(it->getPz(), 0);

    ++it;
    // y^2z^3
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 2);
    EXPECT_EQ(it->getPz(), 3);

    ++it;
    // 2y^2
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 2);
    EXPECT_EQ(it->getPz(), 0);

    ++it;
    // 6
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 0);
    EXPECT_EQ(it->getPz(), 0);
}

TEST(PolynomTest, Addition) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom result = p1 + p2;

    EXPECT_EQ(result.getSize(), 1);
    auto it = result.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), 2);
    EXPECT_EQ(it->getPx(), 1);
}

TEST(PolynomTest, Subtraction) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    Polynom result = p1 - p2;

    EXPECT_EQ(result.getSize(), 1);
    auto it = result.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), 2);
    EXPECT_EQ(it->getPy(), 1);
}

TEST(PolynomTest, Multiplication) {
    Polynom p1("x + 1");
    Polynom p2("x - 1");
    Polynom result = p1 * p2;

    EXPECT_EQ(result.getSize(), 2); // x^2 - 1

    auto it = result.begin();
    // x^2
    EXPECT_DOUBLE_EQ(it->getCoef(), 1);
    EXPECT_EQ(it->getPx(), 2);

    ++it;
    // -1
    EXPECT_DOUBLE_EQ(it->getCoef(), -1);
}

TEST(PolynomTest, MultiplyByScalar) {
    Polynom p("x + y");
    Polynom result = p * 3.0;

    EXPECT_EQ(result.getSize(), 2);
    for (const auto& m : result) {
        EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);
    }
}
TEST(PolynomTest, DivideByScalar) {
    Polynom p("2x + 4y");
    Polynom result = p / 2.0;

    EXPECT_EQ(result.getSize(), 2);

    auto it = result.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), 1.0);
    EXPECT_EQ(it->getPx(), 1);
    EXPECT_EQ(it->getPy(), 0);
    EXPECT_EQ(it->getPz(), 0);

    ++it;
    EXPECT_DOUBLE_EQ(it->getCoef(), 2.0);  
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 1);
    EXPECT_EQ(it->getPz(), 0);
}

TEST(PolynomTest, UnaryMinus) {
    Polynom p("x - y");
    Polynom result = -p;

    EXPECT_EQ(result.getSize(), 2);

    auto it = result.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), -1);
    EXPECT_EQ(it->getPx(), 1);

    ++it;
    EXPECT_DOUBLE_EQ(it->getCoef(), 1);
    EXPECT_EQ(it->getPy(), 1);
}

TEST(PolynomTest, AddAssign) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    p1 += p2;

    EXPECT_EQ(p1.getSize(), 1);
    EXPECT_DOUBLE_EQ(p1.begin()->getCoef(), 2);
}

TEST(PolynomTest, SubtractAssign) {
    Polynom p1("x + y");
    Polynom p2("x - y");
    p1 -= p2;

    EXPECT_EQ(p1.getSize(), 1);
    EXPECT_DOUBLE_EQ(p1.begin()->getCoef(), 2);
    EXPECT_EQ(p1.begin()->getPy(), 1);
}

TEST(PolynomTest, MultiplyAssign) {
    Polynom p1("x + 1");
    Polynom p2("x - 1");
    p1 *= p2;

    EXPECT_EQ(p1.getSize(), 2);
}

TEST(PolynomTest, MultiplyByScalarAssign) {
    Polynom p("x + y");
    p *= 3.0;

    for (const auto& m : p) {
        EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);
    }
}

TEST(PolynomTest, DivideByScalarAssign) {
    Polynom p("2x + 4y");
    p /= 2.0;

    EXPECT_EQ(p.getSize(), 2);

    auto it = p.begin();
    EXPECT_DOUBLE_EQ(it->getCoef(), 1.0);
    EXPECT_EQ(it->getPx(), 1);
    EXPECT_EQ(it->getPy(), 0);
    EXPECT_EQ(it->getPz(), 0);

   
    ++it;
    EXPECT_DOUBLE_EQ(it->getCoef(), 2.0);  
    EXPECT_EQ(it->getPx(), 0);
    EXPECT_EQ(it->getPy(), 1);
    EXPECT_EQ(it->getPz(), 0);
}

TEST(PolynomTest, Equality) {
    Polynom p1("x + y");
    Polynom p2("y + x");
    Polynom p3("x - y");

    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
}

TEST(PolynomTest, Evaluate) {
    Polynom p("x^2 + 2x + 1");
    double result = p.evaluate(2, 0, 0);
    EXPECT_DOUBLE_EQ(result, 9);
}

TEST(PolynomTest, EvaluateComplex) {
    Polynom p("x^2y + 2xz - 3");
    double result = p.evaluate(2, 3, 1);
    EXPECT_DOUBLE_EQ(result, 13);
}

TEST(PolynomTest, Clear) {
    Polynom p("x + y");
    EXPECT_FALSE(p.isEmpty());
    p.clear();
    EXPECT_TRUE(p.isEmpty());
    EXPECT_EQ(p.getSize(), 0);
}

TEST(PolynomTest, InputOutput) {
    Polynom p1("x^2 + 2x + 1");
    std::stringstream ss;
    ss << p1;

    Polynom p2;
    ss >> p2;

    EXPECT_EQ(p1, p2);
}

TEST(PolynomTest, ScalarMultiplicationCommutative) {
    Polynom p("x + y");
    Polynom result1 = p * 3.0;
    Polynom result2 = 3.0 * p;

    EXPECT_EQ(result1, result2);
}

TEST(PolynomTest, CombiningLikeTerms) {
    Polynom p("x + 2x + 3x");
    EXPECT_EQ(p.getSize(), 1);
    EXPECT_DOUBLE_EQ(p.begin()->getCoef(), 6);
}

TEST(PolynomTest, ZeroElimination) {
    Polynom p("x - x + y");
    EXPECT_EQ(p.getSize(), 1);
    EXPECT_EQ(p.begin()->getPy(), 1);
}

TEST(PolynomTest, DivisionByZeroThrows) {
    Polynom p("x + y");
    EXPECT_THROW(p / 0.0, std::invalid_argument);
    EXPECT_THROW(p /= 0.0, std::invalid_argument);
}