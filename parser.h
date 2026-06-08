#ifndef AST_H
#define AST_H

class Parser;
class ASTNode;

#include "tokenizer.h"
#include <vector>
#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

#endif // AST_H