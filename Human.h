#pragma once
#include "Player.h"

class Human : public Player {
public:
    Human() { this-> name = "Player 1"; }
    Human(string name) { this->name = name; }

    vector<Card> getCribCards(bool turn);
    string getName() { return name; }
    vector<Card> getHoldingHand() { return holdingHand; }
    int getScore() { return score; }

    Card playCard(vector<Card> pastCards, int sum);
    void print();
    void resetHand(vector<Card> *newHand);
    void addScore(int newScore) { score += newScore; }

private:
    string name;
    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;
    
    bool canPlay(int sum);
    void printPegging(vector<Card> pastCards, int sum);
};