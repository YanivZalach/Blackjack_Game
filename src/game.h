#pragma once

#include <iostream>
#include <vector>
//game functinalty
#include "classes.h"
#include "data.h"

const int chackLimit = 10;//the max card a player is alowed to take in a game
//sleep time
const int longSleep = 3500;
const int shortSleep = 2000;

//functions
void printGameStatus(Player& player,Diler& dealer);//printing the status of the game
void printEndGame(Player& player,Diler& dealer);//printing the status in the end of the game
void startGame(Player& player,Diler& dealer,std::vector<Card>& cards);//starting the game, card shering
bool antherRound();//restrting the game
bool cardGameTake(Player& player,Diler& dealer,std::vector<Card>& cards);//taking cards in rounds
bool playerDrow(Player& player,std::vector<Card>& cards);//player taking a card
bool dealerDrow(Diler& dealer,Player& player,std::vector<Card>& cards);//dealer taking a card
bool got21(Player& player,Diler& dealer,std::vector<Card>& cards);//did on eof the player got blackjack?

