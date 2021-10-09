
#include <iostream>
#include <vector>

int fast_sigmoid(int x)
{
	float num = x / (1.0f + abs(x));
	if (num < 0)
	{
		num = 0;
	}
	else
	{
		num = 1;
	}
	return num;
}

//1 to 1 neuron
class Neuron1T1
{
private:
	int m_value;
	int m_weight;

public:
	Neuron1T1(int v, int w)
	{
		this->m_value = v;
		this->m_weight = w;
	}

	void setValue(int v)
	{
		this->m_value = v;
	}

	int getValue()
	{
		return this->m_value;
	}

	int getWeight()
	{
		return this->m_weight;
	}

};

//1 to many neuron
class Neuron1TM
{
private:
	int m_value;

public:
	std::vector<int> m_weights;
	Neuron1TM(int v)
	{
		this->m_value = v;
	}

	bool getValue()
	{
		return this->m_value;
	}

};

void simpleAnd()
{
	//x1 && x2
	int b1, b2;
	std::cout << "x1: ";
	std::cin >> b1;
	std::cout << "x2: ";
	std::cin >> b2;
	Neuron1T1 bias(1, -30);
	Neuron1T1 x1(b1, 20);
	Neuron1T1 x2(b2, 20);
	std::cout << "Resulting Weight: \n";
	int res = (bias.getValue()*bias.getWeight()) + (x1.getValue()*x1.getWeight()) + (x2.getValue()*x2.getWeight());
	std::cout << res << '\n';
	std::cout << fast_sigmoid(res);

}

void simpleOr()
{
	//x1 || x2
	int b1, b2;
	std::cout << "x1: ";
	std::cin >> b1;
	std::cout << "x2: ";
	std::cin >> b2;
	Neuron1T1 bias(1, -10);
	Neuron1T1 x1(b1, 20);
	Neuron1T1 x2(b2, 20);
	int res = (bias.getValue()*bias.getWeight()) + (x1.getValue()*x1.getWeight()) + (x2.getValue()*x2.getWeight());
	std::cout << res << '\n';
	std::cout << fast_sigmoid(res);

}

void simpleNot()
{
	//!x
	std::cout << "x1: ";
	int b1;
	std::cin >> b1;
	Neuron1T1 bias(1, 10);
	Neuron1T1 x1(b1, -20);
	std::cout << "Resulting Weight: \n";
	int res = (bias.getValue()*bias.getWeight()) + (x1.getValue()*x1.getWeight());
	std::cout << res << '\n';
	std::cout << fast_sigmoid(res);
}

void conjoinedNot()
{
	// !x1 && !x2
	int b1, b2;
	std::cout << "x1: ";
	std::cin >> b1;
	std::cout << "x2: ";
	std::cin >> b2;
	Neuron1T1 bias(1, 10);
	Neuron1T1 x1(b1, -20);
	Neuron1T1 x2(b2, -20);
	std::cout << "Resulting Weight: \n";
	int res = (bias.getValue()*bias.getWeight()) + (x1.getValue()*x1.getWeight()) + (x2.getValue()*x2.getWeight());
	std::cout << res << '\n';
	std::cout << fast_sigmoid(res);
}

void simpleXNOR()
{
	int b1;
	int b2;
	
	Neuron1TM bias0(1); 
	bias0.m_weights.push_back(-30);
	bias0.m_weights.push_back(10);
	
	Neuron1TM bias1(1);
	bias1.m_weights.push_back(-10);
	
	std::cout << "x1: ";
	std::cin >> b1;
	Neuron1TM x1(b1);
	x1.m_weights.push_back(20);
	x1.m_weights.push_back(-20);
	
	std::cout << "x2: ";
	std::cin >> b2;
	Neuron1TM x2(b2);
	x2.m_weights.push_back(20);
	x2.m_weights.push_back(-10);

	int a1_in = (bias0.m_weights[0] * 1) + (x1.getValue()*x1.m_weights[0]) + (x2.getValue()*x2.m_weights[0]);
	int a2_in = (bias0.m_weights[1] * 1) + (x1.getValue()*x1.m_weights[1]) + (x2.getValue()*x2.m_weights[1]);

	a1_in = (int)round(fast_sigmoid(a1_in));
	a2_in = (int)round(fast_sigmoid(a2_in));

	Neuron1TM a1(a1_in);
	a1.m_weights.push_back(20);
	Neuron1TM a2(a2_in);
	a2.m_weights.push_back(20);

	int hypothesis = (bias1.m_weights[0] * bias1.getValue()) + (a1.getValue()*a1.m_weights[0]) + (a2.getValue()*a2.m_weights[0]);

	std::cout << fast_sigmoid(hypothesis) << '\n';
}

void sandbox()
{
	int b1, b2;
	std::cin >> b1;
	std::cin >> b2;
	Neuron1T1 bias(1, 10);
	Neuron1T1 x1(b1, -20);
	Neuron1T1 x2(b2, -20);
	int res = (bias.getValue()*bias.getWeight()) + (x1.getValue()*x1.getWeight()) + (x2.getValue()*x2.getWeight());
	std::cout << res << '\n';
	std::cout << fast_sigmoid(res);
}

int main()
{
	sandbox();
	return 0;
}
