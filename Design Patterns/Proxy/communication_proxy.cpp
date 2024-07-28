#include <iostream>
#include <string>

struct Pingable
{
    virtual std::string ping(const std::string& message) = 0;
};

struct Pong : Pingable
{
    std::string ping(const std::string& message) override
    {
        return message + " pong";
    }
};

void tryit(Pingable &p)
{
    std::cout << p.ping("ping") << '\n';
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