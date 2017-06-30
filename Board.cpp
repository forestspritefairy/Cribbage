/*--------------------------------------------------------------------
// file name:	Board.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		06/25/2017
// description: A representation of a Cribbage board. Controls the deck
//              and Player classes. The play method acts as the driver for
//              the program.
// variables:	a bool representing if it is player1's turn or player2's
//              turn. Deck that is in charge of dealing the cards and
//              getting the cut for the board. Players 1 and 2 that
//              are the players in the game. A vector that is the crib cards
//--------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		main
// description:	Starts the Game by making a Board and calling play.
//----------------------------------------------------------------*/
int main() {
    Board *b = new Board();
    b->play();
}

/*------------------------------------------------------------------
// name:		Board
// description:	The default constructor for the Board it sets the
//              Players and deck.
// parameters:	none
// called by:	main
//----------------------------------------------------------------*/
Board::Board() {
    int difficulty = intro();
    player2 = new Computer();
    deck = new Deck();
}

/*------------------------------------------------------------------
// name:		hasWon
// description:	check to see if either player has won the game.
// parameters:	none
// returns:		a bool that is true if someone has won.
// called by:	play, pegging
//----------------------------------------------------------------*/
bool Board::hasWon() {
     return (player1->getScore() > 120 || player2->getScore() > 120);
}

/*------------------------------------------------------------------
// name:		deal
// description:	resets the players hands
// parameters:	none
// returns:		none
// called by:	play
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		play
// description:	the driver for this program. It loops through the play
//              of the game until one of the players has won the game.
// parameters:	none
// returns:		none
// called by:	main
//----------------------------------------------------------------*/
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
        vector<int> p1Score = calculateHandScore(player1->getHoldingHand(), *cut);
        vector<int> p2Score = calculateHandScore(player2->getHoldingHand(), *cut);

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

/*------------------------------------------------------------------
// name:		pegging
// description:	allows all the players to take turns pegging. This is
//              done through a large while loops that tracks to see if
//              all players have played their hands. It will give points
//              to players who score points here.
// parameters:	a bool representing who starts the pegging stage.
// returns:		a bool that tells the play method if anyone has won.
// called by:	play
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		inARow
// description:	given a vector checks to see if that vecotor is all in
//              a row that is each number is one larger then the previous.
// parameters:	vector being checked.
// returns:		bool that says wether or not the vector is in a row.
// called by:	checkForPeggingPoints
//----------------------------------------------------------------*/
bool Board::inARow(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 1; i < v.size(); i++) 
        if (v[i - 1] + 1 != v[i]) return false;
    return true;
}

/*------------------------------------------------------------------
// name:		checkForPeggingPoints
// description:	given a vector of cards and an int, checks to see if
//              any points are awarded. Points can come from the vector
//              containing same id Cards, cards in a row, nubs, or having
//              sum equal to 15 / 31.
// parameters:	vector of the past cards, int of the current sum.
// returns:		int that is the number of points awarded.
// called by:	pegging
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		printTable
// description:	prints the summary for the round. It clears the console
//              screen, then prints a table that shows where points were
//              given and the total points for each player.
// parameters:	two vectors that are the information of where each player
//              got points.
// returns:		none.
// called by:	play
//----------------------------------------------------------------*/
void Board::printTable(vector<int> p1Scores, vector<int> p2Scores) {
    ClearScreen();
    cout << "Round Scores" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "|Criteria  | Player 1            | Player 2          |" << endl;
    cout << "|----------|---------------------|-------------------|" << endl;
    cout << "|Hand      | Type    Suit        |  Type    Suit     |" << endl;

    vector<Card> holdingHandP1 = player1->getHoldingHand();
    vector<Card> holdingHandP2 = player2->getHoldingHand();

    for (int i = 0; i < holdingHandP1.size(); i++) {
        cout << "|          | " << holdingHandP1[i] << "   |  " << holdingHandP2[i] << "|" << endl;
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

/*------------------------------------------------------------------
// name:		printRoundStart
// description:	prints the information for the players scores.
// parameters:	none
// returns:		none
// called by:	play
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		intro
// description:	gives the player an intro to textcribbage. Prompts them
//              to enter their name(only displays first 10 char) and
//              the difficulty of the computer opponent.
// parameters:	none
// returns:		none
// called by:	play
//----------------------------------------------------------------*/
int Board::intro() {
    cout << "--------------------------------" << endl;
    cout << "*                              *" << endl;
    cout << "*   Welcome to text Cribbage   *" << endl;
    cout << "*                              *" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "Enter your name: ";

    string playerName;
    int i = 0;
    char in;
    for (in = cin.get(); (in != '\n' && in != '\r' && i < 10); in = cin.get(), i++) {
        playerName.push_back(in);
    }
    
    if (i == 10 && in != '\n' && in != '\r') {
        cin.ignore(10000, '\n');
    }

    player1 = new Human(playerName);

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

/*------------------------------------------------------------------
// name:		wordCheck
// description:	takes in a num and formats it to take up two char spaces.
//              that is if the number is less then 10 it adds a space after
// parameters:	num to be formatted
// returns:		string of the formatted number
// called by:	printTable
//----------------------------------------------------------------*/
string wordCheck(int num) {
    return (num < 10 ) ? (to_string(num) + " ") : to_string(num);
}

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console screen. ONLY FOR WINDOWS OPERATING
//              SYSTEMS.
// parameters:	none
// returns:		none
// called by:	Human::printPegging, intro, printTable, printRoundStart
//----------------------------------------------------------------*/
void ClearScreen() {
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
