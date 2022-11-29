#include <iostream>

void print_all_subsequences(char* str)
{
    if (*str == '\0') //Base case
    {
        std::cout << str << '\n';
        return;
    }

    print_all_subsequences(str + 1); //Induction Hypothesis

    for (int i = 0; str[i] != '\0'; ++i)
    {
        std::cout << str[i];
    }
  
    std::cout << '\n';
}
