#ifndef TABLE_H
#define TABLE_H
#include <Player.h>
#include <random>
#include <algorithm>

class Table {
    private:
        std::default_random_engine rng = std::default_random_engine {};
        const int MAX_PLAYERS = 8;
        std::vector<Card> deck;
        std::vector<Card> usedCards;
        std::vector<Card> board;
        std::vector<Player> players;
    public:

        
        Table();
        
        // setters
        void resetAndShuffleDeck();
        Card drawCard();
        void createBoardCards(int numCards); // burns one card
        void dealCards(int numCards);
        void addPlayers(int numPlayers);
        void removePlayers(int numPlayers);
        
        // getters
        std::vector<Player> getAllPlayersInfo();
        std::vector<Card> getBoard();
        int getCurrNumPlayers();

        // prints
        void printPlayersCards();
        void printBoard();
        void print();
        

};

#endif