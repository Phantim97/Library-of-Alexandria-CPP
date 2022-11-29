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

//Printable Versions
//Metaprogramming Variant
template<int N, char A, char B, char C>
struct TowerOfHanoiSteps
{
    static void print()
    {
        TowerOfHanoiSteps<N - 1, A, C, B>::print(); //Induction Hypothesis
        std::cout << "Move " << N << " from " << A << " to " << C << '\n';
        TowerOfHanoiSteps<N - 1, B, A, C>::print(); //Induction Hypothesis
    }
};

template<char A, char B, char C>
struct TowerOfHanoiSteps<1, A, B, C>
{
    static void print()
    {
        std::cout << "Move 1 from " << A << " to " << C << '\n';
    }
};

//Normal Variant
void tower_of_hanoi_steps(int n, char source, char destination, char helper)
{
    if (n == 0) //Base case
    {
        return;
    }

    tower_of_hanoi_steps(n - 1, source, helper, destination); //Induction Hypothesis
    std::cout << "Move from " << source << " to " << destination << '\n';
    tower_of_hanoi_steps(n - 1, helper, destination, source); //Induction Hypothesis
}
