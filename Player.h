#pragma once
#include "Deck.h"

class Player {

public:
    virtual Card playCard(vector<Card> pastCards, int turn) = 0;
    virtual vector<Card> getCribCards(bool turn) = 0;
    virtual void setName(char* name, int length) = 0;
    virtual char* getName() = 0;
    virtual int getNameLength() = 0;

    //friend ostream& operator<<(ostream& out, Player& p) {
    //    p.print(out);
    //    return out;
    //}
    virtual void print() = 0;
    int getScore() { return score; }
    
    void resetHand(vector<Card> *newHand);
    void addScore(int newScore) { score += newScore; }
    

    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;

private:
    
};

vector<int> calculateHandScore(vector<Card> hand, Card cut);
int score15(const vector<Card> hand);
int scoreRuns(vector<Card> hand);
int scoreOfAKind(vector<Card> hand);
int scoreNubs(const vector<Card> hand, Card cut);
int find15(const vector<Card> numbers, int index, int sum, int score);

void printCards(const vector<Card> v);
void sort(vector<Card> &v);
