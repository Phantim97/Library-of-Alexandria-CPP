#include <iostream>
#include <functional>
#include <string>
#include <sstream>

struct Logger
{
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()> &func, const std::string &name) : func(func), name(name) {}

    void operator()() const
    {
        std::cout << "Entering " << name << '\n';
        func();
        std::cout << "Exiting " << name << '\n'; 
    }
    
};

template <typename Func>
struct Logger2
{
    Func func;
    std::string name;

    Logger2(const Func &func, const std::string &name) : func(func), name(name){}

    void operator()() const
    {
        std::cout << "Entering " << name << '\n';
        func();
        std::cout << "Exiting" << name << '\n';
    }
};

template <typename Func> auto make_logger2(Func func, const std::string &name)
{
    return Logger2<Func>{func, name};
}

double add(double a, double b)
{
    std::cout << a << " + " << b << " = " << a+b << '\n';
    return a+b;
}

//partial specialization
template <typename> struct Logger3;

template<typename R, typename... Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> func;
    std::string name;

    Logger3( const std::function<R(Args...)> &func, const std::string &name) : func(func), name(name) {}

    R operator() (Args ...args)
    {
        std::cout << "Entering " << name << '\n';
        R result  =  func(args...);
        std::cout << "Exiting " << name << '\n';
        return result;
    }
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string& name)
{
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

int main()
{
    Logger([]() {std::cout << "Hello\n";}, "HelloFunction")();

    auto log = make_logger2([]() {std::cout << "Hello\n";}, "HelloFunction");
    log();

    auto logged_add = make_logger3(add, "AddFunction");
    auto result = logged_add(2.0, 3.0);
    std::cout << result << '\n';
    return 0;
}