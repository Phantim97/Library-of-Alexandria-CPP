int linear_search(std::vector<int>& v, int target)
{
    for(int i = 0;i < v.size();i++)
    {
        if (v[i] == target)
        {
            return i;
        }
    }

    return -1;
}

int binary_search(std::vector<int>& v, int target)
{
    int start = 0;
    int end = v.size() - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;

        if (v[mid] == target)
        {
            return mid;
        }
        else if (v[mid] < target)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    return -1;
}
