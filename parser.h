#ifndef AST_H
#define AST_H
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "tokenizer.h"

using namespace std;


enum class ASTNodeType { Program, AssignStmt, PrintStmt, BinaryExpr, Literal, Variable };

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual ASTNodeType getType() const = 0;
};

struct ExprNode : public ASTNode {};

struct LiteralNode : public ExprNode {
    std::string value;
    ASTNodeType getType() const override { return ASTNodeType::Literal; }
};

struct VariableNode : public ExprNode {
    std::string name;
    ASTNodeType getType() const override { return ASTNodeType::Variable; }
};

struct BinaryExprNode : public ExprNode {
    Tokens op; 
    std::unique_ptr<ExprNode> left;
    std::unique_ptr<ExprNode> right;
    ASTNodeType getType() const override { return ASTNodeType::BinaryExpr; }
};

struct StmtNode : public ASTNode {};

struct AssignStmtNode : public StmtNode {
    std::string varName;
    std::unique_ptr<ExprNode> value;
    ASTNodeType getType() const override { return ASTNodeType::AssignStmt; }
};

struct PrintStmtNode : public StmtNode {
    std::unique_ptr<ExprNode> expr;
    ASTNodeType getType() const override { return ASTNodeType::PrintStmt; }
};

struct ProgramNode : public ASTNode {
    std::vector<std::unique_ptr<StmtNode>> statements;
    ASTNodeType getType() const override { return ASTNodeType::Program; }
};

class Parser {
    public:
    Parser(vector<Token> tokens) : tokens(move(tokens)), cursor(0) {}

    unique_ptr<ProgramNode> parse() {
        auto program = std::make_unique<ProgramNode>();
        while (peek().type != Tokens::DONE) {
            program->statements.push_back(parseStatement());
        }
        return program;
    }

    private:
    vector<Token> tokens;
    size_t cursor;
    int line = 0;

    Token peek() {
        if (cursor >= tokens.size()) return Token{Tokens::DONE, ""};
        return tokens[cursor];
    }
    Token advance() {
        if (cursor < tokens.size()) cursor++;
        return tokens[cursor - 1];
    }
    Token assert(Tokens expected, const std::string& message) {
        Token t = peek();
        if (t.type != expected) {
            throw runtime_error("Error: Expected " + to_string(static_cast<int>(expected)) + " but got " + to_string(static_cast<int>(t.type)) + " - " + message);
            exit(1);
        }
        return advance();
    }

    unique_ptr<StmtNode> parseStatement() {
        if(peek().type == Tokens::PRINT){
            advance();
            auto stm = make_unique<PrintStmtNode>();
            stm->expr = parseExpression();
            assert(Tokens::SEMI, "Expected a semicolon at statement #" + to_string(line));
            line++;
            return stm;
        }else if(peek().type == Tokens::VARIABLE){
            Token var = advance();
            assert(Tokens::EQUALS, "Expected a equals sign in variable declaration at statement #" + to_string(line));
            auto stm = make_unique<AssignStmtNode>();
            stm->varName = var.val;
            stm->value = parseExpression();
            assert(Tokens::SEMI, "Expected a semicolon at statement #" + to_string(line));
            line++;
            return stm;
        }

        throw runtime_error("Unable to parse expression #" + to_string(line));
    }

    unique_ptr<ExprNode> parseExpression() {
        return parseAdditive();
    }
    std::unique_ptr<ExprNode> parseAdditive() {
        auto left = parseMultiplicative();
        while (peek().type == Tokens::PLUS || peek().type == Tokens::MINUS) {
            Token op = advance();
            auto node = std::make_unique<BinaryExprNode>();
            node->op = op.type;
            node->left = std::move(left);
            node->right = parseMultiplicative();
            left = std::move(node);
        }
        return left;
    }

    std::unique_ptr<ExprNode> parseMultiplicative() {
        auto left = parseExponentiation();
        while (peek().type == Tokens::MULT || peek().type == Tokens::DIV) {
            Token op = advance();
            auto node = std::make_unique<BinaryExprNode>();
            node->op = op.type;
            node->left = std::move(left);
            node->right = parseExponentiation();
            left = std::move(node);
        }
        return left;
    }

    std::unique_ptr<ExprNode> parseExponentiation() {
        auto left = parsePrimary();
        if (peek().type == Tokens::POW) {
            Token op = advance();
            auto node = std::make_unique<BinaryExprNode>();
            node->op = op.type;
            node->left = std::move(left);
            node->right = parseExponentiation(); 
            return node;
        }
        return left;
    }

    std::unique_ptr<ExprNode> parsePrimary() {
        Token current = peek();
        
        if (current.type == Tokens::NUMBER) {
            advance();
            auto node = std::make_unique<LiteralNode>();
            node->value = current.val;
            return node;
        }
        
        if (current.type == Tokens::VARIABLE) {
            advance();
            auto node = std::make_unique<VariableNode>();
            node->name = current.val;
            return node;
        }
        
        if (current.type == Tokens::LPAREN) {
            advance(); // consume '('
            auto expr = parseExpression();
            assert(Tokens::RPAREN, "Expected matching ')'");
            return expr;
        }
        
        throw std::runtime_error("Unexpected token in expression: " + current.val);
    }
};
    
#endif // AST_H