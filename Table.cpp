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
    deck.erase(this->deck.begin() + idx);

    return returnCard;
}

void Table::createBoardCards(int numCards) {

}

void Table::dealCards(int numCards) {

}

void Table::addPlayers(int numPlayers) {
    
}