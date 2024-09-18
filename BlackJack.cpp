#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <random>
#include <unordered_map>
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
        string values[] = { "Ace", "Two", "Three", "Four", "Five",
            "Six", "Seven", "Eight", "Nine", "Ten",
            "Jack", "Queen", "King" };
        string suits[] = { "Hearts", "Diamonds", "Spades", "Clubs" };
        for(const string& suit : suits){
            for(const string& value : values){
                cards.push_back(Card(value, suit));
            }
        }
    }

    void shuffle(){
        random_device rd;
        mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
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

    void draw(Deck& deck){
        hand.push_back(deck.drawCard());
    }

    int findTotal(){
        int total = 0;
        int aceCount = 0;
        
        unordered_map<string, int> cardValues = {
            {"Two", 2}, {"Three", 3}, {"Four", 4}, {"Five", 5},
            {"Six", 6}, {"Seven", 7}, {"Eight", 8}, {"Nine", 9},
            {"Ten", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10}
        };

        for(const Card& card : hand){
            if(card.value == "Ace"){
                aceCount++;
            }else{
                total += cardValues[card.value];
            }
        }

        for(int i = 0; i < aceCount; i++){
            if((total + 11) > 21){
                return (total + (aceCount - i));
            }else{
                total += 11;
            }
        }
        return total;
    }

    void showHand() const {
        for(const Card& card : hand){
            cout << setw(5) << card.value << " of " << card.suit << endl;
        }
    }
};

class Game{
private:
    Deck deck;
    Player player;
    Player dealer;

    int playerTotal;
    int dealerTotal;
    int playerChoice = 0;
    int done;

    enum state{
        STAND,
        BUST,
        BLACKJACK
    };
    
    state handOne;
    state handTwo;
public:
    void showTable(Player player){
        playerTotal = player.findTotal();
        dealerTotal = dealer.findTotal();

        cout << "Your hand:" << endl;
        player.showHand();
        cout << "Total: " << playerTotal << endl << endl;

        cout << "Dealer's hand:" << endl;
        dealer.showHand();
        cout << "Total: " << dealerTotal << endl << endl;
    }

    bool validateInput(int& input){
        cin >> input;
        if(cin.fail() || (input != 1 && input != 2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }else{
            return true;
        }
    }

    void dealerTurn(){
        cout << endl;
        while(dealerTotal <= 17 && dealerTotal < playerTotal){
            dealer.draw(deck);
            cout << "Dealer drew a " << dealer.hand.back().value <<
                " of " << dealer.hand.back().suit << endl;
            dealerTotal = dealer.findTotal();
            cout << "Dealer's total: " << dealerTotal << endl;
        }
    }

    void playerTurn(){
        do{
            cout << "What would you like to do?" << endl;
            cout << "(1) Hit" << endl;
            cout << "(2) Stand" << endl;
            while(!validateInput(playerChoice)){
                cout << "Invalid choice. Please select 1 or 2." << endl;
            }

            if(playerChoice == 1){
                player.draw(deck);
                playerTotal = player.findTotal();
                showTable(player);
            }
        }while(playerChoice == 1 && playerTotal < 21);

        if(playerTotal == 21){
            cout << "Your hand:" << endl;
            player.showHand();
            cout << "Total: " << playerTotal << endl;
            cout << "You got blackJack! You win!" << endl;
        }else if(playerTotal > 21){
            cout << "Your hand:" << endl;
            player.showHand();
            cout << "Total: " << playerTotal << endl;
            cout << "You bust! You lose!" << endl;
        }else{
            dealerTurn();
            if(dealerTotal > 21){
            cout << "Dealer busts! You win!" << endl;
            }else if(dealerTotal == 21){
                cout << "Dealer has blackjack! You Lose!" << endl;
            }else if(dealerTotal < playerTotal){
                cout << "Your total: " << playerTotal << endl;
                cout << "You win!" << endl;
            }else if(dealerTotal == playerTotal){
                cout << "Your total: " << playerTotal << endl;
                cout << "It's a draw!" << endl;
            }else{
                cout << "Your total: " << playerTotal << endl;
                cout << "Dealer's total: " << dealerTotal << endl;
                cout << "Dealer wins!" << endl;
            }
        }
    }

    state playerTurn(Player &player){
        do{
            cout << "What would you like to do?" << endl;
            cout << "(1) Hit" << endl;
            cout << "(2) Stand" << endl;
            while(true){
                cin >> playerChoice;
                if(cin.fail() || (playerChoice != 1 && playerChoice != 2 && playerChoice != 3)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please select 1, 2, or 3." << endl;
                }else{
                    break;
                }
            }

            if(playerChoice == 1){
                player.draw(deck);
                playerTotal = player.findTotal();
                showTable(player);
            }
        }while(playerChoice == 1 && playerTotal < 21);

        if(playerTotal == 21){
            cout << "This hand:" << endl;
            player.showHand();
            cout << "Total: " << playerTotal << endl;
            cout << "This hand got 21!" << endl;
            return BLACKJACK;
        }else if(playerTotal > 21){
            cout << "This hand:" << endl;
            player.showHand();
            cout << "Total: " << playerTotal << endl;
            cout << "This hand bust!" << endl;
            return BUST;
        }else{
            return STAND;
        }
    }

    void play(){
        deck.shuffle();

        dealer.draw(deck);
        // player.draw(deck);
        // player.draw(deck);

        Card cardOne("Five", "Spade");
        Card cardTwo("Five", "Heart");

        player.hand.push_back(cardOne);
        player.hand.push_back(cardTwo);

        showTable(player);

        if(playerTotal == 21){
            cout << "You got blackJack! You win!" << endl;
        }else if(player.hand[0].value == player.hand[1].value){
            cout << "What would you like to do?" << endl;
            cout << "(1) Hit" << endl;
            cout << "(2) Stand" << endl;
            cout << "(3) Split" << endl;
            while(true){
                cin >> playerChoice;
                if(cin.fail() || (playerChoice != 1 && playerChoice != 2 && playerChoice != 3)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please select 1, 2, or 3." << endl;
                }else{
                    break;
                }
            }
            if(playerChoice == 3){
                Player playerTwo;
                playerTwo.hand.push_back(player.hand[1]);
                player.hand.pop_back();

                player.draw(deck);
                playerTwo.draw(deck);

                showTable(player);

                handOne = playerTurn(player);

                showTable(playerTwo);

                handTwo = playerTurn(playerTwo);

                if(!(handOne == true && handTwo == true)){
                    dealerTurn();
                    if(dealerTotal > 21){
                        cout << "Dealer busts! ";
                        if(handOne == false){
                            cout << "Hand one wins!";
                        }else if(handTwo == false){
                            cout << "Hand two wins!";
                        }else{
                            cout << "Both hands one win!";
                        }
                    }
                    if(handOne == false){
                        if(dealerTotal == 21){
                            cout << "Dealer has blackjack! You Lose!" << endl;
                        }else if(dealerTotal < playerTotal){
                            cout << "Your total: " << playerTotal << endl;
                            cout << "You win!" << endl;
                        }else if(dealerTotal == playerTotal){
                            cout << "Your total: " << playerTotal << endl;
                            cout << "It's a draw!" << endl;
                        }else{
                            cout << "Your total: " << playerTotal << endl;
                            cout << "Dealer's total: " << dealerTotal << endl;
                            cout << "Dealer wins!" << endl;
                        }
                    }
                }

                
            }
        }else{
            playerTurn();
        }
    }
};

int main(){
    int play = 1;
    while(play == 1){
        cout << endl;
        Game Game;
        Game.play();
        cout << endl;
        cout << "Would you like to play again?" << endl
            << "(1) Yes" << endl
            << "(2) No" << endl;
        while(!Game.validateInput(play)){
            cout << "Invalid choice. Please select 1 or 2." << endl;
        }
    }
    return 0;
}