#include <iostream>

struct State
{
    virtual void on(LightSwitch* lhs)
    {
        std::cout << "Light is already on";
    }

    virtual void off(LightSwitch* lhs)
    {
        std::cout << "Light is already off";
    }
};

struct OnState : State
{
    OnState()
    {
        std::cout << "Light is turned on\n";
    }

    void off(LightSwitch* lhs) override
    {
        std::cout << "Switching light off...\n";
        lhs->set_state(new OffState());
        delete this;
    }
};

struct OffState : State
{
    OffState()
    {
        std::cout << "Light is turned off\n";
    }

    void on(LightSwitch* lhs) override
    {
        std::cout << "Switching light on...\n";
        lhs->set_state(new OnState());
        delete this;
    }
};

class LightSwitch
{
    State *state;
    public:
    LightSwitch()
    {
        state = new OffState();
    }

    void set_state(State* state)
    {
        this->state = state;
    }

    void on() 
    {
        state->on(this);
    }
    void off() 
    {
        state->off(this);
    }

};

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();

    return 0;
}