//Metaprogramming Variant
template<int N>
struct DigitSum
{
    static const int value = N%10 + DigitSum<N/10>::value; //Induction Step & Induction Hypothesis (N%10 + DigitSum<N/10>::value)
};

template<>
struct DigitSum<0>
{
    static const int value = 0; //Base Case
};

//Normal Variant
int dig_sum(int n)
{
    if (n == 0) //Base case
    {
        return 0;
    }
    
    return n % 10 + dig_sum(n/10); //Induction Step & Induction Hypothesis (n % 10 + dig_sum(n/10))
}
