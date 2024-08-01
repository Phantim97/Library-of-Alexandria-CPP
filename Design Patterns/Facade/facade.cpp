#include <iostream>
#include <string>

class DVDPlayer
{
public:
	void on()
	{
		std::cout << "DVD Player is on\n";
	}

	void play(const std::string &movie)
	{
		std::cout << "Playing movie: " << movie << "\n";
	}

	void stop()
	{
		std::cout << "Stopping the movie\n";
	}

	void off()
	{
		std::cout << "DVD Player is off\n";
	}
};

class Amplifier
{
public:
	void on()
	{
		std::cout << "Amplifier is on\n";
	}

	void setVolume(int level)
	{
		std::cout << "Setting volume to " << level << "\n";
	}

	void off()
	{
		std::cout << "Amplifier is off\n";
	}
};

class Projector
{
public:
	void on()
	{
		std::cout << "Projector is on\n";
	}

	void wideScreenMode()
	{
		std::cout << "Projector in widescreen mode\n";
	}

	void off()
	{
		std::cout << "Projector is off\n";
	}
};

class HomeTheaterFacade
{
private:
	DVDPlayer &dvd_player_;
	Amplifier &amplifier_;
	Projector &projector_;

public:
	HomeTheaterFacade(DVDPlayer &dvd, Amplifier &amp, Projector &proj) : dvd_player_(dvd), amplifier_(amp), projector_(proj)
	{
	}

	void watchMovie(const std::string &movie)
	{
		std::cout << "Get ready to watch a movie...\n";
		projector_.on();
		projector_.wideScreenMode();
		amplifier_.on();
		amplifier_.setVolume(10);
		dvd_player_.on();
		dvd_player_.play(movie);
	}

	void endMovie()
	{
		std::cout << "Shutting down the home theater...\n";
		dvd_player_.stop();
		dvd_player_.off();
		amplifier_.off();
		projector_.off();
	}
};

int main()
{
	DVDPlayer dvd_player;
	Amplifier amplifier;
	Projector projector;

	HomeTheaterFacade homeTheater(dvd_player, amplifier, projector);

	homeTheater.watchMovie("Inception");
	homeTheater.endMovie();

	return 0;
}
