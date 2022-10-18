#include <iostream>
#include <vector>
#include <ostream>

// CRTP (Curiosly Recurring Template Pattern)
template <typename Self>
struct SomeNeurons
{
    template typename<T> 
    void connect_to(T& other)
    {
        for (Neuron& from : *static_cast<Self*>(this)) //allows to enumerate through whatever the type is
        {
            for (Neuron& to : other)
            {
                from.out.push_back(&other);
                to.in.push_back(&from);
            }
        }
    }
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

    Neuron* begin() {return this;}
    Neuron* end() {return this+1;} //finds end address

    void connect_to(Neuron& other) //link neurons
    {
        out.push_back(&other);
        other.in.push_back(this)
    }

    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron)
    {
        for (Neuron* n : neuron.in)
        {
           os << n->id << "    " << neuron.id << '\n';  
        }

        for (Neuron* n : neuron.out)
        {
           os << neuron->id << "    " << n.id << '\n';  
        }

        return os;
    }
};

struct NeuronLayer : std::vector<Neuron>, SomeNuerons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while (count > 0)
        {
            emplace_back(Neuron{});
            count--;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &obj)
    {
        for (auto& n : obj)
        {
            os << n;
        }

        return os;
    }
};

int main()
{
    Neuron n1, n2;
    n1.connect_to(n2);
    std::cout << n1 << n2 <<'\n';

    NeuronLayer layer1{2}, layer2{3};
    n1.connect_to(layer1);
    layer2.connect_to(n2);
    layer1.connect_to(layer2);

    return 0;
}