#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <regex>
#include <cctype>

enum class Tokens {
    LPAREN, RPAREN, PLUS, MINUS, POW, MULT, DIV, PRINT, EQUALS, NUMBER, VARIABLE
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
        int line = 0;
        int cc = 0;
        while(i < s.length()){
            char c = s[i];
            if(c == '\n') {i++; line++; c = 0; continue;}
            if(isspace(c)) {i++; c++; continue;}

            if      (c == '(') { tokens.push_back({ Tokens::LPAREN,  "" }); i++; }
            else if (c == ')') { tokens.push_back({ Tokens::RPAREN,  "" }); i++; }
            else if (c == '+') { tokens.push_back({ Tokens::PLUS,    "" }); i++; }
            else if (c == '-') { tokens.push_back({ Tokens::MINUS,   "" }); i++; }
            else if (c == '*') { tokens.push_back({ Tokens::MULT,    "" }); i++; }
            else if (c == '/') { tokens.push_back({ Tokens::DIV,     "" }); i++; }
            else if (c == '^') { tokens.push_back({ Tokens::POW,     "" }); i++; }
            else if (c == '=') { tokens.push_back({ Tokens::EQUALS,  "" }); i++; }
            else if (isdigit(c)) {
                std::string num;
                while (i < s.size() && (isdigit(s[i]) || s[i] == '.'))
                    num += s[i++];
                tokens.push_back({ Tokens::NUMBER, num });
            }
            else if (isalpha(c) || c == '_') {
                std::string word;
                while (i < s.size() && (isalnum(s[i]) || s[i] == '_'))
                    word += s[i++];

                if (word == "print")
                    tokens.push_back({ Tokens::PRINT, "" });
                else
                    tokens.push_back({ Tokens::VARIABLE, word });
            }
            else{
                std::cerr << "Unknown Character: " << c << " at " << line << ":" << cc << std::endl;
            }
            cc++;
        }
        return tokens;
    };
private:
    std::string input;
};

#endif // TOKENIZER_H