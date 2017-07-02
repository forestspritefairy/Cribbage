/*--------------------------------------------------------------------
// file name:	Deck.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: Represents a Deck of Cards in a game of Cribbage. You can
//              draw a card cut the deck to get a random card from the middle
//              or reset the deck back to the original 52 cards.
// variables:	Vector of Cards that contains the cards for the deck.
//--------------------------------------------------------------------*/

#pragma once
#include <vector>
#include "Card.h"

using namespace std;

const int MAX_DECK_VALUE = 13;
const int MAX_SUIT_VALUE = 4;

class Deck {

public:
    /*------------------------------------------------------------------
    // name:		Deck
    // description:	Default constructor for the deck. It resets the deck back
    //              to 52 Cards.
    // called by:	Board::Board
    //----------------------------------------------------------------*/
    Deck() { resetDeck(); }

    /*------------------------------------------------------------------
    // name:		draw
    // description:	gets a random card from the deck and removes it from the deck.
    // parameters:	none
    // returns:		The random Card drawn from the deck.
    // called by:	Board::play, Board::Deal
    //----------------------------------------------------------------*/
    Card draw();

    /*------------------------------------------------------------------
    // name:		resetDeck
    // description:	resets the deck back to the original 52 Cards.
    // parameters:	none
    // returns:		none
    // called by:	Board::play
    //----------------------------------------------------------------*/
    void resetDeck();

private:
    vector<Card> cards;
};