#include "Computer.h"

Card Computer::playCard(int sum) {
    for (int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand.at(i);
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }
    //Can't Play
    return Card();
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
