#include <iostream>
#include <vector>

void selection_sort(std::vector<int>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        int min = i;

        for(int j = i+1; j < v.size(); j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }

        if (i != min)
        {
            std::swap(v[i], v[min]);
        }
    }
}

void bubble_sort(std::vector<int>& v)
{
    for (int i = 0; i< v.size(); i++)
    {
        for(int j = 0; j< v.size()-i-1; j++)
        {
            if (v[j] > v[j+1])
            {
                std::swap(v[j],v[j+1]);
            }
        }
    }
}

void merge_sort(std::vector<int>& v)
{
    if (v.size() <= 1)
    {
        return;
    }

    int mid = v.size()/2;

    std::vector<int> left(v.begin(), v.begin()+mid);
    std::vector<int> right(v.begin()+mid, v.end());

    merge_sort(left);
    merge_sort(right);

    int i = 0;
    int j = 0;
    int k = 0;

    while(i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            v[k] = left[i];
            i++;
        }
        else
        {
            v[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < left.size())
    {
        v[k] = left[i];
        i++;
        k++;
    }

    while(j < right.size())
    {
        v[k] = right[j];
        j++;
        k++;
    }
}

void quick_sort(std::vector<int>& v)
{
    if (v.size() <= 1)
    {
        return;
    }

    int pivot = v[0];
    std::vector<int> left;
    std::vector<int> right;

    for(int i=1; i < v.size(); i++)
    {
        if (v[i] < pivot)
        {
            left.push_back(v[i]);
        }
        else
        {
            right.push_back(v[i]);
        }
    }

    quick_sort(left);
    quick_sort(right);

    int i = 0;
    for(int j = 0; j < left.size(); j++)
    {
        v[i] = left[j];
        i++;
    }

    v[i] = pivot;
    i++;

    for(int j = 0 ;j < right.size(); j++)
    {
        v[i] = right[j];
        i++;
    }
}

#include <algorithm>

void radixsort(std::vector<int>& v)
{
    std::vector<int> temp(v.size());

    int max = *std::max_element(v.begin(), v.end());

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        std::vector<int> count(10);

        for (int i = 0; i < v.size(); i++)
        {
            count[(v[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = v.size() - 1; i >= 0; i--)
        {
            temp[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
        }

        for (int i = 0; i < v.size(); i++)
        {
            v[i] = temp[i];
        }
    }
}

void bogosort(std::vector<int>& v)
{
    while(!std::is_sorted(v.begin(), v.end()))
    {
        std::random_shuffle(v.begin(), v.end());
    }
}
