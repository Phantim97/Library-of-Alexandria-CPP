#include <ranges>
#include <iostream>
#include <vector>
#include <string>

void print_result(const std::vector<int>& res)
{
    for (const int i : res)
    {
        std::cout << i << " ";
    }

    std::cout << '\n';
}

void basic_original()
{
    std::vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9}; //As of C++17 you don't need to specify type
    std::vector<int> result; // But if it's empty you have to explicitly define the type

    for (const int i : v)
    {
        if (i % 2 == 0)
        {
            result.push_back(i * i);
        }
    }

    print_result(result);
}

void basic_views()
{
    namespace views = std::views;

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto is_even = [](const int x){return x % 2 == 0;};
    auto square  = [](const int x){return x * x;};

    const std::vector<int> result = v
        | views::filter(is_even)
        | views::transform(square)
        | std::ranges::to<std::vector>();

    print_result(result);
}

void string_original()
{
    std::string data = "10, 15, 20, 25, 30, 35, 40";

    std::vector<int> values;

    size_t start = 0;
    size_t end = data.find(',');
    int count = 0;

    while (count < 2)
    {
        std::string token = data.substr(start, end - start);

        const int n = std::stoi(token);

        if (n % 2 == 0)
        {
            values.push_back(n);
            count++;
        }

        if (end  == std::string::npos)
        {
            break;
        }

        start = end + 1;
        end = data.find(',', start);

    }
}

void string_ex()
{
    namespace views = std::views;

    std::string s = "10, 15, 20, 25, 30, 35, 40";

    auto to_int = [](auto substring)
    {
        const std::string token(substring.begin(), substring.end());
        return std::stoi(token);
    };

    auto is_even = [](const int x) {return x % 2 == 0;};

    const std::vector<int> result = s
        | views::split(',')
        | views::transform(to_int)
        | views::filter(is_even)
        | views::take(2)
        | std::ranges::to<std::vector>();

    print_result(result);
}

int main()
{
    basic_views();
    string_ex();
}