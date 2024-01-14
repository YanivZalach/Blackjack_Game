#pragma once

// Includes
#include <memory>
#include <vector>

//-------------------------------------------------- 
// --------- Consts ---------

// --------- The Dealer Limits ---------
// How match is the dealer going to bet his cards; the smaller the lesser
const double DEALERLOSSHEND = 0.95;
// Limits
const int LOWLIMIT = 12;  // If lowLimit >= dealerHead -> Taking card
const int HIGHLIMIT = 18;  // If highLimit <= dealerHead -> Not taking card

// --------- Deck Const ---------
// The sum of the cards deck 
const int SUMDECK = 4*(1+2+3+4+5+6+7+8+9+10*4);
/*
   We are preparing for the worst case, where in the worst case, every Ace can be 1,
   We add 10*4 because of - 10, J, K, Q (four of each)
*/

// The amount of cards in a deck
const int COUNTDECK = 13*4;

// --------- Game Limit ---------
const int LOSTLIMIT = 21;// If Hend > lostLimit -> Lost the game

// --------- Cards Not Shown ---------
const int CARDSNOTSHOWN = 1;

// --------- Opening Game Cards ---------
const int OPENINGGAMECARDS = 2;

//-------------------------------------------------- 
// --------- Structs ---------

// --------- Card Struct ---------
struct Card {
    std::vector<int> values;  // Possible values of the card (useful for cards like Aces with values 1 or 11)
    char symbol;  // Symbol representing the card (e.g., 'A' for Ace, 'K' for King, etc.)
};

//-------------------------------------------------- 
// --------- Functions ---------

// --------- Player Score ---------
// Function to calculate all the player possible scores (For the `A` card)
void uniqeValuesOnlyVector(std::vector<int>& sums);

// --------- Card Value ---------
// Function to get the true value of the card - for printing
std::string TrueValueCard(const std::unique_ptr<Card>& card);

//-------------------------------------------------- 
// --------- Classes ---------

// --------- Player Class ---------
class Player
{
    private:

        std::vector<std::unique_ptr<Card>> cards;  // The player's cards
        std::vector<int> sums;  // All possible sums of the player's card values

    public:

        Player();  // Constructor
        std::vector<int>& getSums();  // Method to get all the sums of the player's card values
		int getShowCardsSum();  // Method to get the sum of all the open cards of the player
        void printCards();  // Method to print all of the user cards
        void printShowCard();  // Printing the opened cards

        int maxSum();  // Method to get the biggest sum the player has

		void addValueCard(std::unique_ptr<Card> card_in);  // Method to add a new card to the player's hand
};

// --------- Dealer Class ---------
/*
  Inherit from the Player class.
  Add functionality: take a new card or not based on the dealer's cards
*/
class Dealer : public Player
{
	private:
		int count_remaining_cards;  // The sum of the remaining cards in the deck throw the *dealer eyes*

	public:
		Dealer(); // Using the constructor of the parent class
		void addValueDealer( std::unique_ptr<Card> card_in);  // Method to add a new card to the dealer's hand
        bool takeCardDealer(int enemy_card_show);  // Method to calculate the average card value in the deck(0-dont take,1-take,-1-lost)
};
