// Includes
#include <iostream>
#include <vector>
#include <memory>
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

// Method to get the sum of all the open cards of the player
int Player::getShowCardsSum(){
	// Creating a counter to sum all the show cards
	int show_sum;

	if (this->cards.size() > (CARDSNOTSHOWN)) { // We have cards to show?

		for (size_t i = CARDSNOTSHOWN; i < this->cards.size(); i++) {
			// Adding the cards value to sum, adding the `A` as 1(at location 0) for making 'takeCardDealer' based on this more accurate
			show_sum+=(this->cards[i])->values[0];
		}
	}
	return show_sum;
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
	if (this->cards.size() > (CARDSNOTSHOWN)) {
		for (size_t i = CARDSNOTSHOWN; i < this->cards.size(); i++) {
			// Display the symbols of the cards
			std::string value = TrueValueCard(this->cards[i]);
			std::cout << " " << value << " ";
		}
		std::cout << std::endl;  // New line
	}
}

// Method to get the biggest sum
int Player::maxSum(){
     std::vector<int> sums_max_sum = this->getSums();
	 // Sorting for vector
    std::sort(sums_max_sum.begin(), sums_max_sum.end()); 
    //  If there is more then one we will find the max one
	for (size_t i = sums_max_sum.size() - 1 ; i > 0; i--) {
        if(sums_max_sum[i] <= LOSTLIMIT){
            return sums_max_sum[i];
        }
	}
    return sums_max_sum[0];//the lowest one is more then 21 - we lost :(
}

// Method to add a new card to the player's hand
void Player::addValueCard( std::unique_ptr<Card> card_in){

	// The vector of the sums
     std::vector<int> sums_vector = this->getSums();

    // Update all the sums combinations
    bool is_a = (card_in->symbol=='A');  // is the card an A?

    std::vector<int> for_a;  //vector for case that the card is A, added to the sums vector at the end of the function

    //  Adding the value to the sum
    for(size_t i = 0;i<sums_vector.size();i++){
        // Add the value of the new card to each sum
		sums_vector[i]+=card_in->values[0];
        if(is_a){
            // If the new card is an Ace, it can have an additional value of 11, so we add 10 to the sum (11-1)
            for_a.push_back(sums_vector[i]+(card_in->values[1]-card_in->values[0]));
        }
    }
    //adding the 'for_a' vector if created
    if(is_a){
        //using the insert method
        sums_vector.insert(sums_vector.end(),for_a.begin(),for_a.end());
    }

    //removing duplicates for faster use
    uniqeValuesOnlyVector(sums_vector);

	// Adding the card to the player hand - moving the pointer - doing this in the end for no 'Address boundary error'
    this->cards.push_back( std::move(card_in));
}

// --------- Dealer Class ---------
/*
  Inherit from the Player class.
  Add functionality: take a new card or not based on the dealer's cards
*/
Dealer:: Dealer():Player(){
    this->count_remaining_cards = SUMDECK;  // A const in the `.h` file
};


// Method to add a new card to the dealer's hand
void Dealer::addValueDealer( std::unique_ptr<Card> card_in){
    // Subtract the value of the new card from the sum of remaining cards to the eyes of the dealer
    this->count_remaining_cards-=card_in->values[0];
    // Add the new card to the dealer's hand using the addValueCard method of the player class
    addValueCard(std::move(card_in));
}

// Method to calculate the average card value in the deck
bool Dealer::takeCardDealer(int enemy_card_show/*Player::getShowCardsSum()*/){
        // Take anther card?
        // Return: true - take, false - not take

        int max_sum=this->maxSum();  // My max sum

		// Based on the defined limit constants
        if(max_sum <= LOWLIMIT){
            return true;  // Take a new card
        }else if(max_sum>=HIGHLIMIT){
            return false;  // Don't take a new card
        }

        //else - based on the DEALERLOSSHEND constant
        double need_max =LOSTLIMIT- max_sum;  // Calculate the maximum needed card value to reach LOSTLIMIT without busting
        if(need_max<0){
            return false;  // We have already lost the game
        }
        // Calculating the probability of getting a card that does not lead to busting is higher than the threshold
        double avg_card_value  = (double)(this->count_remaining_cards -enemy_card_show) / COUNTDECK;

        if((need_max/avg_card_value)>DEALERLOSSHEND){
            return true;  // Take anther card
        }
        return false;  // Don't take anther card
}
