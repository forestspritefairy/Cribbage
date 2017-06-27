#include <iostream>
#include "Human.h"

using namespace std;

Card Human::playCard(int sum) {
    int input;
    if (playingHand.size() == 0) {
        return Card();
    } 
    if (!canPlay(sum)) {
        return Card();
    }
    while(true) {
        cout << "The Current Sum is " << sum << endl;
        cout << "Your Cards are" << endl;
        printCards(playingHand);
        cout << "Enter a number representing the index of the card you want.";
    
        cin >> input;
        if (input >= 0 && input < playingHand.size() && playingHand[input].value + sum < 31) {
            break;
        }
    }
    Card choice = playingHand[input];
    playingHand.erase(playingHand.begin() + input);
    return choice;
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
        cout << "Your cards are" << endl;
        printCards(holdingHand);
        cout << "Enter two numbers representing the indexes of" << endl;
        cout << "the cards you want to remove." << endl;

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

bool Human::canPlay(int sum) {
    for (int i = 0; i < playingHand.size(); i++) {
        if (playingHand[i].value + sum <= 31) {
            return true;
        }
    }
    return false;
}
