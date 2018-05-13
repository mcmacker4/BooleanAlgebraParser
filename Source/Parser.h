#ifndef DISCRETEMATHSPARSER_PARSER_H
#define DISCRETEMATHSPARSER_PARSER_H

#include "Lexer.h"

namespace Parser {

    enum ExpType {
        EXP_0,
        EXP_1,
        EXP_2,
        EXP_3,
        VALUE,
    };

    class SyntaxError : public std::exception {
    public:
        std::string message;
        explicit SyntaxError(std::string message)
                : message(std::move(message)) {}
    };

    struct Node {
        ExpType type;
        explicit Node(ExpType type)
                : type(type) {}
    };

    struct BinaryNode : public Node {
        Node *left;
        Node *right;
        BinaryNode(ExpType type, Node *left, Node *right)
                : Node(type), left(left), right(right) {}
    };

    struct UnaryNode : public Node {
        Node *child;
        bool negated;
        UnaryNode(ExpType type, Node *child, bool negated)
                : Node(type), child(child), negated(negated) {}
    };

    struct ValueNode : public Node {
        char value;
        explicit ValueNode(char value)
                : Node(VALUE), value(value) {}
    };

    struct AST {
        Node *root;
    };

    AST Parse(std::queue<Lexer::Token> &tokens);

}

#endif //DISCRETEMATHSPARSER_PARSER_H
