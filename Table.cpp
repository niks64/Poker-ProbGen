#include <Table.h>
#include <cstdlib>

Table::Table() {

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
    std::shuffle(std::begin(this->deck), std::end(this->deck), rng);
}

Card Table::drawCard() {
    int s = this->deck.size();

    int idx = rand() % s;
    Card returnCard = this->deck[idx];
    this->deck.erase(this->deck.begin() + idx);
    this->usedCards.push_back(returnCard);

    return returnCard;
}

void Table::createBoardCards(int numCards) {
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

    for (int i = 0; i < s; i++) {
        std::cout << i << "    ";
    }

    for (int i = 0; i < s; i++) {
        this->players[i].getHand();
    }
}