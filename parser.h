#ifndef AST_H
#define AST_H
#include <memory>
#include <string>
#include <vector>
#include "tokenizer.h"

using namespace std;


class ASTNode {
    public:
    ASTNode(){}
    virtual ~ASTNode() = default;
};

class ASTExp : public ASTNode {};

class BinExp : public ASTExp {
    public:
    BinExp(unique_ptr<ASTExp> left, unique_ptr<ASTExp> right, string op) : left(move(left)), right(move(right)), op(op) {};
    
    private:
    unique_ptr<ASTExp> left;
    unique_ptr<ASTExp> right;
    string op;
};

class Parser {
    public:
    Parser() {}
    unique_ptr<ASTNode> parse(const vector<Token>& tokens) {
        return nullptr; // Placeholder
    }
};

#endif // AST_H