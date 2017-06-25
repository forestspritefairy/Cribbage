#pragma once
#include "Player.h"

class Computer : public Player {

public:
    Card playCard(int turn);
    vector<Card> getCribCards(bool turn);
};
