#include "Table.h"

int HR[32487834];

void TestFailed(std::string msg) {
    std::cout << "Test Failed: " << msg << std::endl;
    exit(0);
}

void printVector(std::vector<int> v) {
    for (int c : v) std::cout << c << " ";
    std::cout << std::endl;
}

int LookupHand(std::vector<int> cards) {
    int p = 53;

    for (int c : cards) {
        p += c;
        p = HR[p];
    }

    return p;
}

void updateIndices(std::vector<int> &indices, int n) {
    int i = indices.size() - 1;
    bool callAgain = false;

    while (i >= 0 && indices[i] >= n - (indices.size() - i)) i--;


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
    
    printNewLine(2);
}

std::vector<int> convertStringToVector(const std::string& input)
{
    std::vector<int> result;
    std::stringstream ss(input);
    int num;
    while (ss >> num)
    {
        result.push_back(num);
        ss.ignore();
    }
    return result;
}

void askFold(Table &t) {
    std::string input;
    std::cout << "Input folded player nums (CSV) (n for none): \n";
    //std::getline(std::cin, input);
    std::cin >> input;
    
    if (input == "n") return;
    
    std::vector<int> inp = convertStringToVector(input);

    for (int i : inp) {
        t.foldPlayer(i);
    }
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

    // For each combination, lookup the player hand and add one to the counter of the winner
    while (true) {
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
        if (indices.size() == 0) break;
        // Update the indices and the board cards
        updateIndices(indices, n);
        
        if (indices[0] < 0) break;
        for (int i = 0; i < remaining; i++) {
            boardCards[given + i] = deck[indices[i]];
        }
    }

    // get probabilities (as a %)
    for (int i = 0; i < counters.size(); i++) {
        res.push_back(((static_cast<double>(counters[i])) / total) * 100);
    }

    return res;
}

void playRandom(Table t) {
    int n = t.getCurrNumPlayers();

    // Deal cards to the players
    t.dealCards(2);
    std::vector<double> p = calcProb(t);
    t.printTable();
    printProbs(p);

    // Ask to continue
    askFold(t);

    // Flop
    t.dealBoardCards(3);
    p = calcProb(t);
    t.printTable();
    printProbs(p);
    
    // Ask to continue
    askFold(t);

    // Turn
    t.dealBoardCards(1);
    p = calcProb(t);
    t.printTable();
    printProbs(p);
    
    // Ask to continue
    askFold(t);
    
    // River
    t.dealBoardCards(1);
    p = calcProb(t);
    t.printTable();
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