#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Card{
    public:
        string value;
        string suit;

        Card(string v, string s) : value(v), suit(s) {}
};

class Deck{
    private:
        vector<Card> cards;
    public:
        Deck(){
            string values[] = {"Ace", "Two", "Three", "Four", "Five",
                               "Six", "Seven", "Eight", "Nine", "Ten",
                               "Jack", "Queen", "King"};
            string suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
            for(const string& suit : suits){
                for(const string& value : values){
                    cards.push_back(Card(value, suit));
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
            int total = 0;
            int aceCount = 0;

            for(const Card& card : hand){
                if(card.value == "Two"){
                    total += 2;
                }else if(card.value == "Three"){
                    total += 3;
                }else if(card.value == "Four"){
                    total += 4;
                }else if(card.value == "Five"){
                    total += 5;
                }else if(card.value == "Six"){
                    total += 6;
                }else if(card.value == "Seven"){
                    total += 7;
                }else if(card.value == "Eight"){
                    total += 8;
                }else if(card.value == "Nine"){
                    total += 9;
                }else if(card.value == "Ten" || card.value == "Jack" ||
                         card.value == "Queen" || card.value == "King"){
                    total += 10;
                }else if(card.value == "Ace"){
                    aceCount += 1;
                }
            }
            if(aceCount > 0){
                for(int i = 0; i < aceCount; i++){
                    if((total + (aceCount - i)) >= 21){
                        return (total + (aceCount - 1));
                    }else{
                        total += 11;
                    }
                }
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
        void play(){
            deck.shuffle();

            dealer.draw(deck);
            player.draw(deck);
            player.draw(deck);
            player.draw(deck);
            player.draw(deck);
            player.draw(deck);

            cout << "Your hand:" << endl;
            player.showHand();
            cout << "Total: " << player.findTotal() << endl;

            cout << "Dealer's hand:" << endl;
            dealer.showHand();
            cout << "Total: " << dealer.findTotal() << endl;

            cout << "What would you like to do?" << endl;
            cout << "(1) Hit" << endl;
            cout << "(1) Stand" << endl;
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
            }else if(dealerTotal = 21){
                    cout << "Dealer has blackjack! You Lose!" << endl;
                }else if(dealerTotal < playerTotal){
                            cout << "You win!" << endl;
                    }else if(dealerTotal = playerTotal){
                            cout << "It's a draw!" << endl;
                        }
                    }
};

int main(){
    Game Game;
    Game.play();

    return 0;
}