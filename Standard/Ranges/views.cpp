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

void string_ex()
{
    namespace views = std::views;

    std::string s = "10, 15, 20, 25, 30, 35, 40";

    auto to_int = [](auto s)
    {
        const std::string token(s.begin(), s.end());
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