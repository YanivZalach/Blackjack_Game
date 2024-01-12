#pragma once
#include <vector>

//const
const int sumDeak = 340;//4*(1+2+3+4+5+6+7+8+9+10*4)
const int countDeak = 52;//13*4
const double dillerLossHend = 0.95;//how match is the diller going to bet his cards, the smaller the losser
//the diller limits
const int lowLimit = 11;//billow and if equle the diller will take anter card
const int highLimit = 18;//billow and if equle the diller will not take anter card
const int lostLimit = 21;//if pass this num the player is losing the game

//makeing the list to conting only uniqe values
void uniqeValuesOnlyVector(std::vector<int>& sums);

// The struct for a card in the game
struct Card {
    std::vector<int> values;// Possible values of the card (useful for cards like Aces with values 1 or 11)
    char symbol;// Symbol representing the card (e.g., 'A' for Ace, 'K' for King, etc.)
};

class Player
{
    private:

        std::vector<Card> cards;// The player's cards
        std::vector<int> sums;// All possible sums of the player's card values

    public:

        Player();
        // Method to print all the cards the user has
        void printCards();
        // Method to get all the sums of the player's card values
        std::vector<int>& getSums();
        // Method to add a new card to the player's hand
        void addValueCard( Card cardIn);//!not work
        //Method to get the biggest sum
        int maxSum();
        //getting the card that is open by me
        const Card& getShowCard();
        //printing the show cars
        void printShowCard();
};

// Inherit from the Player class but add functionality to calculate whether to take a new card or not based on the dealer's cards
class Diler : public Player
{
	private:
		int calcTheRemaingPackDealerKnow;//The sum of the remaining cards in the deck/ throw the dillr eyes, dont know what the player had pold

	public:
		// Using the constructor of the parent class
		Diler();
        // Method to add a new card to the dealer's hand
        void addValueCardDiler( Card cardnt);
        // Method to calculate the average card value in the deck
        int probCardValue(int enemyCardShow);//0-dont take,1-take,-1-lost
};
