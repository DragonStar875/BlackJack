#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Card{
    public:
        int value;
        string suit;

        Card(int v, string s) : value(v), suit(s) {}
};

class Deck{
    private:
        vector<Card> cards;
    public:
        Deck(){
            string suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
            for(const string& suit : suits){
                for(int i = 0; i < 13; ++i){
                    cards.push_back(Card(i, suit));
                }
            }
        }

        void shuffle(){
            srand(time(0));
            random_shuffle(cards.begin(), cards.end());
        }

        Card drawCard(){
            Card drawnCard = cards.back();
            cards.pop_back();
            return drawnCard;
        }
};

class Player{
    public:
        vector<Card> hand;

        void draw(Deck &deck){
            hand.push_back(deck.drawCard());
        }
};