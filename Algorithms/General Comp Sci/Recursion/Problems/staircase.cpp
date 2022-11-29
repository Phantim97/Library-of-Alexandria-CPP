//Metaprogramming Variant
template<int N>
struct Staircase
{
    static const int value = Staircase<N - 1>::value + Staircase<N - 2>::value + Staircase<N - 3>::value; //Induction Step & Induction Hypothesis (Staircase<N - 1>::value + Staircase<N - 2>::value + Staircase<N - 3>::value)
};

template<>
struct Staircase<0>
{
    static const int value = 1; //Base Case
};

//Here I add these extra bounds to avoid recursion stack overflow
template<>
struct Staircase<-1>
{
    static const int value = 0; //Base Case
};

template<>
struct Staircase<-2>
{
    static const int value = 0; //Base Case
};

template<>
struct Staircase<-3>
{
    static const int value = 0; //Base Case
};

//Normal Variant
int staircase_problem(int n)
{
    if (n == 0) //Base case
    {
        return 1;
    }

    if (n < 0) //Base case
    {
        return 0;
    }

    return staircase_problem(n - 1) + staircase_problem(n - 2) + staircase_problem(n - 3); //Induction Hypothesis
}
