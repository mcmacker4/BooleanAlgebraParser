cmake_minimum_required(VERSION 3.10)
project(DiscreteMathsParser)

set(CMAKE_CXX_STANDARD 11)

add_executable(DiscreteMathsParser Source/main.cpp Source/Lexer.cpp Source/Lexer.h Source/Parser.h Source/Parser.cpp)