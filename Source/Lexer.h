#ifndef DISCRETEMATHSPARSER_LEXER_H
#define DISCRETEMATHSPARSER_LEXER_H

#include <queue>
#include <istream>

namespace Lexer {

    enum TokenType {
        VARIABLE,
        LITERAL,
        OPERATOR,
        LPAREN,
        RPAREN
    };

    struct Token {
        TokenType type;
        char value;
    };

    class LexException : public std::exception {
    public:
        const std::string message;
        explicit LexException(std::string message)
                : message(std::move(message)) {}
    };

    std::queue<Token> Tokenize(std::istream &stream);

}

#endif //DISCRETEMATHSPARSER_LEXER_H
