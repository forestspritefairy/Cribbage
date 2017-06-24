#include "Deck.h"

class Player {

public:
	virtual int playCard(int turn) = 0;
	int getScore() { return score; }
	virtual vector<Card> getCribCards(bool turn) = 0;
	int calculateHandScore(Card cut);
	void resetHand(vector<Card> newHand);
	void addScore(int newScore) { score += newScore; }
private:
	int score;
	vector<Card> holdingHand;
	vector<Card> playingHand;
};

