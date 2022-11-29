//Metaprogramming Variant
template<int N>
struct GeometricSum
{
    constexpr static const double value = 1.0 / N + GeometricSum<N-1>::value; //Induction Step & Induction Hypothesis (1.0 / N + GeometricSum<N-1>::value)
};

template<>
struct GeometricSum<1>
{
    constexpr static const double value = 1.0; //Base Case
};

//Normal Variant
double geometric_sum(double n)
{
    if (n == 1.0) //Base case
    {
        return 1.0;
    }

    double ans = geometric_sum(n-1); //Induction Hypothesis
    return 1.0 / n + ans; //Induction Step
}
