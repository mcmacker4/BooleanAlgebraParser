#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Parser.h"

using namespace Lexer;
using namespace Parser;

char OperatorFromExp(ExpType type) {
    switch(type) {
        case EXP_0: return 'i';
        case EXP_1: return 'o';
        case EXP_2: return 'a';
        default: return '?';
    }
}

void PrintRPN(Node *node) {

    // ( A ( B ( C n ) a ) o )

    if(node->type == VALUE) {
        auto valNode = (ValueNode*) node;
        std::cout << valNode->value << " ";
    } else if(node->type == EXP_3) {
        auto uNode = (UnaryNode*) node;
        PrintRPN(uNode->child);
        if(uNode->negated) std::cout << "n ";
    } else {
        auto bNode = (BinaryNode*) node;
        PrintRPN(bNode->left);
        PrintRPN(bNode->right);
        std::cout << OperatorFromExp(bNode->type) << " ";
    }

}

int main() {

    std::ifstream stream;
    stream.open("expression.txt", std::ifstream::in);

    if(stream.is_open()) {

        try {

            std::queue<Token> tokens = Tokenize(stream);
            AST ast = Parse(tokens);

            PrintRPN(ast.root);
            std::cout << std::endl;

        } catch (LexException &ex) {
            std::cerr << ex.message << std::endl;
        } catch (SyntaxError &ex) {
            std::cerr << ex.message << std::endl;
        }

    } else {
        std::cerr << "Could not open file." << std::endl;
    }

}
