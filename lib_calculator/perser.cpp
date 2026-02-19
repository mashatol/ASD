//#include "Parser.h"
//#include "stack.h"
//#include <sstream>
//#include <cctype>
//#include <algorithm>
//#include <stdexcept>
//#include <iostream>
//#include <unordered_map>
//
//using namespace std;
//
//namespace Parser {
//    unordered_map<string, int> operatorPriority = {
//        {"+", 1}, {"-", 1},
//        {"*", 2}, {"/", 2},
//        {"^", 3}, {"u-", 4}  
//    };
//
//    unordered_map<string, function<double(double)>> functions = {
//        {"sin", [](double x) { return sin(x); }},
//        {"cos", [](double x) { return cos(x); }},
//        {"tg", [](double x) { return tan(x); }},
//        {"tan", [](double x) { return tan(x); }},
//        {"ln", [](double x) { return log(x); }},
//        {"log", [](double x) { return log10(x); }},
//        {"exp", [](double x) { return exp(x); }},
//        {"sqrt", [](double x) { return sqrt(x); }},
//        {"abs", [](double x) { return fabs(x); }}
//    };
//
//
//    bool isDigit(char c) {
//        return isdigit(static_cast<unsigned char>(c)) || c == '.';
//    }
//
//    bool isLetter(char c) {
//        return isalpha(static_cast<unsigned char>(c)) || c == '_';
//    }
//
//    bool isVariableChar(char c) {
//        return isalnum(static_cast<unsigned char>(c)) || c == '_';
//    }
//
//    int getPriority(const string& op) {
//        typedef unordered_map<string, int>::const_iterator MapIterator;
//        MapIterator it = operatorPriority.find(op);
//        if (it != operatorPriority.end()) {
//            return it->second;
//        }
//        return -1;
//    }
//
//    bool isUnaryOperator(char current, const List<Lexem>& previous) {
//        if (previous.empty()) {
//            return true;
//        }
//
//        const Lexem& last = previous.back();
//
//        if (last.isOperator() ||
//            last.type == OpenBracket ||
//            last.type == OpenedAbs ||
//            last.type == Function) {
//            return true;
//        }
//
//        return false;
//    }
//
//    bool isOpeningAbs(const List<Lexem>& previous) {
//        
//        if (previous.empty()) {
//            return true;
//        }
//
//        const Lexem& last = previous.back();
//
//        if (last.isOperator() ||
//            last.type == OpenBracket ||
//            last.type == OpenedAbs ||
//            last.type == Function) {
//            return true;
//        }
//
//        return false;
//    }
//
//
//    List<Lexem> parse(const string& expression) {
//        List<Lexem> result;
//        string expr = expression;
//
//        expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
//
//        if (expr.empty()) {
//            throw invalid_argument("Empty expression");
//        }
//
//        size_t pos = 0; // позиция
//        size_t length = expr.length(); // длина строки
//
//        while (pos < length) {
//            char current = expr[pos];
//
//            if (isDigit(current)) {
//                size_t start = pos;
//                bool hasDecimal = false; // была ли точка в числе
//
//                while (pos < length && isDigit(expr[pos])) {
//                    if (expr[pos] == '.') {
//                        if (hasDecimal) {
//                            throw invalid_argument("Invalid number: multiple decimal points at position " + to_string(pos + 1));
//                        }
//                        hasDecimal = true;
//                    }
//                    pos++;
//                }
//
//                string numStr = expr.substr(start, pos - start);
//
//                if (numStr == ".") {
//                    throw invalid_argument("Invalid number: single dot at position " + to_string(start + 1)); // переводим позицию в строку
//                }
//
//                double value;
//                try {
//                    value = stod(numStr);
//                }
//                catch (...) {
//                    throw invalid_argument("Invalid number format at position " + to_string(start + 1));
//                }
//
//                result.push_back(Lexem(value));
//                continue;
//            }
//
//            if (isLetter(current)) {
//                size_t start = pos;
//
//                while (pos < length && isVariableChar(expr[pos])) {
//                    pos++;
//                }
//
//                string name = expr.substr(start, pos - start);
//
//                if (pos < length && expr[pos] == '(') {
//                    unordered_map<string, function<double(double)>>::const_iterator it = functions.find(name);
//                    if (it != functions.end()) {
//                        result.push_back(Lexem(name, it->second));
//                    }
//                    else {
//                        throw invalid_argument("Unknown function '" + name + "' at position " + to_string(start + 1));
//                    }
//                }
//                else {
//                    result.push_back(Lexem(name, Variable));
//                }
//                continue;
//            }
//
//            if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
//                string op(1, current);
//
//                if (current == '-') {
//                    if (isUnaryOperator(current, result)) {
//                        result.push_back(Lexem("u-", UnOperator, 4));
//                    }
//                    else {
//                        result.push_back(Lexem("-", Operator, 1));
//                    }
//                }
//                else if (current == '+') {
//                    if (!isUnaryOperator(current, result)) {
//                        result.push_back(Lexem("+", Operator, 1));
//                    }
//                }
//                else {
//                    result.push_back(Lexem(op, Operator, getPriority(op)));
//                }
//
//                pos++;
//                continue;
//            }
//
//            if (current == '(' || current == '[' || current == '{') {
//                result.push_back(Lexem("(", OpenBracket));
//                pos++;
//                continue;
//            }
//
//            if (current == ')' || current == ']' || current == '}') {
//                result.push_back(Lexem(")", CloseBracket));
//                pos++;
//                continue;
//            }
//
//            if (current == '|') {
//                if (pos + 1 < length && expr[pos + 1] == '|') {
//                    if (isOpeningAbs(result)) {
//                        result.push_back(Lexem("||", OpenedAbs));
//                    }
//                    else {
//                        result.push_back(Lexem("||", ClosedAbs));
//                    }
//                    pos += 2;  
//                    continue;
//                }
//                else {
//                    throw invalid_argument("Single '|' is not allowed, use '||' for absolute value at position " + to_string(pos + 1));
//                }
//            }
//
//            throw invalid_argument("Unknown character '" + string(1, current) +
//                "' at position " + to_string(pos + 1));
//        }
//
//        return result;
//    }
//
//
//    List<Lexem> toRPN(const List<Lexem>& infix) {
//        List<Lexem> output;
//        Stack<Lexem> stack(100);
//
//        for (List<Lexem>::ConstIterator it = infix.begin(); it != infix.end(); ++it) {
//            const Lexem& lex = *it;
//
//            switch (lex.type) {
//            case Constant:
//            case Variable:
//                output.push_back(lex);
//                break;
//
//            case Function:
//                stack.push(lex);
//                break;
//
//            case UnOperator:
//            case Operator:
//                while (!stack.is_empty() &&
//                    stack.top().isOperator() &&
//                    stack.top().priority >= lex.priority) {
//                    output.push_back(stack.top());
//                    stack.pop();
//                }
//                stack.push(lex);
//                break;
//
//            case OpenBracket:
//            case OpenedAbs:
//                stack.push(lex);
//                break;
//
//            case CloseBracket: {
//                while (!stack.is_empty() && stack.top().type != OpenBracket) {
//                    output.push_back(stack.top());
//                    stack.pop();
//                }
//
//                if (stack.is_empty()) {
//                    throw runtime_error("Mismatched brackets: missing '('");
//                }
//
//                stack.pop();
//
//                if (!stack.is_empty() && stack.top().type == Function) {
//                    output.push_back(stack.top());
//                    stack.pop();
//                }
//                break;
//            }
//
//            case ClosedAbs: {
//                while (!stack.is_empty() && stack.top().type != OpenedAbs) {
//                    output.push_back(stack.top());
//                    stack.pop();
//                }
//
//                if (stack.is_empty()) {
//                    throw runtime_error("Mismatched absolute value bars: missing opening '||'");
//                }
//
//                stack.pop();
//
//                output.push_back(Lexem("abs", functions.at("abs")));
//                break;
//            }
//
//            default:
//                break;
//            }
//        }
//
//        while (!stack.is_empty()) {
//            if (stack.top().isBracket() || stack.top().isAbs()) {
//                if (stack.top().type == OpenBracket) {
//                    throw runtime_error("Mismatched brackets: missing ')'");
//                }
//                else if (stack.top().type == OpenedAbs) {
//                    throw runtime_error("Mismatched absolute value bars: missing closing '||'");
//                }
//            }
//
//            output.push_back(stack.top());
//            stack.pop();
//        }
//
//        return output;
//    }
//} // namespace Parser