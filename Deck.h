#pragma once
#include <vector>
#include <iostream>

using namespace std;

const int AMOUNT_OF_CARDS = 52;
const int MAX_DECK_VALUE = 13;
const int MAX_SUIT_VALUE = 4;

struct Card {
    Card() {
        id = 0;
        suit = 0;
        value = 0;
    }

    Card(int id, int s) {
        this->id = id;
        suit = s;
        value = (id < 10) ? id : 10;
    }

    bool operator==(const Card & other) {
        return other.id == this->id && other.suit == this->suit;
    }

    bool operator!=(const Card & other) {
        return !(*this == other);
    }

    bool operator>(const Card & other) {
        return (this->id > other.id) || (this->id == other.id && this->suit > other.suit);
    }

    bool operator>=(const Card & other) {
        return !(*this < other);
    }

    bool operator<(const Card & other) {
        return (this->id < other.id) || (this->id == other.id && this->suit < other.suit);
    }

    bool operator<=(const Card & other) {
        return !(*this > other);
    }

    friend ostream& operator<<(ostream& out, const Card c) {
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
    
    int id; // numerical value cards, respective. ACE=1 JACK=11 QUEEN=12 KING=14, NO jokers
    int suit; // 0-HEARTS 1-DIAMONDS 2-CLUBS 3-SPADES
    int value; //What the card is worth in cribbiage play.
};

class Deck {

public:
    Deck();
    Card draw();
    Card cut();
    void resetDeck();

private:
    vector<Card> cards;
};
