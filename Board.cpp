/*--------------------------------------------------------------------
// file name:	Board.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
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
#include <iostream>
#include <vector>
#include <algorithm>
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
    cout << "--------------------------------" << endl;
    cout << "*                              *" << endl;
    cout << "*   Welcome to text Cribbage   *" << endl;
    cout << "*                              *" << endl;
    cout << "--------------------------------" << endl << endl;
    cout << "Enter your name: ";

    string playerName;
    char in;
    for (int i = 0, in = cin.get(); (in != '\n' && in != '\r' && i < 10); in = cin.get(), i++) 
        playerName += in;
    
    ClearScreen();
    player1 = new Human(playerName);
    player2 = new Computer();
    deck = new Deck();
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
int Board::checkForPeggingPoints(vector<Card> v, int sum) {
    //Not enough Cards to peg any points
    int s = v.size();
    if(s < 2) return 0;

    int score = 0;
    if (sum == 15 || sum == 31) score += 2;

    //Of a Kind Check
    if (v[s - 1].id == v[s - 2].id) {
        if(s > 2 && v[s - 2].id == v[s - 3].id) 
            if(s > 3 && v[s - 3].id == v[s - 4].id) return 12 + score; //4 of a kind
            else return 6 + score; //3 of a kind
        else return 2 + score; //pair
    }

    //Runs Check.
    if (s > 2) {
        vector<int> rowCheck;
        for (int i = 1; i < 4; i++) rowCheck.push_back(v[s - i].id);
        if (inARow(rowCheck)) { //3 in a row
            score += 3;
            int counter = 4;
            while (s >= counter) {
                rowCheck.push_back(v[v.size() - counter].id);
                if (inARow(rowCheck)) score++;
                else break;
            }
        }
    }
    return score;
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
// name:		pegging
// description:	allows all the players to take turns pegging. This is
//              done through a large while loops that tracks to see if
//              all players have played their hands. It will give points
//              to players who score points here.
// parameters:	a bool representing who starts the pegging stage.
// returns:		a bool that tells the play method if anyone has won.
// called by:	play
//----------------------------------------------------------------*/
bool Board::pegging(bool turn, vector<int> &p1, vector<int> &p2) {
    ClearScreen();
    int sum = 0;
    vector<Card> pastCards;
    p1.push_back(0);
    p2.push_back(0);

    while (player1->getPlayingHand().size() > 0 || player2->getPlayingHand().size() > 0) {
        //If neither player can play then reset the pegging
        if (!(player1->canPlay(sum) || player2->canPlay(sum))) {
            sum = 0;
            pastCards.clear();
        }

        Card play;
        if(turn) play = player2->playCard(pastCards, sum);
        else {
            play = player1->playCard(pastCards, sum);
            ClearScreen();
        }
        
        //Player played a valid Card.
        if (play.id != 0) {
            //ClearScreen();
            pastCards.push_back(play);
            sum += play.value;
            int score = checkForPeggingPoints(pastCards, sum);
            if (score > 0) {
                if (turn) {
                    p2[5] += score;
                    cout << player2->getName();
                } else {
                    p1[5] += score;
                    cout << "You ";
                }
                cout <<"pegged " << score << " points" << endl;
                if(hasWon()) return true;
            }
        }
        turn = !turn;
    }
    return false;
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
        deal();

        //Get the crib cards from players and set them to the crib
        vector<Card> crib = player1->getCribCards(turn);
        vector<Card> cards2 = player2->getCribCards(turn);
        crib.insert(crib.end(), cards2.begin(), cards2.end());

        Card *cut = &deck->draw();
        
        //If the Cut was a Jack then the person whose crib it is gets 2 points
        if (cut->id == 11) {
            if(turn) {
                player1->addScore(2);
                cout << "You gained 2 points from the Jack cut" << endl;
            } else {
                player2->addScore(2);
                cout << "Computer gained 2 points from the Jack cut" << endl;
            }

            if(hasWon()) break;
        }
        //Calculate the hand scores
        vector<int> p1Score = calculateHandScore(player1->getHoldingHand(), *cut);
        vector<int> p2Score = calculateHandScore(player2->getHoldingHand(), *cut);
        vector<int> cribScores = calculateHandScore(crib, *cut);

        //If pegging returns true someone won the game.
        if (pegging(turn, p1Score, p2Score)) break;

        //Adding the points that each player recived.
        int p1Total = p1Score[0] + p1Score[1] + p1Score[2] + p1Score[3] + p1Score[4] + p1Score[5];
        int p2Total = p2Score[0] + p2Score[1] + p2Score[2] + p2Score[3] + p2Score[4] + p2Score[5];
        int cribTotal = cribScores[0] + cribScores[1] + cribScores[2] + cribScores[3] + cribScores[4];
        
        player1->addScore(p1Total);
        player2->addScore(p2Total);
        turn ? player1->addScore(cribTotal) : player2->addScore(cribTotal);

        //Checking to see if either player won.
        if(hasWon()) break;
        printTable(p1Score, p2Score, crib, turn, *cut);
        
        //Change Turn and reset the deck
        turn = !turn;
        deck->resetDeck();
    }
    ClearScreen();
    if (player1->getScore() > 120 && player2->getScore() > 120) {
        if (turn) {
            cout << "Player 2 has won the game. Good Job!" << endl;
        } else {
            cout << "Player 1 has won the game. Good Job!" << endl;
        }
    } else if (player1->getScore() > player2->getScore()) 
        cout << "Player 1 has won the game. Good Job!" << endl;
    else 
        cout << "Player 2 has won the game. Good Job!" << endl;
    
    cin.get();
    cin.get();
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
void Board::printTable(vector<int> p1Scores, vector<int> p2Scores, vector<Card> crib, bool turn, Card cut) {
    ClearScreen();
    cout << "Total Scores" << endl;
    cout << "-------------------" << endl;
    cout << "| ";
    player1->print();
    cout << "  |" << endl;
    cout << "| ";
    player2->print();
    cout << "  |" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    cout << "Round Scores" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "|Criteria  |";

    string p1Name = player1->getName();
    string p2Name = player2->getName();
    printName(p1Name);
    printName(p2Name);
    if(turn) printName(p1Name + "'s Crib");
    else printName(p2Name + "'s Crib");
    cout << endl;

    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Hand      | Type    Suit        | Type    Suit        | Type    Suit        |" << endl;

    vector<Card> holdingHandP1 = player1->getHoldingHand();
    vector<Card> holdingHandP2 = player2->getHoldingHand();
    vector<int> cribScores = calculateHandScore(crib, cut);

    for (int i = 0; i < holdingHandP1.size(); i++) 
        cout << "|          | " << holdingHandP1[i] << "   | " << holdingHandP2[i] << "   | " << crib[i] << "   |" << endl;
    
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Cut       | " << cut << "   | " << cut << "   | " << cut << "   |" << endl;
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;
    cout << "|Scores    | 15's:      " << format(p1Scores[0]) << "       | 15's:      " 
         << format(p2Scores[0]) << "       | 15's:      " << format(cribScores[0]) << "       |" << endl;
    cout << "|          | Runs:      " << format(p1Scores[1]) << "       | Runs:      " 
         << format(p2Scores[1]) << "       | Runs:      " << format(cribScores[1]) << "       |" << endl;
    cout << "|          | Of a Kind: " << format(p1Scores[2]) << "       | Of a Kind: " 
         << format(p2Scores[2]) << "       | Of a Kind: " << format(cribScores[2]) << "       |" << endl;
    cout << "|          | Flush:     " << format(p1Scores[3]) << "       | Flush:     " 
         << format(p2Scores[3]) << "       | Flush:     " << format(cribScores[3]) << "       |" << endl;
    cout << "|          | Nubs:      " << format(p1Scores[4]) << "       | Nubs:      " 
         << format(p2Scores[4]) << "       | Nubs:      " << format(cribScores[4]) << "       |" << endl;
    cout << "|          | Pegging:   " << format(p1Scores[5]) << "       | Pegging:   "
        << format(p2Scores[5]) << "       |                     |" << endl;
    cout << "|----------|---------------------|---------------------|---------------------|" << endl;



    int p1Total = (p1Scores[0] + p1Scores[1] + p1Scores[2] + p1Scores[3] + p1Scores[4] + p1Scores[5]);
    int p2Total = (p2Scores[0] + p2Scores[1] + p2Scores[2] + p2Scores[3] + p2Scores[4] + p2Scores[5]);
    int cribTotal = (cribScores[0] + cribScores[1] + cribScores[2] + cribScores[3] + cribScores[4]);

    cout << "|Total     | " << format(p1Total) << "                  | " 
         << format(p2Total) << "                  | " << format(cribTotal) << "                  |" << endl;

    cout << "------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Press any key to continue.";
    cin.get();
    cin.get();
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
    cin.ignore(cin.rdbuf()->in_avail(), '\n');

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

/*------------------------------------------------------------------
// name:		format
// description:	takes in a num and formats it to take up two char spaces.
//              that is if the number is less then 10 it adds a space after
// parameters:	num to be formatted
// returns:		string of the formatted number
// called by:	printTable
//----------------------------------------------------------------*/
string format(int num) {
    return (num < 10) ? (to_string(num) + " ") : to_string(num);
}

/*------------------------------------------------------------------
// name:		printName
// description:	Takes in a name and prints one space before the name
//              as many spaces as need after to make the total length 20
// parameters:	string to be printed
// returns:		none
// called by:	printTable
//----------------------------------------------------------------*/
void printName(string name) {
    cout << " " << name;
    for (int i = name.length(); i < 20; i++) cout << " ";
    cout << "|";
}