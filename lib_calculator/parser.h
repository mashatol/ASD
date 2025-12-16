#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <cctype>

class Parser {
private:
    std::string expr;
    size_t pos;
    std::map<std::string, double> vars;

    void skipSpaces();
    double parseNumber();
    std::string parseName();
    double parseAtom();
    double parsePow();
    double parseMulDiv();
    double parseAddSub();
    double parseFunction(const std::string& name);

public:
    Parser();
    double calculate(const std::string& expression);
    double calculate(const std::string& expression, const std::map<std::string, double>& variables);
    static bool validate(const std::string& expression);
};

#endif