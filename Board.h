/*--------------------------------------------------------------------
// file name:	Board.h
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
#include <vector>
#include <string>
#include "Player.h"

class Board {
public:
    /*------------------------------------------------------------------
    // name:		Board
    // description:	The default constructor for the Board it sets the 
    //              Players and deck.
    // parameters:	none
    // called by:	main
    //----------------------------------------------------------------*/
    Board();

    /*------------------------------------------------------------------
    // name:		play
    // description:	the driver for this program. It loops through the play
    //              of the game until one of the players has won the game.
    // parameters:	none
    // returns:		none
    // called by:	main
    //----------------------------------------------------------------*/
    void play();

private:

    /*------------------------------------------------------------------
    // name:		hasWon
    // description:	check to see if either player has won the game.
    // parameters:	none
    // returns:		a bool that is true if someone has won.
    // called by:	play, pegging
    //----------------------------------------------------------------*/
    bool hasWon();

    /*------------------------------------------------------------------
    // name:		deal
    // description:	resets the players hands 
    // parameters:	none
    // returns:		none
    // called by:	play
    //----------------------------------------------------------------*/
    void deal();

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
    bool pegging(bool turn);

    /*------------------------------------------------------------------
    // name:		inARow
    // description:	given a vector checks to see if that vecotor is all in
    //              a row that is each number is one larger then the previous.
    // parameters:	vector being checked.
    // returns:		bool that says wether or not the vector is in a row.
    // called by:	checkForPeggingPoints
    //----------------------------------------------------------------*/
    bool inARow(vector<int> v);
    
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
    int checkForPeggingPoints(vector<Card> pastCards, int sum);

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
    void printTable(vector<int> player1Scores, vector<int> player2Scores);

    /*------------------------------------------------------------------
    // name:		printRoundStart
    // description:	prints the information for the players scores.
    // parameters:	none
    // returns:		none
    // called by:	play
    //----------------------------------------------------------------*/
    void printRoundStart();

    /*------------------------------------------------------------------
    // name:		intro
    // description:	gives the player an intro to textcribbage. Prompts them
    //              to enter their name(only displays first 10 char) and
    //              the difficulty of the computer opponent.
    // parameters:	none
    // returns:		none
    // called by:	play
    //----------------------------------------------------------------*/
    int intro();

    Deck *deck;
    Player *player1;
    Player *player2;
};

/*------------------------------------------------------------------
// name:		wordCheck
// description:	takes in a num and formats it to take up two char spaces.
//              that is if the number is less then 10 it adds a space after
// parameters:	num to be formatted
// returns:		string of the formatted number
// called by:	printTable
//----------------------------------------------------------------*/
string wordCheck(int num);

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console screen. ONLY FOR WINDOWS OPERATING
//              SYSTEMS.
// parameters:	none
// returns:		none
// called by:	Human::printPegging, intro, printTable, printRoundStart
//----------------------------------------------------------------*/
void ClearScreen();