#include <iostream>
#include <string>
#include <vector>

class Person : public Observable<Person>//observable = being monitored
{
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const
    {
        return age;
    }

    void set_age(int age)
    {
        if (age == Person::age)
        {
            return;
        }
        notify(*this, "age");
    }
};

//CRTP
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
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
};

//observer = monitoring

template <typename T>
class Observer
{
    virtual void field_changed(T& src, const std::string field_name) = 0;
};

struct ConsolePersonObserver : public Observer<Person>
{
    private:
        void field_change(Person& src, const std::string field_name)
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