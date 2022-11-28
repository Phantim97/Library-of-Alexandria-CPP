//Metaprogramming Variant
template<int N>
struct Fibonacci
{
    static const int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value; //Induction Step & Induction Hypothesis (Fibonacci<N-1>::value + Fibonacci<N-2>::value)
};

template<>
struct Fibonacci<0>
{
    static const int value = 0; //Base Case
};

//Normal Variant
int fibonacci(int n)
{
    if (n == 0) //Base case
    {
        return 0;
    }

    if (n == 1) //Base case
    {
        return 1;
    }

    int ans1 = fibonacci(n-1); //Induction Hypothesis
    int ans2 = fibonacci(n-2); //Induction Hypothesis
    return ans1 + ans2; //Induction Step
}
