#pragma once
#include "Player.h"

class Human : public Player {
public:
    int playCard(int turn);
    vector<Card> getCribCards(bool turn);
};