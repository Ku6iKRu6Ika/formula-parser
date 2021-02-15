#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include <cmath>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define VERSION_FORMULA_PARSER "1.2.0"

class FormulaParser
{
    string polish_exp;

    int get_priority(char ch);
    bool is_operator(char ch);
    bool is_digit(char ch);
public:
    void parser(string exp);
    double calc();
};

class ExceptionFormulaParser
{
    string m_error;
public:
    ExceptionFormulaParser(string error)
        : m_error(error)
    {
    }
 
    const char* what() { return m_error.c_str(); }
};

#endif