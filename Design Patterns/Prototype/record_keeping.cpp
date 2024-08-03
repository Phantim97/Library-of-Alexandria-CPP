#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Address
{
    std::string street, city;
    int suite;

    Address (const std::string &street, const std::string &city, int suite) : street(street), city(city), suite(suite) {}

    Address (const Address &other) : street(other.street), city(other.city), suite(other.suite) {}

    friend std::ostream& operator<<(std::ostream& os, const Address& address)
    {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

struct Contact
{
    std::string name;
	std::unique_ptr<Address> address;

    Contact(std::string  name, Address *address) : name(std::move(name)), address(address) {}

    Contact (const Contact& other) : name(other.name), address(std::make_unique<Address>(*other.address)){} //copy constructor in address allows to pass the address as pattern

    friend std::ostream& operator<<(std::ostream& os, const Contact &contact)
    {
        std::cout << "name " << contact.name << " address " << *contact.address;
        return os;
    }
};

//Contact main {"", new Address {"123 East Dr", "London", 123}}; Can have global protoype exposed or a factory
struct EmployeeFactory
{
    static std::unique_ptr<Contact> new_main_office_employee(const std::string &name, const int suite)
    {
        static Contact p {"", new Address {"123 East Dr", "London", 0}};
        return new_employee(name, suite, p);
    }
    private:
    static std::unique_ptr<Contact> new_employee(const std::string &name, int suite, const Contact& prototype)
    {
        std::unique_ptr<Contact> result = std::make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

int main()
{
    // Contact john{"John Doe", Address{"123 East Dr", "London", 123}};
    // Contact jane{"Jane Smith", Address{"123 East Dr", "London", 123}};

    const std::unique_ptr<Contact> john = EmployeeFactory::new_main_office_employee("John", 123);

	Contact jane = *john; //shallow copy
	jane.name = "Jane Smith";
	jane.address->suite = 103;

    std::cout << *john << '\n' << jane << '\n';

    return 0;
}