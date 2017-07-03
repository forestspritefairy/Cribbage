/*--------------------------------------------------------------------
// file name:	Card.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A representation of a Card. Card's contain an id, suit
//              and value. Card has overloads for all the compare operators
//              and an overload for <<.
// variables:	Three ints that define what the card is and its value in
//              Cribbage.
//--------------------------------------------------------------------*/

#pragma once
#include <iostream>

struct Card {
    /*------------------------------------------------------------------
    // name:		Card
    // description:	overload constructor that takes in the Cards id and suit
    //              then calculates the value from those, if id or suit are not
    //              enteredt they default to 0.
    // parameters:	int id and int suit that are going to become those values
    //              in Card.
    // returns:		none
    // called by:	Deck::Deck, Deck::resetHand,Human::playCard, Computer::playCard
    //----------------------------------------------------------------*/
    Card(int id = 0, int s = 0) : id(id), suit(s), value((id < 10) ? id : 10) {};

    /*------------------------------------------------------------------
    // name:		operator>
    // description:	checks to see if this card is greater than the other Card
    //              a Card is greater if it has a larger id. If they have
    //              the same id then its whether the suit is greater.
    // parameters:	Card being compared.
    // returns:		bool that says wether or not this Card is greater
    // called by:	Player::sort
    //----------------------------------------------------------------*/
    bool operator>(const Card & other) const {
        return (this->id > other.id) || (this->id == other.id && this->suit > other.suit);
    }

    /*------------------------------------------------------------------
    // name:		operator<<
    // description:	Gives a standard output form for Card.
    // parameters:	the outstream that card is printed to and the Card to
    //              be printed.
    // returns:		the outstream when we are done with it.
    // called by:	Board::printTable, Human::printPegging, Player::printCards
    //----------------------------------------------------------------*/
    friend std::ostream& operator<<(std::ostream& out, const Card c);

    int id; // numerical value cards, respective. ACE=1 JACK=11 QUEEN=12 KING=14, NO jokers
    int suit; // 0-HEARTS 1-DIAMONDS 2-CLUBS 3-SPADES
    int value; //What the card is worth in cribbiage play.
};