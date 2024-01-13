// Includes
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "classes.h"
#include "data.h"

static std::vector<std::unique_ptr<Card>> crateDeakOfCards(){

    std::vector<std::unique_ptr<Card>> deak;
    for(int i = 0;i<NUMOFGROUPSINDEAK;i++){
            deak.push_back(std::make_unique<Card>(Card{{2},'2'}));
            deak.push_back(std::make_unique<Card>(Card{{3},'3'}));
            deak.push_back(std::make_unique<Card>(Card{{4},'4'}));
            deak.push_back(std::make_unique<Card>(Card{{5},'5'}));
            deak.push_back(std::make_unique<Card>(Card{{6},'6'}));
            deak.push_back(std::make_unique<Card>(Card{{7},'7'}));
            deak.push_back(std::make_unique<Card>(Card{{8},'8'}));
            deak.push_back(std::make_unique<Card>(Card{{9},'9'}));
            deak.push_back(std::make_unique<Card>(Card{{10},'T'}));
            deak.push_back(std::make_unique<Card>(Card{{10},'J'}));
            deak.push_back(std::make_unique<Card>(Card{{10},'K'}));
            deak.push_back(std::make_unique<Card>(Card{{10},'Q'}));
            deak.push_back(std::make_unique<Card>(Card{{1,11},'A'}));
    }
    return deak;
}

std::vector<std::unique_ptr<Card>> shffelDeakOfCards(){
	srand(time(NULL));// Creating the seed for random shuffle

	// Creating the deck of cards
	std::vector<std::unique_ptr<Card>> cardes = crateDeakOfCards();

  // Shuffle the deck of cards
	for(int i =0;i<cardes.size();i++){
		// Random index
		int randomN = (rand()%cardes.size());
		// Moving the current index with the random one
		std::unique_ptr<Card> temp = std::move(cardes[randomN]);
		cardes[randomN]=std::move(cardes[i]);
		cardes[i]=std::move(temp);
	}
	return cardes;
}
