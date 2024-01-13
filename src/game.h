#pragma once

// Includes
#include <iostream>
#include <memory>
#include <vector>

#include "classes.h"
#include "data.h"


//-------------------------------------------------- 
// --------- Consts ---------
// The max card a player is allowed to take in a game
const int CHACKLIMIT = 10;

// Sleep time for the game
const int LONGSLEEP = 3500;
const int SHORTSLEEP = 2000;

//-------------------------------------------------- 
// --------- Functions ---------

// Function to clear the console
void clearConsole();

// Printing the status of the game
void printGameStatus(Player *&player,Dealer *&dealer);

// Printing the status in the end of the game
void printEndGame(Player *&player,Dealer *&dealer);

// Starting the game, card handling
void startGame(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards);

// Taking cards in the game rounds
bool cardGameTake(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards);

// Player taking a card
bool playerDrow(Player *&player,std::vector<std::unique_ptr<Card>>& cards);

// Dealer taking a card
bool dealerDrow(Dealer *&dealer,Player *&player,std::vector<std::unique_ptr<Card>>& cards);

// Did on the first round the player got blackjack?
bool gotBlackJack(Player *&player,Dealer *&dealer,std::vector<std::unique_ptr<Card>>& cards);

// Resting the game
bool antherRound();

