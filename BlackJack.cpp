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

        void showHand() const {
            for(const Card& card : hand){
                cout << card.value << " of " << card.suit << endl;
            }
        }

        int findTotal(){
            int total;
            for(const Card& card : hand){
                total += card.value;
            }

            return total;
        }
};

class Game{
    private:
        Deck deck;
        Player player;
        Player dealer;

        int playerTotal;
        int dealerTotal;
    public:
        void begin(){
            deck.shuffle();

            player.draw(deck);
            dealer.draw(deck);
            player.draw(deck);
        }

        void hit(Player player){
            player.draw(deck);
        }

        void stand(){
            while(dealer.findTotal() <= 17){
                hit(dealer);
            }

            playerTotal = player.findTotal();
            dealerTotal = dealer.findTotal();

            if(dealerTotal > 21){
                cout << "Dealer busts! You win!" << endl;
            }else{
                if(dealerTotal = 21){
                    cout << "Dealer has blackjack! You Lose!" << endl;
                }else{
                    if(dealerTotal < playerTotal){
                            cout << "You win!" << endl;
                    }else{
                        if(dealerTotal = playerTotal){
                            cout << "It's a draw!" << endl;
                        }
                    }
                }
            }
        }
};

int main(){
    Game Game;
    Game.begin();

    cout << "Your hand:" << endl;
    player.showHand();

    cout << "Dealer's hand:" << endl;
    dealer.showHand();

    cout << "What would you like to do?" << endl;
    cout << "(1) Hit" << endl;
    cout << "(1) Stand" << endl;


    return 0;
}