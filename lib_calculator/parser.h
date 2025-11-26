#pragma once
#include "List.h"
#include "Lexem.h"
#include "Stack.h"
#include <stdexcept>
#include <string>
#include <unordered_map>

class Parser {
public:
    static List<Lexem> parse(const std::string& expression);
    static List<Lexem> to_postfix(const List<Lexem>& infix);
    static double evaluate(const List<Lexem>& postfix, const std::unordered_map<std::string, double>& variables);

private:
    static bool is_operator(char c);
    static bool is_function(const std::string& str);
    static bool is_variable_char(char c);
    static bool is_bracket(char c);
    static TypeLexem get_bracket_type(char c);
    static bool is_matching_brackets(char open, char close);
    static int get_operator_priority(const std::string& op);
};