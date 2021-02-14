# Formula parser
### Opportunities
* Working with positive and negative numbers
* Working with decimal digits
* Considering priority
### Operations
* `+` - addition
* `-` - subtraction
* `*` - multiplication
* `/` - division
* `^` - degree
### API
* `FormulaParser` - parser class
* `void FormulaParser::parser(string exp)` - a function to convert an expression from
infix to postfix notation
* `double FormulaParser::calc()` - calculate the result of an expression
### Example
```c++
#include <iostream>
#include "formula_parser.h"
using namespace std;

int main()
{
    string exp;
    FormulaParser formula_parser;

    while(true)
    {
        getline(cin, exp);

        try
        {
            formula_parser.parser(exp);
            cout << formula_parser.calc() << '\n';
        }
        catch(ExceptionFormulaParser &err)
        {
            cout << err.what() << '\n';
        }
    }

    return 0;
}
```