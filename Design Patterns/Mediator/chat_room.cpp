#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declaration
class User;

class ChatRoom
{
private:
	std::vector<std::shared_ptr<User>> users;

public:
	void join(const std::shared_ptr<User>& user);
	void broadcast(const std::string& from, const std::string& message);
	void message(const std::string& from, const std::string& to, const std::string& message);
};

class User
{
private:
	std::string name_;
	ChatRoom* chat_room_ = nullptr;

public:
	explicit User(const std::string& name) : name_(name) {}

	void receive(const std::string& from, const std::string& message)
	{
		std::cout << name_ << " received a message from " << from << ": " << message << std::endl;
	}

	void send(const std::string& message)
	{
		if (chat_room_)
		{
			chat_room_->broadcast(name_, message);
		}
	}

	void send_to(const std::string& to, const std::string& message)
	{
		if (chat_room_)
		{
			chat_room_->message(name_, to, message);
		}
	}

	void set_chat_room(ChatRoom* room)
	{
		chat_room_ = room;
	}

	[[nodiscard]] std::string get_name() const
	{
		return name_;
	}
};

void ChatRoom::join(const std::shared_ptr<User>& user)
{
	users.push_back(user);
	user->set_chat_room(this);
}

void ChatRoom::broadcast(const std::string& from, const std::string& message)
{
	for (const std::shared_ptr<User>& user : users)
	{
		if (user->get_name() != from)
		{
			user->receive(from, message);
		}
	}
}

void ChatRoom::message(const std::string& from, const std::string& to, const std::string& message)
{
	for (const std::shared_ptr<User>& user : users)
	{
		if (user->get_name() == to)
		{
			user->receive(from, message);
			break;
		}
	}
}

int main()
{
	std::shared_ptr<ChatRoom> chat_room = std::make_shared<ChatRoom>();

	std::shared_ptr<User> alice = std::make_shared<User>("Alice");
	std::shared_ptr<User>  bob = std::make_shared<User>("Bob");
	std::shared_ptr<User>  charlie = std::make_shared<User>("Charlie");

	chat_room->join(alice);
	chat_room->join(bob);
	chat_room->join(charlie);

	alice->send("Hello, everyone!");
	bob->send("Hi, Alice!");
	charlie->send_to("Alice", "Hey Alice, how are you?");

	return 0;
}
