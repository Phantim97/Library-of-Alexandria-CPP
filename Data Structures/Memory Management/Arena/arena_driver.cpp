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

	void operator delete(void* p, size_t size)
	{
		user_arena.deallocate(static_cast<std::byte*>(p), size);
	}
};

int main()
{
	//No dynamic memory is allocated when we create the users
	User* u1 = new User;

	delete u1;

	User* users = new User[10];
	delete[] users;

	std::unique_ptr<User> user2 = std::make_unique<User>();

	return 0;
}
