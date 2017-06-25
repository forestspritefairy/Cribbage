#include "Computer.h"

int Computer::playCard(int sum) {
    for (int i = 0; i < playingHand.size(); i++) {
        int cardVal = playingHand.at(i).value;
        if (cardVal + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return cardVal;
        }
    }
    //Can't Play
    return 0;
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
