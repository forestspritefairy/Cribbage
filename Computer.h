#pragma once
#include "Player.h"

class Computer : public Player {

public:
    Card playCard(vector<Card> pastCards, int turn);
    vector<Card> getCribCards(bool turn);
};