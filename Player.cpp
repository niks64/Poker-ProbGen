#include "Player.h"

Player::Player() {}


Hand Player::getHand() {
    return this->hand;
}

void Player::addHand(std::vector<Card> hand) {
    for (Card c : hand) {
        this->hand.addCard(c);
    }
}

void Player::addCard(Card c) {
    this->hand.addCard(c);
} 

void Player::clear() {
    this->hand.clear();
}

void Player::printHand() {
    this->hand.print();
}

