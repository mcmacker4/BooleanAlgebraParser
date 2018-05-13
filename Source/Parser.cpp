#include "Parser.h"

namespace Parser {

    /*
     * EBNF-ish syntax for expressions
     *
     * Exp4 : Value | '(', Exp0, ')'
     * Exp3 : [ 'n' ], Exp4
     * Exp2 : Exp3, [ and, Exp3 ]
     * Exp1 : Exp2, [ or, Exp2 ]
     * Exp0 : Exp1, [ i, Exp1 ]
     */

    Node* ReadExp0(std::queue<Lexer::Token> &tokens);

    Node* ReadExp4(std::queue<Lexer::Token> &tokens) {
        //Check if it's a value
        if(tokens.front().type == Lexer::VARIABLE
                || tokens.front().type == Lexer::LITERAL) {
            //Create node
            auto node = new ValueNode(tokens.front().value);
            //consume token
            tokens.pop();
            return node;
        } else if(tokens.front().type == Lexer::LPAREN) {
            //It's a parenthesis, consume it
            tokens.pop();
            //Return Exp0 node
            auto node = ReadExp0(tokens);
            if(tokens.empty() || tokens.front().type != Lexer::RPAREN)
                //Parenthesis not closed
                throw SyntaxError("Missing closing parenthesis.");
            tokens.pop();
            return node;
        } else {
            //Unexpected token
            std::string message = "Unexpected token: ";
            message += tokens.front().value;
            throw SyntaxError(message);
        }
    }

    Node* ReadExp3(std::queue<Lexer::Token> &tokens) {
        //Check if optional negation operator is present
        if(tokens.front().type == Lexer::OPERATOR
                && tokens.front().value == 'n') {
            // It is present, consume token
            tokens.pop();
            //Read child expression
            Node *child = ReadExp4(tokens);
            //Create node
            auto node = new UnaryNode(EXP_3, child, true);
            return node;
        }
        //Next token is not a negation, return Exp4
        return ReadExp4(tokens);
    }

    Node* ReadExp2(std::queue<Lexer::Token> &tokens) {
        //Read next level expression as left operand
        auto node = ReadExp3(tokens);
        //While next token is this level operator
        while(!tokens.empty() && tokens.front().value == 'a') {
            //Consume operator
            tokens.pop();
            //Read right operand as next level expression
            auto right = ReadExp3(tokens);
            //Create new node
            node = new BinaryNode(EXP_2, node, right);
        }
        //Return node
        return node;
    }

    Node* ReadExp1(std::queue<Lexer::Token> &tokens) {
        //Read next level expression as left operand
        auto node = ReadExp2(tokens);
        //While next token is this level operator
        while(!tokens.empty() && tokens.front().value == 'o') {
            //Consume operator
            tokens.pop();
            //Read right operand as next level expression
            auto right = ReadExp2(tokens);
            //Create new node
            node = new BinaryNode(EXP_1, node, right);
        }
        //Return node
        return node;
    }

    Node* ReadExp0(std::queue<Lexer::Token> &tokens) {
        //Read next level expression as left operand
        auto node = ReadExp1(tokens);
        //While next token is this level operator
        while(!tokens.empty() && tokens.front().value == 'i') {
            //Consume operator
            tokens.pop();
            //Read right operand as next level expression
            auto right = ReadExp1(tokens);
            //Create new node
            node = new BinaryNode(EXP_0, node, right);
        }
        //Return node
        return node;
    }

    AST Parse(std::queue<Lexer::Token> &tokens) {
        auto node = ReadExp0(tokens);
        return AST {
            root: node
        };
    }

}