#pragma once
#include <vector>

class Board {
public:
    Board();
    void play();

private:
    bool hasWon();
    void deal();
    void pegging();
    bool inARow(vector<int> v);
    
    bool turn;
    Deck *deck;
    Player *player1;
    Player *player2;
    Card *cut;
    Card * crib;
};
