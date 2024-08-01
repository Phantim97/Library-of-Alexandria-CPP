#include <iostream>

class LightSwitch;

struct State
{
	virtual void on(LightSwitch *lhs)
	{
		std::cout << "Light is already on\n";
	}

	virtual void off(LightSwitch *lhs)
	{
		std::cout << "Light is already off\n";
	}

	virtual ~State() = default;
};

struct OnState : State
{
	OnState()
	{
		std::cout << "Light is turned on\n";
	}

	void off(LightSwitch *lhs) override;
};

struct OffState : State
{
	OffState()
	{
		std::cout << "Light is turned off\n";
	}

	void on(LightSwitch *lhs) override;
};

class LightSwitch
{
	State* state = nullptr;
public:
	LightSwitch()
	{
		state = new OffState();
	}

	~LightSwitch()
	{
		delete state;
	}

	void set_state(State *state)
	{
		delete this->state;
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

void OnState::off(LightSwitch *lhs)
{
	std::cout << "Switching light off...\n";
	lhs->set_state(new OffState());
	delete this;
}

void OffState::on(LightSwitch *lhs)
{
	std::cout << "Switching light on...\n";
	lhs->set_state(new OnState());
	delete this;
}

int main()
{
	LightSwitch ls;
	ls.on();
	ls.off();
	ls.off();

	return 0;
}
