#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

class Memento
{
    int balance;
public:
    Memento(int balance) : balance(balance) {}

    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
    int balance = 0;
public:
    BankAccount(int balance) : balance(balance) {}

    Memento deposit(int amount)
    {
        balance += amount;
        return {balance};
    }

    void restore(const Memento& m)
    {
        balance = m.balance;
    }

    friend std::ostream &operatore<<(std::ostream &os, const BankAccount &account)
    {
        os << "balance: " << account.balance;
        return os;
    }
};

class BankAccount2
{
    int balance{0};
    std::vector<std::shared_ptr<Memento>> changes;
    int current;

    BankAccount2(int balance) : balance(balance)
    {
        changes.emplace_back(std::make_shared<Memento>(balance));
    }

    std::shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        ++changes;
        return m;
    }

    void restore(const std::shared_ptr<Memento>&m)
    {
        if (m)
        {
            balance = m.balance;
            changes.push_back(m);
            current = changes.size() - 1; //adjust current pointer
        }
    }

    std::shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        
        return {};
    }

    std::shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const BankAccount2 Acc2)
    {
        os << "Balance " << Acc2.balance;
        return os;
    }
};

int main()
{
    BankAccount ba{100};
    Memento m1 = ba.deposit(50);
    Memento m2 = ba.deposit(25);

    std::cout << ba << '\n';

    ba.restore(m1);

    std::cout << ba << '\n';

    ba.restore(m2);

    std::cout << ba << '\n';

    BankAccount2 b2a{100};
    b2a.depoist(50);
    b2a.deposit(25);

    b2a.undo();
    b2a.undo();
    b2a.redo();

    return 0;
}