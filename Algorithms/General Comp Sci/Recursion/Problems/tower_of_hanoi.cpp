//Metaprogramming Variant
template<int N>
struct TowerOfHanoi
{
    static const int value = 2 * TowerOfHanoi<N - 1>::value + 1; //Induction Step & Induction Hypothesis (2 * TowerOfHanoi<N - 1>::value + 1)
};

template<>
struct TowerOfHanoi<1>
{
    static const int value = 1; //Base Case
};

//Normal Variant
int tower_of_hanoi(int n)
{
    if (n == 1) //Base case
    {
        return 1;
    }

    return 2 * tower_of_hanoi(n - 1) + 1; //Induction Hypothesis
}
