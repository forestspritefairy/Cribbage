#pragma once
#include "Deck.h"

Deck::Deck() {
    for (int id = 1; id <= MAX_DECK_VALUE; id++) {
        for (int suit = 0; suit < MAX_SUIT_VALUE; suit++) {
            Card c(id, suit);
            cards.push_back(c);
        }
    }
}

Card Deck::draw() {
    int random = rand() % (cards.size() - 1);
    Card draw = cards.at(random);
    cards.erase(cards.begin() + random);
    return draw;
}

Card Deck::cut() {
    return cards.at(rand() % (cards.size() - 1));
}

void Deck::resetDeck() {
    cards.clear();
    for (int value = 1; value <= MAX_DECK_VALUE; value++) {
        for (int suit = 0; suit < MAX_SUIT_VALUE; suit++) {
            Card c(value, suit);
            cards.push_back(c);
        }
    }
}
