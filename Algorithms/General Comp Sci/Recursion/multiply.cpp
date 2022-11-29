//Metaprogramming Variant
template<int M, int N>
struct Multiply
{
    static const int value = M + Multiply<M, N-1>::value; //Induction Step & Induction Hypothesis (M + Multiply<M, N-1>::value)
};

template<int M>
struct Multiply<M, 0>
{
    static const int value = 0; //Base Case
};

//Normal Variant
int multiplication(int m, int n)
{
    if (n == 0) //Base case
    {
        return 0;
    }

    int ans = multiplication(m, n-1); //Induction Hypothesis
    return m + ans; //Induction Step
}
