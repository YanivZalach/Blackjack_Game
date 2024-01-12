// Includes
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cmath>  // For using 'abs'
#include <algorithm>  // For shrinking the vector to his unique values

#include "classes.h"

// --------- Player Score ---------
/*
	Function to calculate all the player possible scores (For the `A` card)
	This effectively reduces the container size by the number of elements removed, which are destroyed.
*/
void uniqeValuesOnlyVector(std::vector<int>& sums) {
	// Sorting the vector
    std::sort(sums.begin(), sums.end());
	// Removing duplicates
    auto last = std::unique(sums.begin(), sums.end());
	// Resizing the vector for it's new size
    sums.erase(last, sums.end());
}

// --------- Card Value ---------
// Function to get the true value of the card - for printing
std::string TrueValueCard(const std::unique_ptr<Card>& card){
	if(card->symbol=='T'){
		// T symbols 10, using 1 char
		return "10";
	}
	// Convert the card symbol to a string and return
    return std::string(1, card->symbol);
}


// --------- Player Class ---------
// Constructor
Player::Player(){
    this->sums = {0};// Initialize sums with 0 to start the game
};

// Getter to the sum
std::vector<int>& Player::getSums(){
    //returning all the sums to work with
    return this->sums;
}

// Method to print ALL of the user cards
void Player::printCards() {
	std::cout << std::endl;  // New line

	// Printing all the cards the user has
	if (!this->cards.empty()) {
		for (const std::unique_ptr<Card>& card : this->cards) {
			// Display the symbols of the cards
			std::string value = TrueValueCard(card);
			std::cout << " " << value << " ";
		}
		std::cout << std::endl;  // New line
	}
}

// Printing the opened cards
void Player::printShowCard(){
	std::cout << std::endl;  // New line

    // Printing the show cards of the user
	if (this->cards.size() > (cardsNotShown + 1)) {
		for (size_t i = cardsNotShown; i < this->cards.size(); i++) {
			// Display the symbols of the cards
			std::string value = TrueValueCard(this->cards[i]);
			std::cout << " " << value << " ";
		}
		std::cout << std::endl;  // New line
	}
}

// Method to get the biggest sum
int Player::maxSum(){
     std::vector<int> sumsMaxSum = this->getSums();
	 // Sorting for vector
    std::sort(sumsMaxSum.begin(), sumsMaxSum.end()); 
    //  If there is more then one we will find the max one
	for (size_t i = sumsMaxSum.size() - 1 ; i > 0; i--) {
        if(sumsMaxSum[i] <= 21){
            return sumsMaxSum[i];
        }
	}
    return sumsMaxSum[0];//the lowest one is more then 21 - we lost :(
}

// Method to add a new card to the player's hand
void Player::addValueCard( std::unique_ptr<Card>& cardIn){
	// Adding the card to the player hand
    this->cards.push_back(cardIn);

	// The vector of the sums
     std::vector<int> sumsVector = this->getSums();

    // Update all the sums combinations
    bool isAese = (cardIn->symbol=='A');  // is the card an A?

    std::vector<int> forA;  //vector for case that the card is A, added to the sums vector at the end of the function

    //  Adding the value to the sum
    for(size_t i = 0;i<sumsVector.size();i++){
        // Add the value of the new card to each sum
		sumsVector[i]+=cardIn->values[0];
        if(isAese){
            // If the new card is an Ace, it can have an additional value of 11, so we add 10 to the sum (11-1)
            forA.push_back(sumsVector[i]+(cardIn->values[1]-cardIn->values[0]));
        }
    }
    //adding the 'forA' vector if created
    if(isAese){
        //using the insert method
        sumsVector.insert(sumsVector.end(),forA.begin(),forA.end());
    }

    //removing duplicates for faster use
    uniqeValuesOnlyVector(sumsVector);
}

// Did to here------------------------------- ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ------------------------------ ----------------------------- 



// Inherit from the Player class but add functionality to calculate whether to take a new card or not based on the dealer's cards
// Using the constructor of the parent class
Dealer:: Dealer():Player(){
    this->calcTheRemaingPackDealerKnow = sumDeck;
    // We are preparing for the worst case, where in the worst case, every Ace can be 1,
    // so we add 10*4 because of - 10, J, K, Q (four of each)
};


// Method to add a new card to the dealer's hand
void Dealer::addValueCardDiler( Card cardnt){
    // Subtract the value of the new card from the sum of remaining cards
    this->calcTheRemaingPackDealerKnow-=cardnt.values[0];
    // Add the new card to the dealer's hand using the base class method
    addValueCard(cardnt);
}

         
// Method to calculate the average card value in the deck
int Dealer::probCardValue(int enemyCardShow){
        // Tif to take anther card or not
        // 1-yes,0-no,-1 - lost the game;
        int maxS=this->maxSum();
        if(maxS<=lowLimit){
            return 1;// It's safe to take a new card
        }
        else if(maxS>=highLimit){
            return 0;// It's risky to take a new card
        }
        //else
        // Calculate the maximum needed card value to reach lostLimit without busting
        double needMax =lostLimit- maxS;
        if(needMax<0){
            return -1;// We have already lost the game
        }
        // Check if the probability of getting a card that does not lead to busting is higher than the threshold
        double avgCardValue  = (this->calcTheRemaingPackDealerKnow -enemyCardShow) / countDeck;
        if((needMax/avgCardValue)>dealerLossHend){
            return 1;// It is safe to take a new card
        }
        return 0;// It is risky to take a new card
}

