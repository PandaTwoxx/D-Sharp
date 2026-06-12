#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

class Interpreter : public ASTVisitor {
public:
    void visit(ProgramNode& node) override {
        for (const auto& stmt : node.statements) {
            stmt->accept(*this);
        }
    }
    void visit(AssignStmtNode& node) override {
        double val = node.value->accept(*this);
        environment[node.varName] = val;
    }
    void visit(PrintStmtNode& node) override {
        double val = node.expr->accept(*this);
        cout << val << endl;
    }
    double visit(LiteralNode& node) override {
        return std::stod(node.value);
    }
    double visit(VariableNode& node) override {
        if (environment.find(node.name) == environment.end()) {
            throw std::runtime_error("Runtime Error: Undefined variable '" + node.name + "'");
        }
        return environment[node.name];
    }
    double visit(BinaryExprNode& node) override {
        double leftVal = node.left->accept(*this);
        double rightVal = node.right->accept(*this);

        switch (node.op) {
            case Tokens::PLUS:  return leftVal + rightVal;
            case Tokens::MINUS: return leftVal - rightVal;
            case Tokens::MULT:  return leftVal * rightVal;
            case Tokens::DIV:   
                if (rightVal == 0) throw std::runtime_error("Runtime Error: Division by zero");
                return leftVal / rightVal;
            case Tokens::POW:   return std::pow(leftVal, rightVal);
            default:
                throw std::runtime_error("Runtime Error: Unknown operator");
        }
    }
private:
    std::unordered_map<std::string, double> environment;
};

#endif // INTERPRETER_H