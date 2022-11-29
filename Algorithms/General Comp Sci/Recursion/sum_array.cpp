//Compile Time
template <size_t Size>
constexpr int sum(const int (&arr)[Size]) //Note the array must be constexpr here
{
    int ret = 0;

    for (int i = 0; i < Size; ++i)
    {
        ret += arr[i];
    }
    
    return ret;
}

//Normal Variant
int sum_array_recursion(int* a, const size_t sz)
{
    if (sz == 0) //Base case
    {
        return 0;
    }

    return a[0] + sum_array_recursion(a + 1, sz - 1); //Induction Hypothesis
}
