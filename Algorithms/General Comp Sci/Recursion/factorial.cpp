//Metaprogramming Variant
template<int N>
struct Factorial
{
    static const int value = N * Factorial<N-1>::value; //Induction Step & Induction Hypothesis (Factorial<N-1>::value)
};

template<>
struct Factorial<0>
{
    static const int value = 1; //Base Case
};

//Normal Variant
int factorial(int n)
{
    if (n == 0) //Base case
    {
        return 1;
    }

    int ans = factorial(n-1); //Induction Hypothesis
    return n * ans; //Induction Step
}
