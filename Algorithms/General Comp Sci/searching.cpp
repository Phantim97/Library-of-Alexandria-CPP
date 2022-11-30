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

//Find first and last occurence of a number in a sorted array
std::pair<int, int> find_first_last(std::vector<int>& v, int target)
{
    int first = -1;
    int last = -1;

    //Find first occurence
    int start = 0;
    int end = v.size() - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;

        if (v[mid] == target)
        {
            first = mid;
            end = mid - 1;
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

    //Find last occurence
    start = 0;
    end = v.size() - 1;

    while (start <= end)
    {
        int mid = start + (end - start) / 2;

        if (v[mid] == target)
        {
            last = mid;
            start = mid + 1;
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

    return std::make_pair(first, last);
}

//Search in rotated sorted array
int search_rotated(std::vector<int>& v, int target)
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

        if (v[start] <= v[mid])
        {
            if (target >= v[start] && target <= v[mid])
            {
                end = mid - 1;
            }
            else
            {
                start = mid + 1;
            }
        }
        else
        {
            if (target >= v[mid] && target <= v[end])
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
    }

    return -1;
}
