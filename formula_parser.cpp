#include "formula_parser.h"

int FormulaParser::get_priority(char ch)
{
    switch(ch)
    {
        case '^':
            return 4;
        case '*': case '/':
            return 3;
        case '+': case '-':
            return 2;
        case '(':
            return 1;
    }
}

bool FormulaParser::is_operator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return true;

    return false;
}

bool FormulaParser::is_digit(char ch)
{
    if((ch >= '0' && ch <= '9') || ch == '.')
        return true;

    return false;
}

void FormulaParser::parser(string exp)
{
    char stack[1000];
    int j = 0;
    bool k = true, l = true, h = true;

    polish_exp.clear();

    for(int i = 0; i < exp.size(); ++i)
    {
        if(is_digit(exp[i]))
        {
            if(k)
                polish_exp += exp[i];
            else
                throw ExceptionFormulaParser("Invalid syntax");

            l = true;
        }
        else if(exp[i] == '(' || exp[i] == ')')
        {
            if(exp[i] == '(')
                stack[j++] = '(';
            else if(exp[i] == ')')
            {
                while(stack[j - 1] != '(')
                {
                    polish_exp += " ";
                    polish_exp += stack[j - 1];
                    --j;
                }

                --j;
            }
        }
        else if(is_operator(exp[i]))
        {
            if(k && !l && !h)
                throw ExceptionFormulaParser("Invalid syntax");

            k = true;
            l = false;
            h = false;

            if(j == 0 || get_priority(stack[j - 1]) < get_priority(exp[i]))
                stack[j++] = exp[i];
            else if(get_priority(stack[j - 1]) >= get_priority(exp[i]))
            {
                while(j != 0 && get_priority(stack[j - 1]) >= get_priority(exp[i]))
                {
                    polish_exp += " ";
                    polish_exp += stack[j - 1];
                    --j;
                }

                if(j == 0 || get_priority(stack[j - 1]) < get_priority(exp[i]))
                    stack[j++] = exp[i];
            }

            polish_exp += " ";
        }
        else if(isspace(exp[i]))
        {
            if(l)
                k = false;

            h = true;
        }
        else
            throw ExceptionFormulaParser("Unknown symbol");
    }

    if(j > 0)
    {
        while(j != 0)
        {
            polish_exp += " ";
            polish_exp += stack[j - 1];

            --j;
        }
    }
}

double FormulaParser::calc()
{
    double stack[1000];
    int j = 0;
    double result = 0, op1, op2;

    bool is_float = false;
    int remainder_fraction = 1;

    for(int i = 0; i < 1000; ++i)
        stack[i] = 0;

    for(int i = 0; i < polish_exp.size(); ++i)
    {
        if(is_digit(polish_exp[i]))
        {
            if(polish_exp[i] == '.')
                is_float = true;
            else
            {
                stack[j] *= 10;
                stack[j] += polish_exp[i] - '0';

                if(is_float)
                    remainder_fraction *= 10;
            }
        }
        else if(is_operator(polish_exp[i]))
        {
            op2 = stack[--j];
            op1 = stack[--j];
            stack[j + 1] = 0;

            switch(polish_exp[i])
            {
                case '+':
                    stack[j] = op1 + op2;
                    result = stack[j];
                    break;
                case '-':
                    stack[j] = op1 - op2;
                    result = stack[j];
                    break;
                case '*':
                    stack[j] = op1 * op2;
                    result = stack[j];
                    break;
                case '/':
                    if(op2 == 0)
                        throw ExceptionFormulaParser("Division by zero");

                    stack[j] = op1 / op2;
                    result = stack[j];
                    break;
                case '^':
                    stack[j] = pow(op1, op2);
                    result = stack[j];
                    break;
            }
        }
        else
        {
            if(is_float)
            {
                is_float = false;
                stack[j] = stack[j] / remainder_fraction;
                remainder_fraction = 1;
            }
            
            ++j;
        }
    }

    ++j;

    if(j > 0)
        result = stack[0];

    return result;
}