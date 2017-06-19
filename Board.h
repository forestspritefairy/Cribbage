#pragma once

class Board {
public:
    Board();


private:
    bool hasWon();
    void deal();
    void play();
    void pegging();
    
    bool turn;
    Deck *deck;
    Player *player1;
    Player *player2;
    Card *cut;
    Card * crib;
};