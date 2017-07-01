#pragma once
#include <vector>
#include "Card.h"

using namespace std;

const int MAX_DECK_VALUE = 13;
const int MAX_SUIT_VALUE = 4;

class Deck {

public:
    Deck();
    Card draw();
    Card cut();
    void resetDeck();

private:
    vector<Card> cards;
};