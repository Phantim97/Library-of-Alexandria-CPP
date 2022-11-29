bool check_sorted_array(int* a, const size_t sz)
{
    if (sz == 0 || sz == 1) //Base case
    {
        return true;
    }

    if (a[0] > a[1]) //Base case
    {
        return false;
    }

    return check_sorted_array(a + 1, sz - 1); //Induction Hypothesis
}
