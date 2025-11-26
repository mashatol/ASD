#pragma once
#include "List.h"
#include "Lexem.h"
#include <unordered_map>
#include <string>

class Expression {
private:
    int id;
    std::string expression_str;
    List<Lexem> infix_notation;
    List<Lexem> postfix_notation;
    std::unordered_map<std::string, double> variables;

public:
    Expression(int _id = 0, const std::string& expr = "")
        : id(_id), expression_str(expr) {
    }

    int get_id() const { return id; }
    const std::string& get_expression() const { return expression_str; }
    void set_expression(const std::string& expr) { expression_str = expr; }

    void set_variable(const std::string& name, double value) {
        variables[name] = value;
    }

    double get_variable(const std::string& name) const {
        auto it = variables.find(name);
        if (it == variables.end()) {
            throw std::runtime_error("Variable not found: " + name);
        }
        return it->second;
    }

    bool has_variable(const std::string& name) const {
        return variables.find(name) != variables.end();
    }

    void set_infix_notation(const List<Lexem>& infix) { infix_notation = infix; }
    void set_postfix_notation(const List<Lexem>& postfix) { postfix_notation = postfix; }

    const List<Lexem>& get_infix_notation() const { return infix_notation; }
    const List<Lexem>& get_postfix_notation() const { return postfix_notation; }

    const std::unordered_map<std::string, double>& get_variables() const { return variables; }
    void clear_variables() { variables.clear(); }
};