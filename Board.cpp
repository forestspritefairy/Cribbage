#pragma once

#include "Board.h"
#include "Deck.h"
#include "Computer.h"
#include "Human.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    Board *b = new Board();
    b->play();
}

Board::Board() {
    deck = new Deck();
    player1 = new Human();
    player2 = new Computer();
    
    turn = true;
}

bool Board::hasWon() {
     return (player1->getScore() > 120 || player2->getScore() > 120);
}

void Board::deal() {
    vector<Card> cards1;
    vector<Card> cards2;
    for (int i = 0; i < 6; i++) {
        cards1.push_back(deck->draw());
        cards2.push_back(deck->draw());
    }

    player1->resetHand(&cards1);
    player2->resetHand(&cards2);
}

void Board::play() {
    while (true) {
        cout << "The Scores are." << endl;
        cout << "Player 1: " << player1->getScore() << endl;
        cout << "Player 2: " << player2->getScore() << endl;
        
        //Deal Cards
        deal();

        //Get the crib cards from players and set them to the crib
        vector<Card> cards1 = player1->getCribCards(turn);
        vector<Card> cards2 = player2->getCribCards(turn);

        for (int i = 0; i < 2; i++) {
            crib.push_back(cards1.at(i));
            crib.push_back(cards2.at(i));
        }
        Card *cut = &deck->cut();
        
        //Pegging
        pegging();

        //Calculate the hand scores
        if (turn) {
            player2->calculateHandScore(*cut);
            if (hasWon()) 
                break;
            
            player1->calculateHandScore(*cut);
            if (hasWon()) break;
            
        }
        else {
            player1->calculateHandScore(*cut);
            if (hasWon()) break;
            
            player2->calculateHandScore(*cut);
            if (hasWon()) break;
        }

        //Change Turn and reset the deck
        turn = !turn;
        deck->resetDeck();
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
        //Player whoes turn it is plays a card.
        //If the value is 0 they cant play.
        int play;
        if (playTurn) {
            play = player2->playCard(sum);
            if(play != 0) player2CardsPlayed++;
        } else {
            play = player1->playCard(sum);
            if(play != 0) player1CardsPlayed++;
        }

        //If the payer could not play tell the program that they passed.
        //If the other player had already passed then reset the sum and replay
        if (play == 0) {
            if (passTrack) {
                sum = 0;
                pastCards.clear();
                if (playTurn) player2->addScore(1);
                else player1->addScore(1);
            } else passTrack = true;
        //If they could play figure out if they got any points.
        } else {
            passTrack = false;
            sum+= play;
            int score = 0;
            pastCards.push_back(play);
            if(pastCards.size() >= 2){
                if (pastCards[pastCards.size() - 1] == pastCards[pastCards.size() - 2]) {
                    if (pastCards.size() >= 4 
                        && pastCards[pastCards.size() - 2] == pastCards[pastCards.size() - 3] 
                        && pastCards[pastCards.size() - 3] == pastCards[pastCards.size() - 4]) {
                        //4 of a kind
                        score += 12;
                    }
                    else if (pastCards.size() >= 3
                        && pastCards[pastCards.size() - 2] == pastCards[pastCards.size() - 3]) {
                        //3 of a kind
                        score += 6;
                    }
                    else {
                        //2 of a kind
                        score += 2;
                    }
                }
            }
            else {
                //3 in a row
                
                if (pastCards.size() >= 3) {
                    vector<int> rowCheck;
                    for (int i = 1; i < 4; i++) {
                        rowCheck.push_back(pastCards.at(pastCards.size() - i));
                    }
                    if (inARow(rowCheck)) {
                        score += 3;
                        int counter = 4;
                        while (pastCards.size() >= counter && counter < 8) {
                            rowCheck.push_back(pastCards.at(pastCards.size() - counter));
                            if(inARow(rowCheck)) score++;
                        }
                    }
                }
                
            }

            if (sum == 15 || sum == 31) score += 2;

            if (playTurn) player2->addScore(score);
            else player1->addScore(score);
        }

        //Check if the person who played has won the game.
        if (hasWon()) {
            //End The program 
        }
        playTurn = !playTurn;
    }
}

bool Board::inARow(vector<int> v)
{
    sort(v.begin(), v.end());
    for (int i = 1; i < v.size(); i++) {
        if (v.at(i - 1) + 1 != v.at(i)) {
            return false;
        }
    }
    return true;
}
