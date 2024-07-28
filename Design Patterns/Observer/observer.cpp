#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class Observer
{
public:
	virtual void field_changed(T& src, const std::string& field_name) = 0;
};

template <typename T>
class Observable
{
	std::vector<Observer<T>*> observers;
public:
	void notify(T& src, const std::string& field_name)
	{
		for (auto observer : observers)
		{
			observer->field_changed(src, field_name);
		}
	}

	void subscribe(Observer<T>& observer)
	{
		observers.push_back(&observer);
	}

	void unsubscribe(Observer<T>& observer)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), &observer), observers.end());
	}
};

class Person : public Observable<Person> // Person is now observable
{
	int age;
public:
	explicit Person(int age) : age(age) {}

	[[nodiscard]] int get_age() const
	{
		return age;
	}

	void set_age(int a)
	{
		if (this->age == a)
		{
			return;
		}
		this->age = a;
		notify(*this, "a");
	}
};

class ConsolePersonObserver : public Observer<Person>
{
public:
	void field_changed(Person& src, const std::string& field_name) override
	{
		std::cout << "Person's " << field_name << " has changed to ";
		if (field_name == "age")
		{
			std::cout << src.get_age();
		}

		std::cout << '\n';
	}
};

int main()
{
	Person p{10};
	ConsolePersonObserver cpo;
	p.subscribe(cpo);

	p.set_age(20);
	p.set_age(30);

	p.unsubscribe(cpo);

	p.set_age(50);

	return 0;
}
