#include <iostream>
#include <vector>
#include <ostream>

struct Neuron;

template <typename Self>
struct SomeNeurons
{
	template <typename T>
	void connect_to(T& other);
};

struct Neuron : SomeNeurons<Neuron>
{
	std::vector<Neuron *> in, out; // vector of neuron pointers
	unsigned int id;
	Neuron()
	{
		static int id = 1;
		this->id = id++;
	}

	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; } // finds end address

	friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron)
	{
		for (Neuron* n : neuron.in)
		{
			os << n->id << " -> " << neuron.id << '\n';
		}

		for (Neuron* n : neuron.out)
		{
			os << neuron.id << " -> " << n->id << '\n';
		}

		return os;
	}
};

struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer>
{
	NeuronLayer(int count)
	{
		while (count > 0)
		{
			emplace_back(Neuron{});
			count--;
		}
	}

	Neuron* begin() const { return const_cast<Neuron*>(data()); }
	Neuron* end() const { return const_cast<Neuron*>(data() + size()); }

	friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &obj)
	{
		for (const Neuron& n : obj)
		{
			os << n;
		}

		return os;
	}
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T& other)
{
	for (Neuron& from : *static_cast<Self*>(this)) // allows to enumerate through whatever the type is
	{
		for (Neuron& to : other)
		{
			from.out.push_back(&to);
			to.in.push_back(&from);
		}
	}
}

int main()
{
	Neuron n1, n2;
	n1.connect_to(n2);
	std::cout << n1 << n2 << '\n';

	NeuronLayer layer1{2}, layer2{3};
	n1.connect_to(layer1);
	layer2.connect_to(n2);
	layer1.connect_to(layer2);

	std::cout << layer1 << layer2;

	return 0;
}
