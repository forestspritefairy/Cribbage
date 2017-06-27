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
    bool turn = true;
    while (true) {
        cout << "--------------------------" << endl;
        cout << "The Scores are." << endl;
        cout << "Player 1: " << player1->getScore() << endl;
        cout << "Player 2: " << player2->getScore() << endl;
        cout << endl;

        deal();

        //Get the crib cards from players and set them to the crib
        vector<Card> crib = player1->getCribCards(turn);
        vector<Card> cards2 = player2->getCribCards(turn);
        crib.insert(crib.end(), cards2.begin(), cards2.end());

        Card *cut = &deck->cut();
        
        //If pegging returns true someone won the game.
        if (pegging(turn)) break;

        //Calculate the hand scores
        vector<int> p1Score = calculateHandScore(player1->holdingHand, *cut);
        vector<int> p2Score = calculateHandScore(player2->holdingHand, *cut);

        printTable(p1Score, p2Score);

        int p1Total = p1Score[0] + p1Score[1] + p1Score[2] + p1Score[3];
        int p2Total = p2Score[0] + p2Score[1] + p2Score[2] + p2Score[3];
        //Checking to see if either player won.
        if (turn) {
            player2->addScore(p2Total);
            if (hasWon()) 
                break;
            
            player1->addScore(p1Total);
            if (hasWon()) break;
            
        }
        else {
            player1->addScore(p1Total);
            if (hasWon()) break;
            
            player2->addScore(p2Total);
            if (hasWon()) break;
        }
        
        //Change Turn and reset the deck
        turn = !turn;
        cout << "Reseting the hands..." << endl;
        deck->resetDeck();
    }

    if (player1->getScore() > player2->getScore()) {
        cout << "Player 1 has won the game. Good Job!" << endl;
    }
    else {
        cout << "Player 2 has won the game. Good Job!" << endl;
    }
    cin.get();
    cin.get();
}

bool Board::pegging(bool turn) {
    int sum = 0;
    int player1CardsPlayed = 0;
    int player2CardsPlayed = 0;
    bool playTurn = turn;
    bool passTrack = false;
    vector<int> pastCards;

    cout << endl;
    cout << "--------------------------" << endl;
    cout << "Begin Pegging." << endl;
    cout << endl;
    while (player1CardsPlayed < 4 || player2CardsPlayed < 4) {
        //Player whoes turn it is plays a card.
        //If the value is 0 they could not play.
        Card play;
        if (playTurn) {
            play = player2->playCard(sum);
            if(play.id != 0) {
                player2CardsPlayed++;
                cout << endl;
                cout << "Player 2 Played:" << endl;
                cout << play;
            }
        } else {
            play = player1->playCard(sum);
            if(play.id != 0) {
                player1CardsPlayed++;
                cout << endl;
                cout << "Player 1 Played:" << endl;
                cout << play;
            }
        }

        //If the payer could not play tell the program that they passed.
        //If the other player had already passed then reset the sum and replay
        if (play.id == 0) {
            if (passTrack) {
                sum = 0;
                pastCards.clear();
                if (playTurn) player2->addScore(1);
                else player1->addScore(1);
            } else passTrack = true;
        //If they could play figure out if they got any points.
        } else {
            passTrack = false;
            sum+= play.value;
            pastCards.push_back(play.id);
            
            int score = checkForPeggingPoints(pastCards, sum);

            if (playTurn) player2->addScore(score);
            else player1->addScore(score);
        }

        //Check if the person who played has won the game.
        if (hasWon()) {
            return true;
            //End The program 
        }
        playTurn = !playTurn;
    }
    return false;
}

bool Board::inARow(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 1; i < v.size(); i++) 
        if (v[i - 1] + 1 != v[i]) return false;

    return true;
}

int Board::checkForPeggingPoints(vector<int> pastCards, int sum) {
    int score = 0;

    if (pastCards.size() >= 2) {
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
                rowCheck.push_back(pastCards[pastCards.size() - i]);
            }
            if (inARow(rowCheck)) {
                score += 3;
                int counter = 4;
                while (pastCards.size() >= counter && counter < 8) {
                    rowCheck.push_back(pastCards[pastCards.size() - counter]);
                    if (inARow(rowCheck)) score++;
                }
            }
        }

    }
    if (sum == 15 || sum == 31) score += 2;

    return score;
}

void Board::printTable(vector<int> p1Scores, vector<int> p2Scores) {
    cout << endl;
    cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "|Criteria  | Player 1            | Player 2    " << endl;
    cout << "|----------|---------------------|--------------------"<< endl;
    cout << "|Hand      | ";

    cout << "Type    Suit        |  Type    Suit" << endl;

    for (int i = 0; i < player1->holdingHand.size(); i++) {
        cout << "|          | " << player1->holdingHand[i] << "   |  " << player2->holdingHand[i] << endl;
    }
    cout << "|----------|---------------------|--------------------" << endl;

    cout << "|Scores    | ";
    
    cout << "15's:      " << p1Scores[0] << "        | " << "15's:      " << p2Scores[0] << endl;
    cout << "|          | Runs:      " << p1Scores[1] << "        | " << "Runs:      " << p2Scores[1] << endl;
    cout << "|          | Of a Kind: " << p1Scores[2] << "        | " << "Of a Kind: " << p2Scores[2] << endl;
    cout << "|          | Nubs:      " << p1Scores[3] << "        | " << "Nubs:      " << p2Scores[3] << endl;
    cout << "|----------|---------------------|--------------------" << endl;

    int p1Total = (p1Scores[0] + p1Scores[1] + p1Scores[2] + p1Scores[3]);
    int p2Total = (p2Scores[0] + p2Scores[1] + p2Scores[2] + p2Scores[3]);

    cout << "|Total     | " << p1Total;
    if(p1Total < 10) cout << " ";

    cout << "                  | " << p2Total << endl;
   // cout << "|          | Total:     " << (p1Scores[0] + p1Scores[1] + p1Scores[2] + p1Scores[3]) << "        | " 
   //      << "Total:     " << (p2Scores[0] + p2Scores[1] + p2Scores[2] + p2Scores[3]) << endl;
    cout << "------------------------------------------------------" << endl;
    cout << endl;
}

ostream& print(ostream& out, const int num) {
    if (num < 10) out << num << " ";
    out << num;
    return out;
}

string wordCheck(int num) {
    if(num < 10 ) return num + " ";
    return num + "";
}
