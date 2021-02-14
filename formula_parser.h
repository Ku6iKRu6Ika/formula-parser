#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include <cmath>
#include <string>
using namespace std;

#define VERSION_FORMULA_PARSER "1.0.0.0"

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

#endif