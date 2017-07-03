/*--------------------------------------------------------------------
// file name:	Card.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A representation of a Card. Card's contain an id, suit
//              and value. Card has overloads for all the compare operators
//              and an overload for <<.
// variables:	Three ints that define what the card is and its value in
//              Cribbage.
//--------------------------------------------------------------------*/

#pragma once
#include "Card.h"

/*------------------------------------------------------------------
// name:		operator<<
// description:	Gives a standard output form for Card.
// parameters:	the outstream that card is printed to and the Card to
//              be printed.
// returns:		the outstream when we are done with it.
// called by:	Board::printTable, Human::printPegging, Player::printCards
//----------------------------------------------------------------*/
std::ostream & operator<<(std::ostream & out, const Card c) {
    if (c.id == 1) out << "Ace     ";
    else if (c.id == 11) out << "Jack    ";
    else if (c.id == 12) out << "Queen   ";
    else if (c.id == 13) out << "King    ";
    else if (c.id == 10) out << c.id << "      ";
    else out << c.id << "       ";

    if (c.suit == 0) out << "Hearts   ";
    else if (c.suit == 1) out << "Diamonds ";
    else if (c.suit == 2) out << "Clubs    ";
    else out << "Spades   ";

    return out;
}
