#include "arena.h"

Arena<1024> user_arena;

class User
{
private:
	int id_;
public:
	void* operator new(size_t size)
	{
		return user_arena.allocate(size);
	}

	void operator delete(void* p)
	{
		user_arena.deallocate(static_cast<std::byte*>(p), sizeof(User));
	}

	void* operator new[](size_t size)
	{
		return user_arena.allocate(size);
	}

	void operator delete[](void* p)
	{
		user_arena.deallocate(static_cast<std::byte*>(p), sizeof(User) * 10); // Assuming 10 for example
	}
};

int main()
{
	std::cout << "Arena Size: " << Arena<1024>::size() << '\n';
	std::cout << "User Size: " << sizeof(User) << '\n';

	std::cout << "Allocating user to arena...\n";
	//No dynamic memory is allocated when we create the users
	User* u1 = new User;
	std::cout << "Arena bytes in use: " << user_arena.used() << '\n';

	std::cout << "Deleting User...\n";
	delete u1;
	std::cout << "Arena bytes in use: " << user_arena.used() << '\n';

	std::cout << "Allocating 10 users to arena...\n";
	User* users = new User[10];
	std::cout << "Arena bytes in use: " << user_arena.used() << '\n';
	std::cout << "Deallocating User array\n";
	delete[] users;
	std::cout << "Arena bytes in use: " << user_arena.used() << '\n';

	const std::unique_ptr<User> user2 = std::make_unique<User>(); //Will clean up on exiting scope no need to print here

	return 0;
}
