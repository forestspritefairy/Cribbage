/*--------------------------------------------------------------------
// file name:	Player.h
// authors:     Ben Clark, Polina Eremenko
// date:		06/29/2017
// description: A representation of a player in a Cribbage game. Player
//              is a pure abstract class and only serves as a mold for
//              board to call upon.
//--------------------------------------------------------------------*/

#pragma once
#include "Deck.h"
#include <string>

class Player {

public:
    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the player the past cards that have been played and
    //              the rounds current sum. Wants the player to choose a Card
    //              to play, if they can't play they return a default Card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    virtual Card playCard(vector<Card> pastCards, int sum) = 0;

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	gives the player a bool that represents whether or not it
    //              is their crib and asks them for a vector of cards to be 
    //              put in the crib.
    // parameters:	bool of whoes crib it is.
    // called by:	Board::play
    //----------------------------------------------------------------*/
    virtual vector<Card> getCribCards(bool turn) = 0;

    /*------------------------------------------------------------------
    // name:		getName
    // description:	Gets the name of the player.
    // parameters:	none
    // called by:	print
    //----------------------------------------------------------------*/
    virtual string getName() = 0;

    /*------------------------------------------------------------------
    // name:		getHoldingHand
    // description:	gets the hand from the player.
    // parameters:	none
    // called by:	play
    //----------------------------------------------------------------*/
    virtual vector<Card> getHoldingHand() = 0;

    /*------------------------------------------------------------------
    // name:		getScore
    // description:	gets the players current score
    // parameters:	none
    // called by:	main
    //----------------------------------------------------------------*/
    virtual int getScore() = 0;
    virtual void print() = 0;
    virtual void resetHand(vector<Card> *newHand) = 0;
    virtual void addScore(int newScore) = 0;
    
};

vector<int> calculateHandScore(vector<Card> hand, Card cut);
int score15(const vector<Card> hand);
int scoreRuns(vector<Card> hand);
int scoreOfAKind(vector<Card> hand);
int scoreNubs(const vector<Card> hand, Card cut);
int find15(const vector<Card> numbers, int index, int sum, int score);
void printCards(const vector<Card> v);
void sort(vector<Card> &v);