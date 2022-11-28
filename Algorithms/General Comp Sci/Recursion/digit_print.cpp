#include <iostream>

//Metaprogramming Variant
template<int N>
struct print_digits
{
    static void print()
    {
        print_digits<N/10>::print(); //Induction Hypothesis
        std::cout << N%10 << '\n'; //Induction Step
    }
};

template<>
struct print_digits<0>
{
    static void print()
    {
        return; //Base Case
    }
};

//Normal Variant
void print_digits(int n)
{
    if (n == 0) //Base case
    {
        return;
    }

    print_digits(n/10); //Induction Hypothesis
    std::cout << n%10 << '\n'; //Induction Step
}
