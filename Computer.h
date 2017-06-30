#pragma once
#include "Player.h"

class Computer : public Player {

public:
    const string BOTNAME = "Easy Bot";

    void addScore(int newScore) { score += newScore; }

    vector<Card> getCribCards(bool turn);
    string getName() { return BOTNAME; }
    vector<Card> getHoldingHand() { return holdingHand; }
    int getScore() { return score; }
    Card playCard(vector<Card> pastCards, int sum);
    void print();
    void resetHand(vector<Card> *newHand);
private:
    
    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;
};