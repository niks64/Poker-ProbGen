#include <Card.h>

Card::Card(suit s, value val) {
    this->cardSuit = s;
    this->faceValue = val;
}

suit Card::getSuit() {
    return this->cardSuit;
}

value Card::getValue() {
    return this->faceValue;
}
