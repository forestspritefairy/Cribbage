#pragma once
#include <iostream>

using namespace std;

struct Card {
    Card() {
        id = 0;
        suit = 0;
        value = 0;
    }

    Card(int id, int s);

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

    friend ostream& operator<<(ostream& out, const Card c);

    int id; // numerical value cards, respective. ACE=1 JACK=11 QUEEN=12 KING=14, NO jokers
    int suit; // 0-HEARTS 1-DIAMONDS 2-CLUBS 3-SPADES
    int value; //What the card is worth in cribbiage play.
};