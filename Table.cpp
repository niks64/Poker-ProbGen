#include "Table.h"

void printNewLine(int num) {
    for (int i = 0; i < num; i++) std::cout << std::endl;
}

void printBar() {
    std::cout << "| ";
}

void Table::resetAndShuffleDeck() {
    this->deck.clear();
    this->usedCards.clear();
    this->board.clear();


    // add cards to the deck
    for (int i = 0; i < NUM_SUITS; i++) {
        for (int j = 0; j < NUM_VALUES; j++) {
            suit s = static_cast<suit>(i + 1);
            value v = static_cast<value>(j + 2);
            Card c = Card(s, v);
            this->deck.push_back(c);
        }
    }

    // shuffle cards
    std::mt19937 rng(seed);
    std::shuffle(std::begin(this->deck), std::end(this->deck), rng);
}

std::vector<std::vector<Card>> Table::getPlayerCards() {
    int s = this->players.size();
    std::vector<std::vector<Card>> res;

    for (int i = 0; i < s; i++) {
        res.push_back(this->players[i].getHand().getCards());
    }

    return res;
}

Table::Table() {
    resetAndShuffleDeck();
}

int Table::getNumCardsRemaining() {
    return this->deck.size();
}

Card Table::drawCard() {
    int s = this->deck.size();

    int idx = rand() % s;
    Card returnCard = this->deck[idx];
    this->deck.erase(this->deck.begin() + idx);
    this->usedCards.push_back(returnCard);

    return returnCard;
}

void Table::dealBoardCards(int numCards) {
    this->drawCard();
    for (int i = 0; i < numCards; i++) {
        Card tempCard = this->drawCard();
        board.push_back(tempCard);
    }
}

void Table::dealCards(int numCards) {
    int s = this->players.size();
    std::vector<std::vector<Card>> tempHands(s);

    for (int i  =0; i < numCards; i++) {
        for (int j = 0; j < s; j++) {
            Card tempCard = this->drawCard();
            tempHands[j].push_back(tempCard);
        }
    }

    for (int i = 0; i < s; i++) {
        this->players[i].addHand(tempHands[i]);
    }
}

void Table::addPlayers(int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        this->players.push_back(Player());
    }
}

void Table::removePlayers(int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        this->players.pop_back();
    }
}

std::vector<Player> Table::getAllPlayersInfo() {
    return this->players;
}

std::vector<Card> Table::getBoard() {
    return this->board;
}

int Table::getCurrNumPlayers() {
    return this->players.size();
}


void Table::printPlayersCards() {
    int s = this->players.size();

    printNewLine(1);
    printf("%s\n", "--- Player Cards ---");

    for (int i = 0; i < s; i++) {
        printf("%-*s", TEXAS_HAND_STRING_LENGTH, ("P" + std::to_string(i + 1)).c_str());
        printBar();
    }
    printNewLine(1);

    for (int i = 0; i < s; i++) {
        this->players[i].printHand();
        printBar();
    }
    printNewLine(2);
}

void Table::printBoard() {
    printNewLine(1);
    printf("%s\n", "---- Board ---");
    for (Card c : this->board) {
        c.print();
    }
    printNewLine(2);
}

void Table::printTable() {
    // Print the board
    this->printBoard();

    // Print the player cards
    this->printPlayersCards();
}