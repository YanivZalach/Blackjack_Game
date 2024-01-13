// Includes
#include <iostream>
#include <vector>
#include <memory>

#include "classes.h"
#include "game.h"

// Function to clear the console
void clearConsole(){
	// Clear the console - ANSI escape codes are supported by many terminal emulators, making them relatively portable.
    std::cout << "\033[2J\033[H";
}

// Printing the status of the game
void printGameStatus(std::shared_ptr<Player>& player, std::shared_ptr<Dealer>& dealer) {
	clearConsole();  // Clearing the console

	if (player) {
		std::cout << "Your cards: ";
		player->printCards();

		std::cout << "Your open card:";
		player->printShowCard();
	}

	if (dealer) {
		std::cout << "The dealer's open card:";
		dealer->printShowCard();
	}
}


// Printing the status in the end of the game
void printEndGame(std::shared_ptr<Player>& player,std::shared_ptr<Dealer>& dealer){

	clearConsole();  // Clearing the console

	std::cout<<"Showing the cards!"<<std::endl;

	if (dealer) {  // The dealer cards
		std::cout<<"The dealer got: "<<std::endl;
		dealer->printCards();
	}

	if(dealer->maxSum()<=LOSTLIMIT &&(dealer->maxSum()>=player->maxSum()||player->maxSum()>LOSTLIMIT)){
		// The dealer is wining the game(dealer>=player or player>LOWLIMIT)
		std::cout<<"YOU LOST THE GAME..."<<std::endl;

		if(dealer->maxSum()==player->maxSum()){
			// the dealer is wining in a tie
			std::cout<<"THE HOUSE WINS IN A TIE"<<std::endl;
		}
	}
	else if(player->maxSum()<=LOSTLIMIT){
		// We got here - the dealer lost, if the player is in limit he won
		std::cout<<"YOU WON THE GAME!!!"<<std::endl;
	}
	else{
		// The player is not in the limit - both lost
		std::cout<<"You have both lost..."<<std::endl;
	}
}

//the opening of the game
void startGame(std::shared_ptr<Player>& player,std::shared_ptr<Dealer>& dealer,std::vector<std::unique_ptr<Card>>& cards){

	std::cout<<"STARTING THE GAME"<<std::endl;
	std::cout<<"2 cardes for each, one open"<<std::endl;
	for (size_t i = 0; i<OPENINGGAMECARDS; i++) {
		dealer->addValueDealer(cards.back());  // Inserting the last element
		cards.pop_back();  // Removing it
		player->addValueCard(cards.back());
		cards.pop_back();
	}
	//addtimer
}

// Taking cards in the game rounds
bool cardGameTake(std::shared_ptr<Player>& player,std::shared_ptr<Dealer>& dealer,std::vector<std::unique_ptr<Card>>& cards){
    // If the player had ended to take cards
    bool player_want_to_drow = true;
    bool dealer_want_to_drow = true;
    int i =0;//making shore we dont pass chackLimit
    while ((player_want_to_drow||dealer_want_to_drow)&&(CHACKLIMIT>i))
    {
        if(gotBlackJack(player,dealer,cards)){
            return false;
        }
        //printing the round
        std::cout<<"Round "<<(i+3)<<std::endl;//i starts from 0, and we have 2 cards
        if(player_want_to_drow ==true){
            player_want_to_drow = playerDrow(player,cards);
        }
        if(dealer_want_to_drow ==true){
            dealer_want_to_drow = dealerDrow(dealer, player,cards);
        }
        //time to read - addtimer
        printGameStatus( player, dealer);
        i++;//incresing i
    }
    return true;
}

// Player taking a card
bool playerDrow(std::shared_ptr<Player>& player,std::vector<std::unique_ptr<Card>>& cards){
    // Taking a card?
    char input_take_card;
    std::cout<<"Take anther card?"<<'\n'<<"(y=take/N=stop)"<<std::endl;
    std::cin>>input_take_card;

	// Taking a card
    if(input_take_card=='y'||input_take_card=='Y'){
        player->addValueCard(cards.back());
        cards.pop_back();
        std::cout<<"You drow a card!"<<std::endl;
        return true;
    }

    // Else - stop taking cards
    std::cout<<"You stoped drowing!"<<std::endl;
    return false;
}

// Dealer taking a card
bool dealerDrow(std::shared_ptr<Dealer>& dealer,std::shared_ptr<Player>& player,std::vector<std::unique_ptr<Card>>& cards){
    // Taking a card?
    bool dealer_take = dealer->takeCardDealer(player->getShowCardsSum());

    // Taking a card
    if (dealer_take) {
        std::cout<<"The dealer drow a card!"<<std::endl;
        dealer->addValueDealer(cards.back());
        cards.pop_back();
        return true;
    } 
    // Else - not taking a card
    std::cout<<"The dealer stoped drowing!"<<std::endl;
    return false;
}

// Did on the first round the player got blackjack?
bool gotBlackJack(std::shared_ptr<Player>& player,std::shared_ptr<Dealer>& dealer,std::vector<std::unique_ptr<Card>>& cards){
    // Both
    if(dealer->maxSum()==LOSTLIMIT && player->maxSum()==LOSTLIMIT){
        std::cout<<"WHIT!"<<std::endl;
		// Addtimer
        std::cout<<"YOU BOTH GOT A BLACKJACK!!!"<<std::endl;
        return true;
    }
    // Player only
    if(player->maxSum() == LOSTLIMIT){
        std::cout<<"WHIT!"<<std::endl;
		// addtimer
        std::cout<<"YOU WIN, YOU GOT A BLACKJACK!!!"<<std::endl;
        return true;
    }
    //dealer
    if(dealer->maxSum()==LOSTLIMIT){
        std::cout<<"WHIT!"<<std::endl;
		// Addtimer
        std::cout<<"YOU LOST, THE DEALER GOT A BLACKJACK!!!"<<std::endl;
         return true;
    }
    return false;
}


//at the end of the game 
bool antherRound(){
    // A new game?
    std::cout<<"Anther round(y/N)?"<<std::endl;
    char run;
    std::cin >> run;
	// A new game
    if(run == 'y'|| run =='Y'){
        return true;
    }
	// Exit the program
    return false;
}

int main(){
	return 0;
}
