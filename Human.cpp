#pragma once
#include <iostream>
#include "Human.h"
#include "Board.h"

using namespace std;

Card Human::playCard(vector<Card> pastCards, int sum) {
    int input;
    if (playingHand.size() == 0) {
        return Card();
    } 
    if (!canPlay(sum)) {
        return Card();
    }
    while(true) {
        printPegging(pastCards, sum);

        cin >> input;
        cout << endl;
        if (input >= 0 && input < playingHand.size() && playingHand[input].value + sum < 31) {
            break;
        }
    }
    Card choice = playingHand[input];
    playingHand.erase(playingHand.begin() + input);
    return choice;
}

void Human::printPegging(vector<Card> pastCards, int sum) {
    ClearScreen();

    cout << "Pegging" << endl;
    cout << "------------------------" << endl;
    for (int i = pastCards.size() - 1; i >= 0; i--) {
        cout << "| " << pastCards[i] << "    |" << endl;
    }
    cout << "|----------------------|" << endl;
    cout << "| Sum  " << wordCheck(sum) << "              |" << endl;
    cout << "------------------------" << endl;
    cout << endl;

    printCards(playingHand);

    cout << "Enter card index to play: ";
}

vector<Card> Human::getCribCards(bool turn) {
    int in1;
    int in2;
    while(true) {
        if(turn){
            cout << "It is currently your crib." << endl;
        }
        else {
            cout << "It is currently not your crib." << endl;
        }
        cout << endl;
        printCards(holdingHand);
        cout << "Enter two numbers representing the indexes of" << endl;
        cout << "the cards you want to place in the crib." << endl;

        cin >> in1;
        cin >> in2;

        if (in1 >= 0 && in1 < holdingHand.size() && in2 >= 0 && in2 < holdingHand.size() && in1 != in2) {
            break;
        }
    }
    vector<Card> cribIn;
    cribIn.push_back(holdingHand[in1]);
    cribIn.push_back(holdingHand[in2]);

    holdingHand.erase(holdingHand.begin() + in1);
    if (in1 < in2) {
        in2--;
    }
    holdingHand.erase(holdingHand.begin() + in2);

    playingHand = holdingHand;
    return cribIn;
}

void Human::setName(char * name, int length) {
    if (length > 10){
        this->name = new char[10];
        nameLength = 10;
        length = 10;
        for (int i = 0; i < length; i++) {
            this->name[i] = name[i];
        }
    }
    else {
        this->name = name;
        nameLength = length;
    }
}

char * Human::getName() {
    return name;
}

int Human::getNameLength()
{
    return nameLength;
}

void Human::print() {
    char* name = this->getName();
    int nameLength = this->getNameLength();
    for (int i = 0; i < nameLength; i++) {
        cout << name[i];
    }

    for (int i = nameLength; i <= 10; i++) {
        cout << " ";
    }
    
    cout << ((score > 99) ? to_string(score) : (score > 9)
        ? to_string(score) + " " : to_string(score) + "  ");
}

bool Human::canPlay(int sum) {
    for (int i = 0; i < playingHand.size(); i++) {
        if (playingHand[i].value + sum <= 31) {
            return true;
        }
    }
    return false;
}

