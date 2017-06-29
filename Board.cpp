#pragma once

#include "Board.h"
#include "Deck.h"
#include "Computer.h"
#include "Human.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int main() {
    Board *b = new Board();
    b->play();
}

Board::Board() {
    player1 = new Human();
    int difficulty = intro();
    player2 = new Computer();
    deck = new Deck();
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
        printRoundStart();
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
    vector<Card> pastCards;

    while (player1CardsPlayed < 4 || player2CardsPlayed < 4) {
        //Player whoes turn it is plays a card.
        //If the value is 0 they could not play.
        Card play;
        if (playTurn) {
            play = player2->playCard(pastCards, sum);
            if(play.id != 0) {
                player2CardsPlayed++;
            }
        } else {
            
            play = player1->playCard(pastCards, sum);
            if(play.id != 0) {
                player1CardsPlayed++;
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
            pastCards.push_back(play);
            
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

int Board::checkForPeggingPoints(vector<Card> pastCards, int sum) {
    int score = 0;

    if (pastCards.size() >= 2) {
        if (pastCards[pastCards.size() - 1].value == pastCards[pastCards.size() - 2].value) {
            if (pastCards.size() >= 4
                && pastCards[pastCards.size() - 2].value == pastCards[pastCards.size() - 3].value
                && pastCards[pastCards.size() - 3].value == pastCards[pastCards.size() - 4].value) {
                //4 of a kind
                score += 12;
            }
            else if (pastCards.size() >= 3
                && pastCards[pastCards.size() - 2].value == pastCards[pastCards.size() - 3].value) {
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
                rowCheck.push_back(pastCards[pastCards.size() - i].value);
            }
            if (inARow(rowCheck)) {
                score += 3;
                int counter = 4;
                while (pastCards.size() >= counter && counter < 8) {
                    rowCheck.push_back(pastCards[pastCards.size() - counter].value);
                    if (inARow(rowCheck)) score++;
                }
            }
        }

    }
    if (sum == 15 || sum == 31) score += 2;

    return score;
}   

void Board::printTable(vector<int> p1Scores, vector<int> p2Scores) {
    ClearScreen();
    cout << "Round Scores" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "|Criteria  | Player 1            | Player 2          |" << endl;
    cout << "|----------|---------------------|-------------------|" << endl;
    cout << "|Hand      | Type    Suit        |  Type    Suit     |" << endl;

    for (int i = 0; i < player1->holdingHand.size(); i++) {
        cout << "|          | " << player1->holdingHand[i] << "   |  " << player2->holdingHand[i] << "|" << endl;
    }
    cout << "|----------|---------------------|-------------------|" << endl;

    cout << "|Scores    | ";
    cout << "15's:      " << wordCheck(p1Scores[0]) << "       | " << "15's:      " << wordCheck(p2Scores[0]) << "     |" << endl;
    cout << "|          | Runs:      " << wordCheck(p1Scores[1]) << "       | " << "Runs:      " << wordCheck(p2Scores[1]) << "     |" << endl;
    cout << "|          | Of a Kind: " << wordCheck(p1Scores[2]) << "       | " << "Of a Kind: " << wordCheck(p2Scores[2]) << "     |" << endl;
    cout << "|          | Nubs:      " << wordCheck(p1Scores[3]) << "       | " << "Nubs:      " << wordCheck(p2Scores[3]) << "     |" << endl;
    cout << "|----------|---------------------|-------------------|" << endl;

    int p1Total = (p1Scores[0] + p1Scores[1] + p1Scores[2] + p1Scores[3]);
    int p2Total = (p2Scores[0] + p2Scores[1] + p2Scores[2] + p2Scores[3]);

    cout << "|Total     | " << wordCheck(p1Total) << "                  | " << wordCheck(p2Total) << "                |" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << endl;
    cout << "Press any key to continue.";
    cin.get();
    cin.get();
}

void Board::printRoundStart() {
    ClearScreen();
    cout << "Scores" << endl;
    cout << "-------------------" << endl;
    cout << "| ";
    player1->print();
    cout << "  |" << endl;
    cout << "| ";
    player2->print();
    cout << "  |" << endl;
    cout << "-------------------" << endl;
    cout << endl;
}

int Board::intro() {
    cout << "--------------------------------" << endl;
    cout << "*                              *" << endl;
    cout << "*   Welcome to text Cribbage   *" << endl;
    cout << "*                              *" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "Enter your name: ";

    char* playerName = new char[10];
    int i = 0;
    char in;
    for (in = cin.get(); (in != '\n' && in != '\r' && i < 10); in = cin.get(), i++) {
        playerName[i] = in;
    }
    
    if (i == 10 && in != '\n' && in != '\r') {
        cin.ignore(10000, '\n');
    }
    player1->setName(playerName, i);

    int diffChoice = 3;
    while(diffChoice > 2 || diffChoice < 0) {
        ClearScreen();
        cout << "Next choose a number representing " << endl;
        cout << "the difficulty of the computer." << endl;
        cout << "Easy : 0" << endl;
        cout << "Medium : 1" << endl;
        cout << "Hard : 2" << endl;
        cout << "Difficulty: ";
        cin >> diffChoice;
    }

    return diffChoice;
}

string wordCheck(int num) {
    return (num < 10 ) ? (to_string(num) + " ") : to_string(num);
}

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
