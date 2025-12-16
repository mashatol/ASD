#include "Parser.h"

Parser::Parser() : pos(0) {}

void Parser::skipSpaces() {
    while (pos < expr.size() && isspace(expr[pos])) pos++;
}

double Parser::parseNumber() {
    size_t start = pos;
    bool dot = false;

    while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (dot) throw std::runtime_error("Invalid number");
            dot = true;
        }
        pos++;
    }

    std::string num = expr.substr(start, pos - start);
    std::stringstream ss(num);
    double val;
    ss >> val;
    return val;
}

std::string Parser::parseName() {
    size_t start = pos;
    while (pos < expr.size() && (isalnum(expr[pos]) || expr[pos] == '_')) pos++;
    return expr.substr(start, pos - start);
}

double Parser::parseFunction(const std::string& name) {
    skipSpaces();
    if (expr[pos] != '(') throw std::runtime_error("Expected '(' after function");
    pos++;

    double arg = parseAddSub();

    skipSpaces();
    if (expr[pos] != ')') throw std::runtime_error("Expected ')'");
    pos++;

    if (name == "sin") return sin(arg);
    if (name == "cos") return cos(arg);
    if (name == "tan") return tan(arg);
    if (name == "sqrt") {
        if (arg < 0) throw std::runtime_error("sqrt of negative");
        return sqrt(arg);
    }
    if (name == "abs") return fabs(arg);
    if (name == "log") return log10(arg);
    if (name == "ln") return log(arg);
    if (name == "exp") return exp(arg);

    throw std::runtime_error("Unknown function: " + name);
}

double Parser::parseAtom() {
    skipSpaces();

    if (expr[pos] == '(') {
        pos++;
        double val = parseAddSub();
        skipSpaces();
        if (expr[pos] != ')') throw std::runtime_error("Expected ')'");
        pos++;
        return val;
    }

    if (expr[pos] == '-') {
        pos++;
        return -parseAtom();
    }

    if (isdigit(expr[pos]) || expr[pos] == '.') {
        return parseNumber();
    }

    if (isalpha(expr[pos])) {
        std::string name = parseName();
        skipSpaces();

        if (expr[pos] == '(') {
            return parseFunction(name);
        }

        auto it = vars.find(name);
        if (it == vars.end()) throw std::runtime_error("Unknown variable: " + name);
        return it->second;
    }

    throw std::runtime_error("Unexpected character");
}

double Parser::parsePow() {
    double left = parseAtom();

    while (true) {
        skipSpaces();
        if (expr[pos] == '^') {
            pos++;
            double right = parseAtom();
            left = pow(left, right);
        }
        else {
            break;
        }
    }

    return left;
}

double Parser::parseMulDiv() {
    double left = parsePow();

    while (true) {
        skipSpaces();
        char op = expr[pos];
        if (op == '*' || op == '/' || op == '%') {
            pos++;
            double right = parsePow();

            if (op == '*') left *= right;
            else if (op == '/') {
                if (right == 0) throw std::runtime_error("Division by zero");
                left /= right;
            }
            else {
                left = fmod(left, right);
            }
        }
        else {
            break;
        }
    }

    return left;
}

double Parser::parseAddSub() {
    double left = parseMulDiv();

    while (true) {
        skipSpaces();
        char op = expr[pos];
        if (op == '+' || op == '-') {
            pos++;
            double right = parseMulDiv();

            if (op == '+') left += right;
            else left -= right;
        }
        else {
            break;
        }
    }

    return left;
}

double Parser::calculate(const std::string& expression) {
    expr = expression;
    pos = 0;
    vars.clear();

    double result = parseAddSub();
    skipSpaces();
    if (pos != expr.size()) throw std::runtime_error("Unexpected characters");

    return result;
}

double Parser::calculate(const std::string& expression, const std::map<std::string, double>& variables) {
    expr = expression;
    pos = 0;
    vars = variables;

    double result = parseAddSub();
    skipSpaces();
    if (pos != expr.size()) throw std::runtime_error("Unexpected characters");

    return result;
}

bool Parser::validate(const std::string& expression) {
    try {
        Parser p;
        p.calculate(expression);
        return true;
    }
    catch (...) {
        return false;
    }
}