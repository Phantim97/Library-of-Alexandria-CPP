//Metaprogramming Variant
template<int N, int* A, size_t Size>
struct IsPresent
{
    static const bool value = (A[0] == N) || IsPresent<N, A + 1, Size - 1>::value; //Induction Step & Induction Hypothesis ((A[0] == N) || IsPresent<N, A + 1, Size - 1>::value)
};

template<int N, int* A>
struct IsPresent<N, A, 0>
{
    static const bool value = false; //Base Case
};

//Normal Variant
int element_present(int* a, int target, const int sz)
{
    if (sz == 0) //Base case
    {
        return -1;
    }

    if (a[0] == target)
    {
        return 0;
    }

    int ans = element_present(a + 1, target, sz - 1); //Induction Hypothesis
    if (ans == -1)
    {
        return -1;
    }
    else
    {
        return ans + 1;
    }
}
