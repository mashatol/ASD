//#ifndef EXPRESSION_H
//#define EXPRESSION_H
//
//#include "list.h"
//#include "Lexem.h"
//#include <string>
//#include <unordered_map>
//
//class Expression {
//    int id;
//    std::string exprStr;
//    List<Lexem> infix;
//    List<Lexem> rpn;
//    std::unordered_map<std::string, double> vars;
//    bool parsed;
//
//    void extractVariables();
//public:
//    Expression() : id(0), parsed(false) {}
//    Expression(int _id, const std::string& expr);
//
//    void parse();
//    double evaluate(const std::unordered_map<std::string, double>& vars = {}); //вычисляет значение выражения
//    void setVariable(const std::string& name, double value); // устанавливает значение переменной
//    void clearVariables();
//
//    int getId() const { return id; }
//    std::string getExpression() const { return exprStr; }
//    bool getIsParsed() const { return parsed; }
//    const std::unordered_map<std::string, double>& getVariables() const { return vars; }
//
//    const List<Lexem>& getInfix() const { return infix; } 
//    const List<Lexem>& getRPN() const { return rpn; }
//
//    void setExpression(const std::string& expr); // изменяет выражение
//    size_t getVariableCount() const { return vars.size(); } // возвращает количество переменных
//};
//
//#endif