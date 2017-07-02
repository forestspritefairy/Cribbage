/*--------------------------------------------------------------------
// file name:	Computer.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A simple computer, that plays cribbage.
// variables:   holdingHand which is the hand that gets calculated at the 
//              end of each round. playingHand which is a copy of 
//              holdingHand used for pegging. score which is the computer's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"

class Computer : public Player {

public:
    const string BOTNAME = "Easy Bot";

    /*------------------------------------------------------------------
    // name:		addScore
    // description:	if the score they send is positive then it adds that to 
    //              the computers total score.
    // parameters:	score to be added to total.
    // called by:	Board::play, Board::pegging
    //----------------------------------------------------------------*/
    void addScore(int newScore) { if(newScore > 0) score += newScore; }

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	gives the computer a bool that represents whether or not it
    //              is their crib and asks them for a vector of cards to be
    //              put in the crib.
    // parameters:	bool of whose crib it is.
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getCribCards(bool turn);

    /*------------------------------------------------------------------
    // name:		getName
    // description:	Gets the name of the Computer.
    // parameters:	none
    // called by:	print
    //----------------------------------------------------------------*/
    string getName() { return BOTNAME; }

    /*------------------------------------------------------------------
    // name:		getHoldingHand
    // description:	gets the hand from the computer.
    // parameters:	none
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getHoldingHand() { return holdingHand; }

    /*------------------------------------------------------------------
    // name:		getScore
    // description:	gets the computer's current score
    // parameters:	none
    // called by:	Board::hasWon, Board::play
    //----------------------------------------------------------------*/
    int getScore() { return score; }

    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the computer the past cards that have been played and
    //              the rounds current sum. Computer always plays the first card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    Card playCard(vector<Card> pastCards, int sum);

    /*------------------------------------------------------------------
    // name:		print
    // description:	prints the name of the computer and their score.
    // parameters:	none
    // called by:	Board::printRoundStart
    //----------------------------------------------------------------*/
    void print();

    /*------------------------------------------------------------------
    // name:		resetHand
    // description:	resets the computer's hand by giving them a new vector.
    // parameters:	vector of Cards that is the players new hand.
    // called by:	Board::deal
    //----------------------------------------------------------------*/
    void resetHand(vector<Card> *newHand);
private:
    
    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;
};