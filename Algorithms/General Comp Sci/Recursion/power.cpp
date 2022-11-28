//Metaprogramming Variant
template<int N, int P>
struct Power
{
    static const int value = N * Power<N, P-1>::value; //Induction Step & Induction Hypothesis (N * Power<N, P-1>::value)
};

template<int N>
struct Power<N, 0>
{
    static const int value = 1; //Base Case
};

//Normal Variant
int power(int n, int p)
{
    if (p == 0) //Base case
    {
        return 1;
    }

    int ans = power(n, p-1); //Induction Hypothesis
    return n * ans; //Induction Step
}
