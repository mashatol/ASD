//#ifndef PARSER_H
//#define PARSER_H
//
//#include "list.h"
//#include "Lexem.h"
//#include <string>
//#include <functional>
//
//namespace Parser {
//    List<Lexem> parse(const std::string& expression);
//    List<Lexem> toRPN(const List<Lexem>& infix);
//
//    bool isDigit(char c); // является ли символ цифрой или точкой(для десятичных дробей)
//    bool isLetter(char c);
//    bool isVariableChar(char c);
//    bool isUnaryOperator(char current, const List<Lexem>& previous);
//    bool isOpeningAbs(const List<Lexem>& previous);
//
//    int getPriority(const std::string& op);
//}
//
//#endif // PARSER_H