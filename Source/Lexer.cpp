#include "Lexer.h"

namespace Lexer {

    Token NextToken(std::istream &stream) {
        auto value = (char) stream.get();
        switch(value) {
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
            case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
            case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z': {
                return Token {
                    VARIABLE, value
                };
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': {
                return Token {
                    LITERAL, value
                };
            }
            case 'n': case 'a': case 'o': case 'i': {
                return Token {
                    OPERATOR, value
                };
            }
            case '(': {
                return Token {
                    LPAREN, value
                };
            }
            case ')': {
                return Token {
                    RPAREN, value
                };
            }
            default: {
                std::string message = "Invalid character: ";
                message += std::to_string(value);
                throw LexException(message);
            }
        }
    }

    void IgnoreSpaces(std::istream &stream) {
        while(isspace(stream.peek()))
            stream.get();
    }

    std::queue<Token> Tokenize(std::istream &stream) {
        std::queue<Token> tokens;
        IgnoreSpaces(stream);
        while(!stream.eof()) {
            Token token = NextToken(stream);
            tokens.push(token);
            IgnoreSpaces(stream);
        }
        return tokens;
    }

}