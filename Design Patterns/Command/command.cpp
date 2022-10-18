#include <iostream>
#include <vector>

struct BankAccount
{
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount)
    {
        balance += amount;
        std::cout << "Deposited" << amount << " | Balance is " << balance << '\n';
    }

    bool withdraw(int amount)
    {
        if (balance - amount >= overdraft_limit)
        {
            balance -= amount;
            std::cout << "Withdrew " << amount << " | Remaining: " << balance  << '\n';
            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const BankAccount &b)
    {
        std::cout << "Balance: " << b.balance << '\n';
    }
};

struct Command
{
    bool success;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action {deposit, withdraw} action;
    int amount;

    BankAccountCommand(BankAccount &account, Action action, int amount) : account(account), action(action), amount(amount) 
    {
        success = false;
    }

    void call() override
    {
        switch (action)
        {
            case deposit:
                account.deposit(amount);
                success = true;
                break;
            case withdraw:
                success = account.withdraw(amount);
                break;
            default:
                break;
        }
    }

    void undo() override
    {
        if (!success)
        {
            return;
        }

        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;
        case withdraw:
            account.deposit(amount);
            break;
        default:
            break;
        }
    }
};

struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
    CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand> &items) : std::vector(items) {}

    void call() override
    {
        for (auto& cmd : *this)
        {
            cmd.call();
        }
    }

    void undo() override
    {
        for (auto it  = rbegin(); it != rend(); ++it)
        {
            it->undo();
        }
    }
}

struct MoneyTransferCommand : CompositeBankAccountCommand
{
    MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount) : CompositeBankAccountCommand
    (
        {
            BankAccountCommand{from, BankAccountCommand::withdraw, amount}, 
        BankAccountCommand{to, BankAccountCommand::deposit, amount}
        }
    ) {}
};

int main()
{
    BankAccount ba;
    
    std::vector<BankAccountCommand> commands
    {
        BankAccountCommand{ba, BankAccountCommand::deposit, 100},
        BankAccountCommand{ba, BankAccountCommand::withdraw, 200}
    };

    std::cout << ba;

    for (int i = 0; i < commands.size(); i++)
    {
        commands[i].call();
    }

    std::cout << ba;

    return 0;
}