#include <iostream>

void print_permutations(char* str)
{
    if (*str == '\0') //Base case
    {
        std::cout << '\n';
        return;
    }

    for (int i = 0; str[i] != '\0'; ++i)
    {
        std::swap(str[0], str[i]);
        print_permutations(str + 1); //Induction Hypothesis
        std::swap(str[0], str[i]);
    }
}
