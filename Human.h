/*--------------------------------------------------------------------
// file name:	Human.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: The human player for the game of crib. This is where most
//              of the human interaction with the game happens.
// variables:   holdingHand which is the hand that gets calculated at the
//              end of each round. playingHand which is a copy of
//              holdingHand used for pegging. score which is the human's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"

class Human : public Player {
public:
    /*------------------------------------------------------------------
    // name:		Human
    // description:	overload constructor that sets the name of the human 
    //              to the string given.
    // parameters:	string which is the name of the player.
    // called by:	Board::intro
    //----------------------------------------------------------------*/
    Human(string name) { this->name = name; }

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	given a bool that tells the player whether or not it
    //              is their turn prompts the human to give two cards to
    //              be put in the crib.
    // parameters:	bool that is whose crib it is.
    // returns:		vector of Cards that is the Cards to be put in the Crib
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getCribCards(bool turn);

    /*------------------------------------------------------------------
    // name:		getName
    // description:	Gets the name of the player.
    // parameters:	none
    // called by:	print
    //----------------------------------------------------------------*/
    string getName() { return name; }

    /*------------------------------------------------------------------
    // name:		getHoldingHand
    // description:	gets the holdingHand from the player.
    // parameters:	none
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getHoldingHand() { return holdingHand; }

    /*------------------------------------------------------------------
    // name:		getScore
    // description:	gets the players current score
    // parameters:	none
    // called by:	Board::hasWon, Board::play
    //----------------------------------------------------------------*/
    int getScore() { return score; }

    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the player the past cards that have been played and
    //              the rounds current sum. Wants the player to choose a Card
    //              to play, if they can't play they return a default Card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    Card playCard(vector<Card> pastCards, int sum);

    /*------------------------------------------------------------------
    // name:		print
    // description:	prints the name of the player and their score.
    // parameters:	none
    // called by:	Board::printRoundStart
    //----------------------------------------------------------------*/
    void print();

    /*------------------------------------------------------------------
    // name:		resetHand
    // description:	resets the players hand by giving them a new vector.
    // parameters:	vector of Cards that is the players new hand.
    // called by:	Board::deal
    //----------------------------------------------------------------*/
    void resetHand(vector<Card> *newHand);

    /*------------------------------------------------------------------
    // name:		addScore
    // description:	adds points to the players score.
    // parameters:	int of the number of points to be added.
    // called by:	Board::play, Board::pegging
    //----------------------------------------------------------------*/
    void addScore(int newScore) { score += newScore; }

private:
    string name;
    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;

    /*------------------------------------------------------------------
    // name:		printCards
    // description:	makes a table of all the cards in the vector.
    // parameters:	vector of cards to be outputted.
    // called by:	printPegging, getCribCard
    //----------------------------------------------------------------*/
    void printCards(const vector<Card> v);

    /*------------------------------------------------------------------
    // name:		canPlay
    // description:	checks to see if the player can play a card given
    //              what they have left in their playingHand and the current
    //              sum.
    // parameters:	int of the current pegging sum
    // called by:	playCard
    //----------------------------------------------------------------*/
    bool canPlay(int sum);

    /*------------------------------------------------------------------
    // name:		printPegging
    // description:	prints out information tables for when the player is pegging
    // parameters:	the pastCards that have been played and the current sum
    // called by:	playCard
    //----------------------------------------------------------------*/
    void printPegging(vector<Card> pastCards, int sum);
};