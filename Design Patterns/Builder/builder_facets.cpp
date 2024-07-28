#include <iostream>
#include <vector>
#include <string>

class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

//----------------------------------------------------
class Person
{
    //address information
    public:
    std::string street_addr, post_code, city;

    //employment information
    std::string company_name, position;
    int annual_income = 0;

    static PersonBuilder create();

    // std::ostream &operator<<(std::ostream &os, const Person &person)
    // {
    //     os << "street address: " << person.street_addr << "\npost code: " << person.post_code; << "\ncity: " << person.city
    //     << ...

    //     return os;
    // }

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};

std::ostream &operator<<(std::ostream &os, const Person &person)
{
	os << "Street address: " << person.street_addr
	   << "\nPost code: " << person.post_code
	   << "\nCity: " << person.city
	   << "\nCompany name: " << person.company_name
	   << "\nPosition: " << person.position
	   << "\nAnnual income: " << person.annual_income;
	return os;
}


//----------------------------------------------------
class PersonBuilderBase
{
    protected:
    Person &person;
    
    public:
    PersonBuilderBase(Person &person) : person(person) {}

    operator Person() const 
    {
        return std::move(person);
    }

    PersonAddressBuilder lives();
    PersonJobBuilder works();
};

//----------------------------------------------------
class PersonBuilder : public PersonBuilderBase
{
    Person p;
    public:
    PersonBuilder() : PersonBuilderBase(p) {}
};

PersonBuilder Person::create()
{
    return PersonBuilder();
}

//----------------------------------------------------
class PersonAddressBuilder : public PersonBuilderBase
{
    typedef PersonAddressBuilder self;
public:
	PersonAddressBuilder(Person &person) : PersonBuilderBase(person) {}

    self& at(std::string street_address)
    {
        person.street_addr = street_address;
        return *this;
    }

    self& with_post_code(std::string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    self& in(std::string city)
    {
        person.city = city;
        return *this;
    }
};
//----------------------------------------------------
class PersonJobBuilder : public PersonBuilderBase
{
public:
    PersonJobBuilder(Person &p) : PersonBuilderBase(p) {}

    PersonJobBuilder& at(std::string company_name)
    {
        person.company_name = company_name;
        return *this;
    }

    PersonJobBuilder& as_a(std::string job)
    {
        person.position = job;
        return *this;
    }

    PersonJobBuilder& earning(int income)
    {
        person.annual_income = income;
        return *this;
    }
};
//----------------------------------------------------

PersonAddressBuilder PersonBuilderBase::lives()
{
	return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works()
{
	return PersonJobBuilder(person);
}

int main()
{
    Person p = Person::create().lives().at("123 London Road").with_post_code("SW1 1GB").in("London").works().at("PragmaSoft").as_a("Consultant").earning(10e6);

    //with overloaded os stream operator you can simply do:
    std::cout << p << '\n';

    return 0;
}