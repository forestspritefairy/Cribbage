#pragma once
#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

int Player::calculateHandScore(Card cut) {
    vector<Card> fullHand = holdingHand;
    fullHand.push_back(cut);
    
    printCards(fullHand);
    cout << endl;
    cout << "15's:      " << score15(cut) << endl;
    cout << "Runs:      " << scoreRuns(cut) << endl;
    cout << "Of a Kind: " << scoreOfAKind(cut) << endl;
    cout << "Nubs:      " << scoreNubs(cut) << endl;
    cout << "Total:     " << score15(cut) + scoreRuns(cut) + scoreOfAKind(cut) + scoreNubs(cut) << endl;
    cout << endl;
    return score15(cut) + scoreRuns(cut) + scoreOfAKind(cut) + scoreNubs(cut);
}

void Player::resetHand(vector<Card> *newHand) {
    holdingHand = *newHand;
    playingHand = *newHand;
}

int Player::score15(Card cut) {
    vector<Card> fullHand = holdingHand;
    fullHand.push_back(cut);
    return find15(fullHand,0,0,0);
}


 int Player::find15(vector<Card> numbers, int index, int sum, int score) {
    if (sum > 15) {
         return score;
    }
    if (sum == 15) {
        return score + 2;
    }
    if (index == numbers.size()) {
        
        return score;
    }
    //Left half is the inclusive. Right half is the exclusive.
    return find15(numbers, index + 1, sum + numbers[index].value, score) + find15(numbers, index + 1, sum, score);
}

 void printCards(vector<Card> v) {
     for (int i = 0; i < v.size(); i++) {
         cout << v.at(i).id << " ";
     }
     cout << endl;
     for (int i = 0; i < v.size(); i++) {
         cout << v.at(i).value << " ";
     }
     cout << endl;
     for (int i = 0; i < v.size(); i++) {
         cout << v.at(i).suit << " ";
     }
     cout << endl;
     for (int i = 0; i < v.size(); i++) {
         cout << i << " ";
     }
     cout << endl;

}

int Player::scoreRuns(Card cut) {
    vector<Card> fullHand = holdingHand;
    fullHand.push_back(cut);

    sort(fullHand);

    int multipiler = 1;
    int runLength = 1;
    int maxRunLength = 0;
    for (int i = 1; i < fullHand.size(); i++) {
        if (fullHand.at(i - 1).id == fullHand.at(i).id)
            multipiler++;
        else if (fullHand.at(i - 1).id + 1 == fullHand.at(i).id) 
            runLength++;
        else {
            if (runLength > 2) break;
            else {
                multipiler = 0;
                runLength = 1;
            }
        }
    }
    if (multipiler == 4 && runLength > 2 && scoreOfAKind(cut) == 4) {
        //2 pair run
        multipiler++;
    }
    return (runLength > 2) ? (runLength * multipiler) : 0;
}

int Player::scoreOfAKind(Card cut) {
    int s = 0;
    vector<Card> fullHand = holdingHand;
    fullHand.push_back(cut);

    for (int i = 0; i < fullHand.size(); i++) {
        int counter = 0;
        for (int j = i + 1; j < fullHand.size(); j++) {
            if (fullHand.at(i).id == fullHand.at(j).id) {
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

int Player::scoreNubs(Card cut) {
    for (int i = 0; i < holdingHand.size(); i++) {
        if (holdingHand.at(i).id == 11 && holdingHand.at(i).suit == cut.suit) {
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
