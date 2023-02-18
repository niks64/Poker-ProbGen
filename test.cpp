#include "Table.h"

void test_suit_symbols() {
    for (int i = 1; i<=4; i++) {
        suit s = static_cast<suit>(i);
        std::cout << suitStrings[s] << " ";
    }
    std::cout << std::endl;
}

void test_value_symbols() {
    for (int i = 2; i <= 14; i++) {
        value v = static_cast<value>(i);
        std::cout << valueStrings[v] << " ";
    }
    std::cout << std::endl;
}

void test_card_prints() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 2; j <= 14; j++) {
            Card tmp = Card(static_cast<suit>(i),static_cast<value>(j));
            tmp.print();
        }
        std::cout << std::endl;
    }
}

void test_hand_print() {
    Card c1 = Card(static_cast<suit>(1),static_cast<value>(10));
    Card c2 = Card(static_cast<suit>(2),static_cast<value>(10));

    Hand h = Hand();
    h.addCard(c1);
    h.addCard(c2);

    printf("%-*s\n", TEXAS_HAND_STRING_LENGTH, "P1");
    h.print();

    std::cout << std::endl;
}

void test_player_hand_print() {
    Player p = Player();
    Card c1 = Card(static_cast<suit>(1),static_cast<value>(10));
    Card c2 = Card(static_cast<suit>(2),static_cast<value>(10));

    p.addHand({c1, c2});
    printf("%-*s\n", TEXAS_HAND_STRING_LENGTH, "P1");
    p.printHand();
    std::cout << std::endl;
}

void test_table_print() {
    Table t = Table();

    // Setup the table
    t.addPlayers(4);
    t.dealCards(2);
    t.dealBoardCards(3);
    t.printTable();
}

int main() {

    // test_suit_symbols();
    // test_value_symbols();
    // test_card_prints();
    // test_hand_print();
    // test_player_hand_print();
    test_table_print();

}