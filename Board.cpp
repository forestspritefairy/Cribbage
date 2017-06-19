#include "Board.h"
#include <vector>
using namespace std;

int main() {
    Board b();
    b.play();

}

Board::Board() {
    deck = new Deck();
    player1 = new player1();
    player2 = new player2();
    
    turn = true;
}

bool Board::hasWon() {
     return (player1.getScore() > 120 || player2.getScore() > 120);
}

void Board::deal() {
    Card *cards1 = new Card[6];
    Card *cards2 = new Card[6];
    for (int i = 0; i < 6; i++) {
        cards1[i] = deck.draw();
        cards2[i] = deck.draw();
    }
    player1.resetHand(cards1);
    player2.resetHand(cards2);
}

void Board::play() {
    while (true) {
        //Deal Cards
        deal();

        //Get the crib cards from players and set them to the crib
        Card *cards1 = player1.getCribCards(turn);
        Card *cards2 = player1.getCribCards(turn);
        for (int i = 0, int j = 0; i < 2; i++, j+=2) {
            crib[j] = cards1[i];
            crib[j+1] =  cards2[i];
        }

        cut = deck.cut();
        
        //Pegging
        pegging();

        //Calculate the hand scores
        if (turn) {
            player2.calculateHandScore(cut);
            if (hasWon()) {
                break;
            }
            player1.calculateHandScore(cut);
            if (hasWon()) {
                break;
            }
        }
        else {
            player1.calculateHandScore(cut);
            if (hasWon()) {
                break;
            }
            player2.calculateHandScore(cut);
            if (hasWon()) {
                break;
            }
        }

        //Change Turn and reset the deck
        turn = !turn;
        deck.resetDeck();
    }
}

void Board::pegging() {
    int sum = 0;
    int player1CardsPlayed = 0;
    int player2CardsPlayed = 0;
    bool playTurn = turn;
    bool passTrack = false;
    vector<int> pastCards;

    while (player1CardsPlayed < 4 || player2CardsPlayed < 4) {
        int play;
        //int play = playTurn ? player2.playCard(sum) : player1.playCard(sum);
        if (playTurn) {
            play = player2.playCard(sum);
            if(play != 0) player2CardsPlayed++;
        }
        else {
            play = player1.playCard(sum);
            if(play != 0) player1CardsPlayed++;
        }
        if (play == 0) {
            if (passTrack) {
                sum = 0;
                pastCards.clear();
                if (playTurn) 
                    player2.addScore(1);
                else 
                    player1.addScore(1);
            }
            else {
                passTrack = true;
            }
        }
        else {
            sum+= play;
            int score = 0;
            pastCards.push_back(play);
            if(pastCards.size >= 2){
                if (pastCards[pastCards.size - 1] == pastCards[pastCards.size - 2]) {
                    if (pastCards.size >= 4 
                        && pastCards[pastCards.size - 2] == pastCards[pastCards.size - 3] 
                        && pastCards[pastCards.size - 3] == pastCards[pastCards.size - 4]) {
                        //4 of a kind
                        score += 12;
                    }
                    else if (pastCards.size >= 3
                        && pastCards[pastCards.size - 2] == pastCards[pastCards.size - 3]) {
                        //3 of a kind
                        score += 6;
                    }
                    else
                    {
                        //2 of a kind
                        score += 2;
                    }
                }
            }
            else {

            }
            if (sum == 15 || sum == 31) {
                score += 2;
            }

        }

        if (hasWon()) {
            //End The program 
        }
    }
}
