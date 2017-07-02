/*--------------------------------------------------------------------
// file name:	Player.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		06/29/2017
// description: A representation of a player in a Cribbage game. Player
//              is a pure abstract class and only serves as a mold for
//              board to call upon.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

/*------------------------------------------------------------------
// name:		calculateHandScore
// description:	given a hand and a cut calculates the number of points
//              earned. returns a vector that contains where they recived
//              points in each catagory.
// parameters:	vector of cards thats the hand, and Card that represents the
//              cut.
// called by:	Board::play
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		score15
// description:	given a hand calculates the number of points earned from 15's.
// parameters:	vector of Cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int score15(const vector<Card> hand) {
    return find15(hand,0,0,0);
}

/*------------------------------------------------------------------
// name:		find15
// description:	helper method for score15
// parameters:	A vector of Cards, the current index in the array we are
//              at. The current sum that has been scored, and the amount
//              of points they have recived.
// called by:	score15
//----------------------------------------------------------------*/
int find15(const vector<Card> numbers, int index, int sum, int score) {
    if (sum > 15) return score;
    if (sum == 15) return score + 2;
    if (index == numbers.size()) return score;
    
    //Left half is the inclusive. Right half is the exclusive.
    return find15(numbers, index + 1, sum + numbers[index].value, score) + find15(numbers, index + 1, sum, score);
}

/*------------------------------------------------------------------
// name:		scoreRuns
// description:	given a hand of Cards calculates the number of points earned
//              from runs.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
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
                multipiler = 1;
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

/*------------------------------------------------------------------
// name:		scoreOfAKind
// description:	given a hand of Cards calculates the number of points earned
//              from pairs, 3 of a kind, and 4 of a kind.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore, scoreRuns
//----------------------------------------------------------------*/
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

/*------------------------------------------------------------------
// name:		scoreNubs
// description:	given a hand of Cards and a cut calculates the number of
//              points earned from runs.
// parameters:	vector of cards and cut to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreNubs(const vector<Card> hand, Card cut) {
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].id == 11 && hand[i].suit == cut.suit) {
            return 1;
        }
    }
    return 0;
}

/*------------------------------------------------------------------
// name:		sort
// description:	given an address to a vector of Cards. Sorts the vector
// parameters:	location of vector to be sorted.
// called by:	scoreRuns
//----------------------------------------------------------------*/
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
