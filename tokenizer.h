#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <regex>
#include <cctype>

enum class Tokens {
    LPAREN, RPAREN, PLUS, MINUS, POW, MULT, DIV, PRINT, EQUALS, NUMBER, VARIABLE, SEMI, DONE
};

struct Token{
    Tokens type;
    std::string val;
};

class Tokenizer {
public:
    Tokenizer(){}
        std::vector<Token> tokenize(std::string s){
        std::vector<Token> tokens;
        int i = 0;
        int line = 1;
        int cc = 0;
        int startLine = 0;
        while(i < s.length()){
            char c = s[i];
            if(c == '\n') {
                if(tokens.empty() || tokens.back().type != Tokens::SEMI){
                    handleError(line, cc, "Expected semicolon", s.substr(startLine, s.find('\n', startLine) - startLine));
                }
                startLine = i+1;
                i++; 
                line++; 
                cc = 0; 
                continue;
            }
            if(isspace(c)) {i++; cc++; continue;}

            if      (c == '(') { tokens.push_back({ Tokens::LPAREN,  "" }); i++; cc++; }
            else if (c == ')') { tokens.push_back({ Tokens::RPAREN,  "" }); i++; cc++; }
            else if (c == '+') { tokens.push_back({ Tokens::PLUS,    "" }); i++; cc++; }
            else if (c == '-') { tokens.push_back({ Tokens::MINUS,   "" }); i++; cc++; }
            else if (c == '*') { tokens.push_back({ Tokens::MULT,    "" }); i++; cc++; }
            else if (c == '/') { tokens.push_back({ Tokens::DIV,     "" }); i++; cc++; }
            else if (c == '^') { tokens.push_back({ Tokens::POW,     "" }); i++; cc++; }
            else if (c == '=') { tokens.push_back({ Tokens::EQUALS,  "" }); i++; cc++; }
            else if (c == ';') { tokens.push_back({ Tokens::SEMI,     "" }); i++; cc++; }
            else if (isdigit(c)) {
                std::string num;
                while (i < s.size() && (isdigit(s[i]) || s[i] == '.')) {
                    num += s[i++];
                    cc++;
                }
                tokens.push_back({ Tokens::NUMBER, num });
            }
            else if (isalpha(c) || c == '_') {
                std::string word;
                while (i < s.size() && (isalnum(s[i]) || s[i] == '_')) {
                    word += s[i++];
                    cc++;
                }

                if (word == "print")
                    tokens.push_back({ Tokens::PRINT, "" });
                else
                    tokens.push_back({ Tokens::VARIABLE, word });
            }
            else{
                handleError(line, cc, "Unexpected Character: " + std::string(1, c), s.substr(startLine, s.find('\n', startLine) - startLine));
            }
        }
        return tokens;
    }

    void handleError(int line, int cc, const std::string& message, const std::string& lineContent) {
        std::cerr << "Error at " << line << ":" << cc << " during tokenization - " << message << std::endl;
        std::cerr << ">>\t" << lineContent << "\t<<" << std::endl;
        exit(1);
    }
private:
    std::string input;
};

#endif // TOKENIZER_H