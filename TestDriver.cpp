/*--------------------------------------------------------------------
// file name:	TestDriver.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A testing driver that comprehensivly tests calculateHandScore
//--------------------------------------------------------------------*/

#pragma once
#include "Board.h"

using namespace std;

/*------------------------------------------------------------------
// name:		testPrint
// description:	gives a output for each test in the driver
// parameters:	vector of Cards that is the hand you had, vector of ints
//              that is the scores you got, and the Cut for the round.
// returns:		none
// called by:	pairTests, runTests, fifteenTests
//----------------------------------------------------------------*/
void testPrint(vector<Card> hand, vector<int> score, Card cut) {
    cout << "--------------------------------" << endl;
    cout << "|Hand      | " << hand[0] << " |" << endl;

    for (int i = 1; i < hand.size(); i++)
        cout << "|          | " << hand[i] << " |" << endl;

    cout << "|----------|-------------------|" << endl;
    cout << "|Cut       | " << cut << " |" << endl;
    cout << "|----------|-------------------|" << endl;
    cout << "|Scores    | 15's:      " << format(score[0]) << "     |" << endl;
    cout << "|          | Runs:      " << format(score[1]) << "     |" << endl;
    cout << "|          | Of a Kind: " << format(score[2]) << "     |" << endl;
    cout << "|          | Flush:     " << format(score[3]) << "     |" << endl;
    cout << "|          | Nubs:      " << format(score[4]) << "     |" << endl;
    cout << "--------------------------------" << endl << endl;

}

/*------------------------------------------------------------------
// name:		pairTests
// description:	tests the pair catagory for the calculateHandScore method
// parameters:	none
// returns:		none
// called by:	main
//----------------------------------------------------------------*/
void pairTests() {
    ClearScreen();
    cout << "//////////////////////////////////////" << endl;
    cout << "              Pair Tests              " << endl;
    cout << "//////////////////////////////////////" << endl << endl;
    Deck *deck = new Deck();

    //Test Four of a Kind
    vector<Card> hand;
    for (int i = 0; i < 4; i++) {
        hand.push_back(Card(1, i));
    }
    Card cut = Card(2,1);
    vector<int> score = calculateHandScore(hand, cut);
    cout << "Four of a Kind" << endl;
    testPrint(hand, score, cut);

    //Test Full House
    hand.clear();
    for (int i = 0; i < 3; i++) {
        hand.push_back(Card(1, i));
    }
    hand.push_back(Card(2, 0));
    score = calculateHandScore(hand, cut);
    cout << "Three of a kind and Pair" << endl;
    testPrint(hand, score, cut);

    //Two Pairs and Nubs
    hand.clear();
    for (int i = 0; i < 2; i++) {
        hand.push_back(Card(11, i));
        hand.push_back(Card(1, i));
    }
    score = calculateHandScore(hand, cut);
    cout << "Two Pair and Nubs" << endl;
    testPrint(hand, score, cut);

    //Pair and Nubs
    hand.clear();
    for (int i = 0; i < 2; i++) {
        hand.push_back(Card(11, i));
    }
    hand.push_back(Card(1, 1));
    hand.push_back(Card(2, 2));
    cut = Card(3,1);
    score = calculateHandScore(hand, cut);
    cout << "Pair" << endl;
    testPrint(hand, score, cut);

    //3 of a kind
    hand.clear();
    for (int i = 0; i < 3; i++) {
        hand.push_back(Card(11, i));
    }
    hand.push_back(Card(1, 1));

    score = calculateHandScore(hand, cut);
    cout << "3 of a Kind" << endl;
    testPrint(hand, score, cut);

    cin.get();
}

/*------------------------------------------------------------------
// name:		runTests
// description:	tests the runs catagory for the calculateHandScore method
// parameters:	none
// returns:		none
// called by:	main
//----------------------------------------------------------------*/
void runTests() {
    cout << "//////////////////////////////////////" << endl;
    cout << "              Runs Tests              " << endl;
    cout << "//////////////////////////////////////" << endl << endl;
    ClearScreen();
    Deck *deck = new Deck();

    //Run of 3
    vector<Card> hand;
    for (int i = 1; i < 4; i++) {
        hand.push_back(Card(i, 1));
    }
    hand.push_back(Card(10, 1));
    Card cut = Card(9, 1);
    vector<int> score = calculateHandScore(hand, cut);
    cout << "Run of 3" << endl;
    testPrint(hand, score, cut);

    //Run of 4
    hand.clear();
    for (int i = 1; i < 5; i++) {
        hand.push_back(Card(i, 1));
    }
    score = calculateHandScore(hand, cut);
    cout << "Run of 4" << endl;
    testPrint(hand, score, cut);

    //Run of 5
    hand.clear();
    for (int i = 1; i < 5; i++) {
        hand.push_back(Card(i, 2));
    }
    cut = Card(5, 1);
    score = calculateHandScore(hand, cut);
    cout << "Run of 5" << endl;
    testPrint(hand, score, cut);

    //Double run of 3
    hand.clear();
    for (int i = 1; i < 4; i++) {
        hand.push_back(Card(i, 1));
    }
    hand.push_back(Card(1,2));
    score = calculateHandScore(hand, cut);
    cout << "Double run of 3" << endl;
    testPrint(hand, score, cut);

    //Double run of 4
    hand.clear();
    for (int i = 1; i < 5; i++) {
        hand.push_back(Card(i, 1));
    }
    cut = Card(1, 2);
    score = calculateHandScore(hand, cut);
    cout << "Double run of 4" << endl;
    testPrint(hand, score, cut);

    //Triple run of 3
    hand.clear();
    for (int i = 1; i < 4; i++) {
        hand.push_back(Card(i, 1));
    }
    hand.push_back(Card(1, 2));
    cut = Card(1,3);
    score = calculateHandScore(hand, cut);
    cout << "Triple run of 3" << endl;
    testPrint(hand, score, cut);

    //Quadruple run of 3
    hand.clear();
    for (int i = 6; i < 9; i++) {
        hand.push_back(Card(i, 1));
    }
    hand.push_back(Card(8, 2));
    cut = Card(7, 2);
    score = calculateHandScore(hand, cut);
    cout << "Quadruple run of 3" << endl;
    testPrint(hand, score, cut);
    cin.get();
}

/*------------------------------------------------------------------
// name:		fifteenTests
// description:	tests the 15's catagory for the calculateHandScore method
// parameters:	none
// returns:		none
// called by:	main
//----------------------------------------------------------------*/
void fifteenTests() {
    cout << "//////////////////////////////////////" << endl;
    cout << "              15s  Tests              " << endl;
    cout << "//////////////////////////////////////" << endl << endl;
    ClearScreen();
    Deck *deck = new Deck();

    //3 fives and a 10
    vector<Card> hand;
    for (int i = 0; i < 3; i++) {
        hand.push_back(Card(5, i));
    }
    hand.push_back(Card(10, 1));
    Card cut = Card(9, 1);
    vector<int> score = calculateHandScore(hand, cut);
    cout << "3 fives and a 10" << endl;
    testPrint(hand, score, cut);

    //4 fives and a Jack
    hand.clear();
    for (int i = 0; i < 4; i++) {
        hand.push_back(Card(5, i));
    }
    cut = Card(11, 1);
    score = calculateHandScore(hand, cut);
    cout << "4 fives and a Jack" << endl;
    testPrint(hand, score, cut);

    //Ace through 4 and a 10
    hand.clear();
    for (int i = 1; i < 5; i++) {
        hand.push_back(Card(i, 1));
    }
    cut = Card(10,2);
    score = calculateHandScore(hand, cut);
    cout << "Ace through 4 and a 10" << endl;
    testPrint(hand, score, cut);

    cin.get();
}

/*------------------------------------------------------------------
// name:		main
// description:	The main for a simple testing class.
//----------------------------------------------------------------*/
int main() {
    pairTests();
    runTests();
    fifteenTests();
}