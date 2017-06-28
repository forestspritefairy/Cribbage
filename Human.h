#pragma once
#include "Player.h"

class Human : public Player {
public:
    Card playCard(vector<Card> pastCards, int turn);
    vector<Card> getCribCards(bool turn);

private:
    bool canPlay(int sum);
    void printPegging(vector<Card> pastCards, int sum);
};