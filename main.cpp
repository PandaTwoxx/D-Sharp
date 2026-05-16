#include <iostream>
#include <fstream>
#include <sstream>
#include "tokenizer.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_string>" << endl;
        return 1;
    }
    string input;
    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        cerr << "Could not open file: " << argv[1] << endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    input = buffer.str();
    Tokenizer tokenizer;
    vector<Token> tokens = tokenizer.tokenize(input);
    cout << "Tokens:" << endl;
    for (const auto& token : tokens) {
        cout << static_cast<int>(token.type) << " (" << token.val << ")" << endl;
    }

    return 0;
}