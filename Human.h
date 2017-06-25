#pragma once
#include "Player.h"

class Human : public Player {
public:
    Card playCard(int turn);
    vector<Card> getCribCards(bool turn);
};
