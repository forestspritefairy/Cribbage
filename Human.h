#pragma once
#include "Player.h"

class Human : public Player {
public:
    Card playCard(vector<Card> pastCards, int turn);
    vector<Card> getCribCards(bool turn);
    void setName(char* name, int length);
    char* getName();
    int getNameLength();
    //friend ostream& operator<<(ostream& out, const Human c);
    void print();
private:
    char *name;
    int nameLength;

    
    bool canPlay(int sum);
    void printPegging(vector<Card> pastCards, int sum);
};