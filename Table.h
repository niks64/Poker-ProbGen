#ifndef TABLE_H
#define TABLE_H
#include "Player.h"

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
        
        // getters
        std::vector<Player> getAllPlayersInfo();
        std::vector<Card> getBoard();
        int getCurrNumPlayers();

        // setters
        void resetAndShuffleDeck();
        Card drawCard();
        void dealBoardCards(int numCards); // burns one card
        void dealCards(int numCards);
        void addPlayers(int numPlayers);
        void removePlayers(int numPlayers);

        // prints
        void printPlayersCards();
        void printBoard();
        void printTable();
        

};

#endif