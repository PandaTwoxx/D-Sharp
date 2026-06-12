#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <path_to_file>" << endl;
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

    Parser parser(tokens);
    auto ast = parser.parse();

    Interpreter interpreter;
    interpreter.visit(*ast);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Completed in " << duration.count() << " microseconds" << endl;
    return 0;
}