#ifndef TABLE_H
#define TABLE_H
#include "Player.h"

void printNewLine(int n);
void printBar();

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
        std::vector<std::vector<Card>> getPlayerCards();
        std::vector<Card> getBoard();
        std::vector<Card> getDeck();
        int getCurrNumPlayers();
        int getNumCardsRemaining();

        // setters
        void resetAndShuffleDeck();
        Card drawCard();
        void dealBoardCards(int numCards); // burns one card each time called
        void dealCards(int numCards);
        void addPlayers(int numPlayers);
        void removePlayers(int numPlayers);
        void foldPlayer(int index);
        void setBoardCards(std::vector<Card> c);
        void addHand(std::vector<Card> c, int i);
        void useCard(Card c);

        // prints
        void printPlayersNums();
        void printPlayersCards();
        void printBoard();
        void printTable();

};

#endif