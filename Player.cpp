#pragma once
#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

void Player::resetHand(vector<Card> *newHand) {
    holdingHand = *newHand;
    playingHand = *newHand;
}

vector<int> calculateHandScore(vector<Card> hand, Card cut) {
    vector<int> scores;
    vector<Card> fullHand = hand;
    fullHand.push_back(cut);

    scores.push_back(score15(fullHand));
    scores.push_back(scoreRuns(fullHand));
    scores.push_back(scoreOfAKind(fullHand));
    scores.push_back(scoreNubs(fullHand, cut));

    return scores;
}

int score15(const vector<Card> hand) {
    return find15(hand,0,0,0);
}

int find15(const vector<Card> numbers, int index, int sum, int score) {
    if (sum > 15) return score;
    if (sum == 15) return score + 2;
    if (index == numbers.size()) return score;
    
    //Left half is the inclusive. Right half is the exclusive.
    return find15(numbers, index + 1, sum + numbers[index].value, score) + find15(numbers, index + 1, sum, score);
}

void printCards(const vector<Card> v) {
    cout << "Your Cards" << endl;
    cout << "---------------------------" << endl;
    cout << "|Index | Card             |" << endl;
    cout << "|------|------------------|" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "| " << i << "    | " << v[i] << "|" << endl;
    }
    cout << "---------------------------" << endl;
}

int scoreRuns(vector<Card> hand) {
    sort(hand);

    int multipiler = 1;
    int runLength = 1;
    int maxRunLength = 0;
    for (int i = 1; i < hand.size(); i++) {
        if (hand[i - 1].id == hand[i].id)
            multipiler++;
        else if (hand[i - 1].id + 1 == hand[i].id) 
            runLength++;
        else {
            if (runLength > 2) break;
            else {
                multipiler = 0;
                runLength = 1;
            }
        }
    }
    if (multipiler == 4 && runLength > 2 && scoreOfAKind(hand) == 4) {
        //2 pair run
        multipiler++;
    }
    return (runLength > 2) ? (runLength * multipiler) : 0;
}

int scoreOfAKind(vector<Card> hand) {
    int s = 0;

    for (int i = 0; i < hand.size(); i++) {
        int counter = 0;
        for (int j = i + 1; j < hand.size(); j++) {
            if (hand[i].id == hand[j].id) {
                counter++;
            }
        }
        //Pair
        if (counter == 1) {
            s += 2;
        }
        //3-of a kind
        else if (counter == 2) {
            s += 4;
        }
        //4 of a kind
        else if(counter == 3) {
            return 12;
        }
        counter = 0;
    }
    return s;
}

int scoreNubs(const vector<Card> hand, Card cut) {
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].id == 11 && hand[i].suit == cut.suit) {
            return 1;
        }
    }
    return 0;
}

void sort(vector<Card>& v) {
    bool swapped = true;
    int n = v.size();
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (v[i - 1] > v[i]) {
                Card temp = v.at(i-1);
                v[i-1] = v[i];
                v[i] = temp;
                swapped = true;
            }
        }
        n = n-1;
    }
}
