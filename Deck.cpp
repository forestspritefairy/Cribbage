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
#include "Deck.h"

/*------------------------------------------------------------------
// name:		draw
// description:	gets a random card from the deck and removes it from the deck.
// parameters:	none
// returns:		The random Card drawn from the deck.
// called by:	Board::play, Board::Deal
//----------------------------------------------------------------*/
Card Deck::draw() {
    int random = rand() % (cards.size() - 1);
    Card draw = cards.at(random);
    cards.erase(cards.begin() + random);
    return draw;
}

/*------------------------------------------------------------------
// name:		resetDeck
// description:	resets the deck back to the original 52 Cards.
// parameters:	none
// returns:		none
// called by:	Board:play
//----------------------------------------------------------------*/
void Deck::resetDeck() {
    cards.clear();
    for (int value = 1; value <= MAX_DECK_VALUE; value++) {
        for (int suit = 0; suit < MAX_SUIT_VALUE; suit++) {
            Card c(value, suit);
            cards.push_back(c);
        }
    }
}
