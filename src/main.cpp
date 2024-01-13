// Includes
#include <iostream>
#include <memory>
#include <vector>

#include "classes.h"
#include "game.h"


int main() {

    do{
		clearConsole(); // Clearing the console

        // Creating a shuffled deck of cards
        std::vector<std::unique_ptr<Card>> cards = shffelDeakOfCards();

        // Crating a dealer and a player as a shared pointer
        std::shared_ptr<Dealer> dealer = std::make_shared<Dealer>();
        std::shared_ptr<Player> player = std::make_shared<Player>();

        startGame(player,dealer,cards);  // Starting the game

        printGameStatus( player, dealer);  // Printing the game status

        // Taking anther card
        if(cardGameTake(player,dealer,cards)){
            printEndGame(player,dealer);  // If both not taking card - end game
        }

    }while(antherRound());  // Playing anther round?

    std::cout<<"Thanks for playing"<<std::endl;

    return 0;
}
