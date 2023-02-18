#ifndef TABLE_H
#define TABLE_H
#include "Player.h"

class Table {
    private:
        const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

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
        int getNumCardsRemaining();

        // setters
        void resetAndShuffleDeck();
        Card drawCard();
        void dealBoardCards(int numCards); // burns one card each time called
        void dealCards(int numCards);
        void addPlayers(int numPlayers);
        void removePlayers(int numPlayers);

        // prints
        void printPlayersCards();
        void printBoard();
        void printTable();

};

#endif