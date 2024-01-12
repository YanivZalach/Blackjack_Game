#include <iostream>
#include <vector>
//game functinalty
#include "game.h"


int main() {
    //the start of a new game after the first
    bool antherRoundOfGame = false;
    do{
        //clering the output
        system("cls"); //for mac and linux:  system("clear");

        //creating a shfuld deak of cards
        std::vector<Card> cards = shffelDeakOfCards();

        //crating a dealer and a player
        Diler dealer = Diler();
        Player player = Player();

        //starting the game
        startGame(player,dealer,cards);

        //printing info to the player
        printGameStatus( player, dealer);

        //taking anther card
        if(cardGameTake(player,dealer,cards)){
            //if no resust we will show both
            printEndGame(player,dealer);
        }

        //playing agien?
        antherRoundOfGame=antherRound();

    }while(antherRoundOfGame);

    std::cout<<"Thanks for playing"<<std::endl;

    return 0;
}
