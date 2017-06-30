#include "Computer.h"
#include <string>

Card Computer::playCard(vector<Card> pastCards, int sum) {
    for (int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand[i];
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }
    //Can't Play
    return Card();
}


void Computer::resetHand(vector<Card> *newHand) {
    holdingHand = *newHand;
    playingHand = *newHand;
}

vector<Card> Computer::getCribCards(bool turn) {
    vector<Card> cribCards;
    cribCards.push_back(holdingHand.at(0));
    cribCards.push_back(holdingHand.at(1));

    holdingHand.erase(holdingHand.begin());
    holdingHand.erase(holdingHand.begin());

    playingHand = holdingHand;
    return cribCards;
}

void Computer::print() {
    cout << "Easy Bot   ";
    cout << ((score > 99) ? to_string(score) : (score > 9)
        ? to_string(score) + " " : to_string(score) + "  ");
}
