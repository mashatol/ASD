#include "Parser.h"
#include <sstream>
#include <cctype>

bool Parser::is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Parser::is_function(const std::string& str) {
    return str == "sin" || str == "cos" || str == "tg" ||
        str == "ln" || str == "exp" || str == "abs";
}

bool Parser::is_variable_char(char c) {
    return std::isalnum(c) || c == '_';
}

bool Parser::is_bracket(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
}

TypeLexem Parser::get_bracket_type(char c) {
    if (c == '(' || c == '{' || c == '[') return TypeLexem::OpenBracket;
    if (c == ')' || c == '}' || c == ']') return TypeLexem::CloseBracket;
    throw std::runtime_error("Invalid bracket character");
}

bool Parser::is_matching_brackets(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '{' && close == '}') ||
        (open == '[' && close == ']');
}

int Parser::get_operator_priority(const std::string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return -1;
}

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    std::string buffer;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (std::isspace(c)) {
            continue;
        }

        if (std::isdigit(c) || c == '.') {
            buffer += c;
            while (i + 1 < expression.length() &&
                (std::isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
                buffer += expression[++i];
            }
            double value = std::stod(buffer);
            lexems.push_back(Lexem(buffer, TypeLexem::Constant, value));
            buffer.clear();
        }
        else if (std::isalpha(c) || c == '_') {
            buffer += c;
            while (i + 1 < expression.length() && Parser::is_variable_char(expression[i + 1])) {
                buffer += expression[++i];
            }

            if (Parser::is_function(buffer)) {
                std::function<double(double)> func;
                if (buffer == "sin") func = MathFunctions::my_sin;
                else if (buffer == "cos") func = MathFunctions::my_cos;
                else if (buffer == "tg") func = MathFunctions::my_tg;
                else if (buffer == "ln") func = MathFunctions::my_ln;
                else if (buffer == "exp") func = MathFunctions::my_exp;
                else if (buffer == "abs") func = MathFunctions::my_abs;

                lexems.push_back(Lexem(buffer, TypeLexem::Function, 0.0, 4, func));
            }
            else {
                lexems.push_back(Lexem(buffer, TypeLexem::Variable));
            }
            buffer.clear();
        }
        else if (Parser::is_operator(c)) {
            std::string op(1, c);
            int priority = Parser::get_operator_priority(op);
            lexems.push_back(Lexem(op, TypeLexem::Operator, 0.0, priority));
        }
        else if (Parser::is_bracket(c)) {
            TypeLexem type = Parser::get_bracket_type(c);
            lexems.push_back(Lexem(std::string(1, c), type));
        }
        else {
            throw std::runtime_error("Invalid character in expression: " + std::string(1, c));
        }
    }

    return lexems;
}

List<Lexem> Parser::to_postfix(const List<Lexem>& infix) {
    List<Lexem> output;
    Stack<Lexem> op_stack;

    typename List<Lexem>::ConstIterator it = infix.begin();
    while (it != infix.end()) {
        const Lexem& lexem = *it;

        switch (lexem.type) {
        case TypeLexem::Constant:
        case TypeLexem::Variable:
            output.push_back(lexem);
            break;

        case TypeLexem::Function:
            op_stack.push(lexem);
            break;

        case TypeLexem::Operator: {
            while (!op_stack.is_empty() &&
                op_stack.top().type != TypeLexem::OpenBracket &&
                op_stack.top().priority >= lexem.priority) {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            op_stack.push(lexem);
            break;
        }

        case TypeLexem::OpenBracket:
            op_stack.push(lexem);
            break;

        case TypeLexem::CloseBracket:
            while (!op_stack.is_empty() && op_stack.top().type != TypeLexem::OpenBracket) {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            if (op_stack.is_empty()) {
                throw std::runtime_error("Mismatched brackets");
            }
            op_stack.pop();

            if (!op_stack.is_empty() && op_stack.top().type == TypeLexem::Function) {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            break;

        default:
            break;
        }
        ++it;
    }

    while (!op_stack.is_empty()) {
        if (op_stack.top().type == TypeLexem::OpenBracket) {
            throw std::runtime_error("Mismatched brackets");
        }
        output.push_back(op_stack.top());
        op_stack.pop();
    }

    return output;
}

double Parser::evaluate(const List<Lexem>& postfix, const std::unordered_map<std::string, double>& variables) {
    Stack<double> value_stack;

    typename List<Lexem>::ConstIterator it = postfix.begin();
    while (it != postfix.end()) {
        const Lexem& lexem = *it;

        switch (lexem.type) {
        case TypeLexem::Constant:
            value_stack.push(lexem.value);
            break;

        case TypeLexem::Variable: {
            auto var_it = variables.find(lexem.name);
            if (var_it == variables.end()) {
                throw std::runtime_error("Undefined variable: " + lexem.name);
            }
            value_stack.push(var_it->second);
            break;
        }

        case TypeLexem::Function: {
            if (value_stack.is_empty()) throw std::runtime_error("Not enough operands for function");
            double arg = value_stack.top();
            value_stack.pop();
            double result = lexem.function(arg);
            value_stack.push(result);
            break;
        }

        case TypeLexem::Operator: {
            if (value_stack.is_empty()) throw std::runtime_error("Not enough operands for operator");
            double right = value_stack.top();
            value_stack.pop();
            if (value_stack.is_empty()) throw std::runtime_error("Not enough operands for operator");
            double left = value_stack.top();
            value_stack.pop();

            double result = 0;
            if (lexem.name == "+") result = left + right;
            else if (lexem.name == "-") result = left - right;
            else if (lexem.name == "*") result = left * right;
            else if (lexem.name == "/") {
                if (right == 0) throw std::runtime_error("Division by zero");
                result = left / right;
            }
            else if (lexem.name == "^") result = pow(left, right);

            value_stack.push(result);
            break;
        }
        default:
            break;
        }
        ++it;
    }

    if (value_stack.is_empty()) throw std::runtime_error("Empty expression");
    double result = value_stack.top();
    value_stack.pop();

    if (!value_stack.is_empty()) throw std::runtime_error("Too many operands");

    return result;
}