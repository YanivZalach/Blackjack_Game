// Includes
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>  // For the timer
#include <chrono>


#include "classes.h"
#include "game.h"

// Stopping the program for game effect
void timer(){
	// Pause for SLEEP seconds
    std::this_thread::sleep_for(std::chrono::seconds(SLEEP));
}
// Function to clear the console
void clearConsole(){
	// Clear the console - ANSI escape codes are supported by many terminal emulators, making them relatively portable.
	std::cout << "\033[2J\033[H";
}

// Printing the status of the game
void printGameStatus(Player *&player, Dealer *&dealer) {
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
int printEndGame(Player *&player,Dealer *&dealer){

	clearConsole();  // Clearing the console

	std::cout<<"Showing the cards!"<<std::endl;

	if (player) {  // The player cards
		std::cout<<"You got: "<<std::endl;
		player->printCards();
	}
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
		return 0;
	}
	else if(player->maxSum()<=LOSTLIMIT){
		// We got here - the dealer lost, if the player is in limit he won
		std::cout<<"YOU WON THE GAME!!!"<<std::endl;
		return 1;
	}
	// The player is not in the limit - both lost
	std::cout<<"You have both lost..."<<std::endl;
	return -1;

}

// The opening of the game
void startGame(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards){

	std::cout<<"STARTING THE GAME"<<std::endl;
	std::cout<<"2 cardes for each, one open"<<std::endl;

	for (size_t i = 0; i<OPENINGGAMECARDS; i++) {
		std::unique_ptr<Card> hold_player = std::move(cards.back());
		cards.pop_back();
		player->addValueCard(std::move(hold_player));

		std::unique_ptr<Card> hold_dealer = std::move(cards.back());
		cards.pop_back();  // Removing it
		dealer->addValueDealer(std::move(hold_dealer));  // Inserting the last element
	}
	// Timer
	timer();
}

// Taking cards in the game rounds
bool cardGameTake(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards){
	if(gotBlackJack(player,dealer,cards)){  // Got blackjack on the start?
		std::cout << "The dealer's card:";
		dealer->printCards();
		return false;
	}
	// If the player had ended to take cards
	bool player_want_to_drow = true;
	bool dealer_want_to_drow = true;
	int i = 0;// For not passing the CHACKLIMIT
	while ((player_want_to_drow||dealer_want_to_drow)&&(CHACKLIMIT>i))
	{
		// Printing the round
		std::cout<<"Round "<<(i+3)<<std::endl;//i starts from 0, and we have 2 cards

		if(player_want_to_drow ==true){
			player_want_to_drow = playerDrow(player,cards);
		}
		if(dealer_want_to_drow ==true){
			dealer_want_to_drow = dealerDrow(dealer, player,cards);
		}

		if(gotBlackJack(player,dealer,cards)){  // Got blackjack?
												// The dealer info - wont see it else

			std::cout << "The dealer's card:";
			dealer->printCards();
			return false;
		}
		// Timer
		timer();
		printGameStatus( player, dealer);
		i++;// Increasing the round counter
	}
	return true;
}

// Player taking a card
bool playerDrow(Player *&player,std::vector<std::unique_ptr<Card>>& cards){
	// Taking a card?
	char input_take_card;
	std::cout<<"Take anther card?"<<'\n'<<"(y=take/N=stop)"<<std::endl;
	std::cin>>input_take_card;

	// Taking a card
	if(input_take_card=='y'||input_take_card=='Y'){
		player->addValueCard(std::move(cards.back()));
		cards.pop_back();
		std::cout<<"You drow a card!"<<std::endl;
		return true;
	}

	// Else - stop taking cards
	std::cout<<"You stoped drowing!"<<std::endl;
	return false;
}

// Dealer taking a card
bool dealerDrow(Dealer *&dealer,Player *&player,std::vector<std::unique_ptr<Card>>& cards){
	// Taking a card?
	bool dealer_take = dealer->takeCardDealer(player->getShowCardsSum());

	// Taking a card
	if (dealer_take) {
		std::cout<<"The dealer drow a card!"<<std::endl;
		dealer->addValueDealer(std::move(cards.back()));
		cards.pop_back();
		return true;
	} 
	// Else - not taking a card
	std::cout<<"The dealer stoped drowing!"<<std::endl;
	return false;
}

// Did on the first round the player got blackjack?
bool gotBlackJack(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards){
	// Both
	if(dealer->maxSum()==LOSTLIMIT && player->maxSum()==LOSTLIMIT){
		std::cout<<"WHIT!"<<std::endl;
		// Timer
		timer();
		std::cout<<"YOU BOTH GOT A BLACKJACK!!!"<<std::endl;
		return true;
	}
	// Player only
	if(player->maxSum() == LOSTLIMIT){
		std::cout<<"WHIT!"<<std::endl;
		// Timer
		timer();
		std::cout<<"YOU WIN, YOU GOT A BLACKJACK!!!"<<std::endl;
		return true;
	}
	//dealer
	if(dealer->maxSum()==LOSTLIMIT){
		std::cout<<"WHIT!"<<std::endl;
		// Timer
		timer();
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




