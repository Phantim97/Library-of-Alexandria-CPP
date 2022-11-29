#include <iostream>
void print_array(char* str)
{
    if (*str == '\0') //Base case
    {
        return;
    }

    std::cout << *str << '\n';
    print_array(str + 1); //Induction Hypothesis
}
