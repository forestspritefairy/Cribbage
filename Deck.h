#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

const int AMOUNT_OF_CARDS = 52;
const int MAX_DECK_VALUE = 13;
const int MAX_SUIT_VALUE = 4;

class Deck {

public:
	Deck();
	Card draw();
	Card cut();
	void resetDeck();

private:
	vector<Card> cards;
};	


struct Card {
	Card(int val, int s) {
		value = val;
		suit = s;
	}
	int value; // numerical value cards, respective. ACE=1 JACK=11 QUEEN=12 KING=14, NO jokers
	int suit; // 0-HEARTS 1-DIAMONDS 2-CLUBS 3-SPADES
};