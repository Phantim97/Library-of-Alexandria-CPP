//Metaprogramming Variant
template<int N>
struct CountZeros
{
    static const int value = (N % 10 == 0) + CountZeros<N/10>::value; //Induction Step & Induction Hypothesis ((N%10 == 0) + CountZeros<N/10>::value)
};

template<>
struct CountZeros<0>
{
    static const int value = 0; //Base Case
};

//Normal Variant
int count_zeros(int n)
{
    if (n == 0) //Base case
    {
        return 0;
    }

    int ans = count_zeros(n /1 0); //Induction Hypothesis
    return (n % 10 == 0) + ans; //Induction Step
}
