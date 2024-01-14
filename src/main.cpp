// Includes
#include <iostream>
#include <memory>
#include <vector>

#include "classes.h"
#include "game.h"


int main() {

	// The game score
	int player_won = 0;
	int dealer_won = 0;

	do{
		clearConsole(); // Clearing the console

		// Creating a shuffled deck of cards
		std::vector<std::unique_ptr<Card>> cards = shffelDeakOfCards();

		// Crating a dealer and a player as a shared pointer
		Dealer *dealer = new Dealer();
		Player *player = new Player();

		startGame(player,dealer,cards);  // Starting the game

		printGameStatus( player, dealer);  // Printing the game status

		// Taking anther card
		if(cardGameTake(player,dealer,cards)){
			switch (printEndGame(player,dealer)){ // If both not taking card - end game 
				case 1:  // Player won this round
					player_won++;
					break;
				case 0:  // Dealer won this round
					dealer_won++;
					break;
			} 
		} else {  // In the case of a blackjack
			if (player->maxSum() == LOSTLIMIT) {
				if (dealer->maxSum() == LOSTLIMIT) {
					dealer_won++;  // Both got a blackjack
				}
					player_won++;
			} else {
					dealer_won++;
			}
		}

		// Realising the memory
		delete dealer;
		delete player;

		// Printing the currant resoles
		std::cout<<"\n----- Score -----"<<std::endl;
		std::cout<<"You : Dealer"<<std::endl;
		std::cout<<player_won<<" : "<<dealer_won<<"\n"<<std::endl;

	}while(antherRound());  // Playing anther round?


	std::cout<<"Thanks for playing"<<std::endl;

	return 0;
}
