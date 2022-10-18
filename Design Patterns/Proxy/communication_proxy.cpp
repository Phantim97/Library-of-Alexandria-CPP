#include <iostream>
#include <string>

struct Pingable
{
    virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable
{
    std::wsting ping(const std::wstring& message) override
    {
        return message + L" pong";
    }
};

void tryit(Pingable &p)
{
    std::wcout << p.ping(L"ping") << '\n';
}

int main()
{
    Pong po;

    for (int i = 0; i < 3; i++)
    {
        tryit(po);
    }

    return 0;
}