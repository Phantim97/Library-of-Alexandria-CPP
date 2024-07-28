#include <iostream>
#include <string>
#include <sstream>

struct Creature
{
    std::string name;
    int attack, defense;

    explicit Creature(const std::string& name, int attack, int defense) : name(name), attack(attack), defense(defense) {}

    friend std::ostream &operator<<(std::ostream& os, const Creature& c)
    {
        os << "Name: " << c.name << " | attack: " <<  c.attack << " | defense: " << c.defense << '\n';
        return os;
    }


};

//the point is to inherit this class
class CreatureModifier
{
private:
    CreatureModifier* next = nullptr;
protected:
    Creature& creature;
public:
    explicit CreatureModifier(Creature& creature) : creature(creature) {}

    CreatureModifier* add(CreatureModifier *cm)
    {
        if (next) //if next add cm to pointer chain
        {
            next->add(cm);
        }
        else
        {
            next = cm;
        }
        
        return this;
    }

    virtual void handle()
    {
        if (next) //call base handle implementation
        {
            next->handle();
        }
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override
    {
        creature.attack *= 2;
        CreatureModifier::handle(); //how super works in ue4 (invokes base impl)
    }
};

class IncreasedDefenseModifier : public CreatureModifier
{
public:
    explicit IncreasedDefenseModifier(Creature &creature) : CreatureModifier(creature) {}

    void  handle() override
    {
        if (creature.attack <= 2)
        {
            creature.defense++;
        }

        CreatureModifier::handle();
    }
};

class NoBonusesModifier : public CreatureModifier
{
public:
    explicit NoBonusesModifier(Creature &creature) : CreatureModifier(creature) {}

    void handle() override
    {
		//Do nothing, stop the chain
    }

};

int main()
{
    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r2{goblin};
    IncreasedDefenseModifier r3{goblin};

    NoBonusesModifier curse{goblin};
    root.add(&curse);

    root.add(&r1)->add(&r2)->add(&r3);

    root.handle();

    std::cout << goblin << '\n';

    return 0;
}