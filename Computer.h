#pragma once
#include "Player.h"

class Computer : public Player {

public:
    int playCard(int turn);
    vector<Card> getCribCards(bool turn);
};