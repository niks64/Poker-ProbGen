#include "Table.h"

int HR[32487834];

void TestFailed(std::string msg) {
    std::cout << "Test Failed: " << msg << std::endl;
    exit(0);
}

int LookupHand(std::vector<int> cards) {

}

void updateIndices(std::vector<int> indices, int n) {
    int i = indices.size() - 1;
    bool callAgain = false;

    while (i >= 0 && indices[i] >= n - 1) i--;


    if (i < 0) indices[0] = -1;
    else {
        indices[i]++;

        for (int j = i + 1; j < indices.size(); j++) {
            indices[j] = indices[j - 1] + 1;
            if (indices[j] >= n) callAgain = true;
        }

        if (callAgain) updateIndices(indices, n);
    }
}

std::vector<int> ConvertCards(std::vector<Card> cards) {
    std::vector<int> res;

    for (Card c : cards) {
        int s = c.getSuit();
        int v = c.getValue();

        res.push_back((v-2)*4 + s);
    }

    return res;
}

void printProbs(std::vector<double> p) {
    printNewLine(1);
    printf("%s\n", "---- Winning Odds ---");

    int s = p.size();

    for (int i = 0; i < s; i++) {
        printf("%0*.2f%%  ", 5, p[i]);
        printBar();
    }
    
    printNewLine(1);
}

std::vector<double> calcProb(Table t) {
    std::vector<double> res;
    
    // Get player hands 
    std::vector<std::vector<Card>> hands = t.getPlayerCards();
    std::vector<std::vector<int>> convertedHands;
    for (std::vector<Card> c : hands) {
        convertedHands.push_back(ConvertCards(c));
    }

    // Get Board Cards
    std::vector<Card> givenBoard = t.getBoard();
    std::vector<int> convertedGivenBoard = ConvertCards(givenBoard);

    int given = givenBoard.size();
    int remaining = 5 - given;

    // Get the remaining cards in the deck
    std::vector<int> deck = ConvertCards(t.getDeck());
    int n = deck.size();

    // Counters (including one for the total)
    int total = 0;
    std::vector<int> counters(hands.size(), 0);
    
    std::vector<int> boardCards = convertedGivenBoard;
    std::vector<int> indices;
    // Add the remaining cards
    for (int j = 0; j < remaining; j++) {
        boardCards.push_back(deck[j]);
        indices.push_back(j);
    }

    int curr = given;
    bool done = false;

    // For each combination, lookup the player hand and add one to the counter of the winner
    while (!done) {
        int maxVal = -1;
        int highest = 0;

        for (int j = 0; j < convertedHands.size(); j++) {
            std::vector<int> mergedVector;
            mergedVector.insert(mergedVector.end(), convertedHands[j].begin(), convertedHands[j].end());
            mergedVector.insert(mergedVector.end(), boardCards.begin(), boardCards.end());

            int strength = LookupHand(mergedVector);

            if (strength > maxVal) {
                maxVal = strength;
                highest = j;
            }
        }

        counters[highest] += 1;
        total += 1;

        // Update the indices and the board cards
        updateIndices(indices, n);
        
        if (indices[0] < 0) break;

        for (int i = 0; i < remaining; i++) {
            boardCards[given + i] = deck[indices[i]];
        }
    }


    // get probabilities (as a %)

    return res;
}

void playRandom(Table t) {
    t.dealCards(2);
    t.printPlayersCards();
    
    std::vector<double> p = calcProb(t);
    printProbs(p);
}

int main(int argc, char *argv[]) {

    // Load the Table
    memset(HR, 0, sizeof(HR));
    FILE * fin = fopen("./TableGeneration/HandRanks.dat", "rb");
    if (!fin) TestFailed("File did not open.");

    size_t bytesread = fread(HR, sizeof(HR), 1, fin);
    fclose(fin);
    std::cout << "Loaded the Hand Ranks File." << std::endl;


    // Ask configurations of the table:
    // - how many players (n)
    int n;
    std::cout << "Please enter the number of players: " << std::endl;
    std::cin >> n;

    // Setup the Table
    Table t = Table();
    t.addPlayers(n);
    playRandom(t);





    // if deal randomly
        // deal the cards and print probabilities
        // Ask whether any players (1->n) should be folded
        // Deal board and ask whether any players (1->n) should be folded at each step
    // if specify hand
        // Specify hand for each player in the game
        // print probabilities and ask whether any should be folded
        // Deal board and ask whether any players (1->n) should be folded at each step

    // Check whether to deal randomly or enter specific cards
    // bool ifSpecify = false;
    
    // if (argc > 1 && strcmp("-s", argv[1]) == 0) {
    //     ifSpecify = true;
    // }
}