//Metaprogramming Variant (May not work until C++23 due to cmath constexpr
template<int N>
struct IsPalindrome
{
    static const bool value = (N % 10 == N / (int)pow(10, (int)log10(N))) && IsPalindrome<N % static_cast<int>(pow(10, (int)log10(N)) / 10)>::value; //Induction Step & Induction Hypothesis ((N % 10 == N / (int)pow(10, (int)log10(N))) && IsPalindrome<N % (int)pow(10, (int)log10(N)) / 10>::value)
};

template<>
struct IsPalindrome<0>
{
    static const bool value = true; //Base Case
};

//Normal Version
bool isPalindrome(int n)
{
    if (n == 0) //Base case
    {
        return true;
    }

    int last_digit = n % 10;
    int first_digit = n / (int)pow(10, (int)log10(n));
    if (last_digit != first_digit)
    {
        return false;
    }

    int small_number = n % (int)pow(10, (int)log10(n)) / 10;
    return isPalindrome(small_number); //Induction Hypothesis
}
