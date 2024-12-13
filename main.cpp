#include <iostream>
#include <vector>
#include <sstream>

#include "lexemeanalyzer.h"
#include "parser.h"

int main() {
    // std::cout << "Enter source file name: ";
    // std::string filename;x
    // std::cin >> filename;

    // std::ifstream file(filename);

    // if (!file.is_open()) {
    //     std::cerr << "Could not open the file!" << '\n';
    //     return 1;
    // }

    // std::stringstream buffer;
    // buffer << file.rdbuf();
    // std::string sourceCode = buffer.str();


    std::vector<Lexeme> lexemes = AnalyzeLexeme();
    Parser parser(lexemes);
    try {
        parser.parse(); 
        std::cout << "Process completed successfully" << '\n';
    } catch (std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
    SymbolTable symbolTable;

    try {
        SemanticAnalyzer semanticAnalyzer(symbolTable, lexemes);
        semanticAnalyzer.analyze();
        std::cout << "Semantic analysis passed." << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Semantic error: " << e.what() << std::endl;

    }
    return 0;
}