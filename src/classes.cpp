#include <iostream>
#include <vector>
#include "classes.h"
#include <cmath>//for abs
#include <algorithm>//for srinking the vector to his uniqe values

//makeing the list to conting only uniqe values
//This effectively reduces the container size by the number of elements removed, which are destroyed.
void uniqeValuesOnlyVector(std::vector<int>& sums) {
    // sort followed by unique, to remove all duplicates
    std::sort(sums.begin(), sums.end());
    auto last = std::unique(sums.begin(), sums.end());
    sums.erase(last, sums.end());
}


//constracter
Player::Player(){
    this->sums = {0};// Initialize sums with 0 to start the game
};


// Method to print all the cards the user has
void Player::printCards(){
    std::cout<<std::endl;
    //printing all the cardes the user has
    if(!this->cards.empty())
    {
        for(auto i =this->cards.begin();i!=this->cards.end();i++){
            // Display the symbols of the cards
            if(i->symbol=='T'){//T is a char that is signals the card 10, so this is what we print
                std::cout <<" 10 ";
            }
            else{
                std::cout <<" "<<i->symbol<<" ";
            }
        }
    }
    std::cout<<std::endl;
}


// Method to get all the sums of the player's card values
std::vector<int>& Player::getSums(){
    //returning all the sums to work with
    return this->sums;
}


// Method to add a new card to the player's hand
void Player::addValueCard( Card cardIn){
    this->cards.push_back(cardIn);
    // Update all the sums combinations
    // is the card an A
    bool isAese = (cardIn.symbol=='A');
    //vector for case that the card is A
    std::vector<int> forA;
    //adding the value
    for(auto i = this->sums.begin();i!=this->sums.end();i++){
        // Add the value of the new card to each sum
        *i+=cardIn.values[0];
        if(isAese){
            // If the new card is an Ace, it can have an additional value of 11, so we add 10 to the sum
            forA.push_back(*i+10);
        }
    }
    //adding in the case of A
    if(isAese){
        //using the insert mathed
        this->sums.insert(this->sums.end(),forA.begin(),forA.end());
    }

    //removing doplicets
    uniqeValuesOnlyVector(this->sums);
}


//Method to get the biggest sum
int Player::maxSum(){//trying not to inclode above 21 -> is so we lost
     std::vector<int> sumsMaxSum = this->getSums();
    //making shore the vector of sums is order for more aficent code
    std::sort(sumsMaxSum.begin(), sumsMaxSum.end()); 
    //if there is more then one we will find the max one
    for(auto i = std::prev(sumsMaxSum.end());i>=sumsMaxSum.begin();i--){//using std::prev(sumsMaxSum.end()) because we start at the leat elemet of the vector
        if(*i<=21){
            return *i;
        }
    }
    return sumsMaxSum[0];//the lowes one - more then 21
}

//getting the card that is open by me
const Card& Player::getShowCard(){
    return *(this->cards.begin());
}

// Method to print all the cards the user has
void Player::printShowCard(){
    std::cout<<std::endl;
    //printing the show card of the user
    if(this->getShowCard().symbol=='T'){//T is a char that is signals the card 10, so this is what we print
        std::cout <<" 10 ";
    }
    else{
        std::cout <<" "<<this->getShowCard().symbol<<" ";
    }
    std::cout<<std::endl;
}


// Inherit from the Player class but add functionality to calculate whether to take a new card or not based on the dealer's cards
// Using the constructor of the parent class
Diler:: Diler():Player(){
    this->calcTheRemaingPackDealerKnow = sumDeak;
    // We are preparing for the worst case, where in the worst case, every Ace can be 1,
    // so we add 10*4 because of - 10, J, K, Q (four of each)
};


// Method to add a new card to the dealer's hand
void Diler::addValueCardDiler( Card cardnt){
    // Subtract the value of the new card from the sum of remaining cards
    this->calcTheRemaingPackDealerKnow-=cardnt.values[0];
    // Add the new card to the dealer's hand using the base class method
    addValueCard(cardnt);
}

         
// Method to calculate the average card value in the deck
int Diler::probCardValue(int enemyCardShow){
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
        double avgCardValue  = (this->calcTheRemaingPackDealerKnow -enemyCardShow) / countDeak;
        if((needMax/avgCardValue)>dillerLossHend){
            return 1;// It is safe to take a new card
        }
        return 0;// It is risky to take a new card
}

