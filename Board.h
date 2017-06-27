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
    // returns:		the istream after we are done with it.
    // called by:	main
    //----------------------------------------------------------------*/
    void deal();
    bool pegging(bool turn);
    bool inARow(vector<int> v);
    int checkForPeggingPoints(vector<int> pastCards, int sum);
    
    Deck *deck;
    Player *player1;
    Player *player2;
};