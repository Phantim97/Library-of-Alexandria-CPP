#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Game
{
    public:
        Game(int num_of_players) : num_of_players(num_of_players) {}

        void run()
        {
            start()
            {
                while(!have_winner())
                {
                    take_turn();
                }
            }

            std::cout << "Player " << get_winner() << "wins.\n";
        }
    proteceted:
        int num_of_players;
        int current_player = 0;
        virtual void start() = 0;
        virtual bool have_winner() = 0;
        virtual void take_turn() = 0;
        virtual int get_winner() = 0;
};

class Chess : public Game
{
public:
    Chess() : Game(2) {}
protected:
        void start() override
        {
            std::cout << "starting a game of chess\n";
        }

        bool have_winner() override
        {
            return false;
        }

        void take_turn() override
        {
            std::cout << "Turn " << turn << "taken by player " << current_player << '\n';
            ++turn;
            current_player = (current_player + 1) % num_of_players;
        }

        int get_winner() override
        {
            return current_player;
        }

private:
    int turn = 0;
    int max_turns = 10;
};

int main()
{
    Chess chess;
    chess.run();

    return 0;
}