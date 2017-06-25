#pragma once
#include "Deck.h"

class Player {

public:
    virtual Card playCard(int turn) = 0;
    virtual vector<Card> getCribCards(bool turn) = 0;

    int getScore() { return score; }
    int calculateHandScore(Card cut);
    void resetHand(vector<Card> *newHand);
    void addScore(int newScore) { score += newScore; }
    

    vector<Card> holdingHand;
    vector<Card> playingHand;

private:
    int score15(Card cut);
    int scoreRuns(Card cut);
    int scoreOfAKind(Card cut);
    int scoreNubs(Card cut);
    int find15(vector<Card> numbers, int index, int sum, int score);

    int score;
    
};

void printCards(vector<Card> v);
void sort(vector<Card> &v);
