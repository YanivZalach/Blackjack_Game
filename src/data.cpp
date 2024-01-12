#include <iostream>
#include <vector>
#include "classes.h"
#include "data.h"
#include <ctime> //for creating the sead from courent time

std::vector<Card> crateDeakOfCards(){

    std::vector<Card> deak;
    for(int i = 0;i<numOfGroupsInDeak;i++){
            deak.push_back(Card{{2},'2'});
            deak.push_back(Card{{3},'3'});
            deak.push_back(Card{{4},'4'});
            deak.push_back(Card{{5},'5'});
            deak.push_back(Card{{6},'6'});
            deak.push_back(Card{{7},'7'});
            deak.push_back(Card{{8},'8'});
            deak.push_back(Card{{9},'9'});
            deak.push_back(Card{{10},'T'});
            deak.push_back(Card{{10},'J'});
            deak.push_back(Card{{10},'K'});
            deak.push_back(Card{{10},'Q'});
            deak.push_back(Card{{1,11},'A'});
    }
    return deak;
}

std::vector<Card> shffelDeakOfCards(){
        srand(time(NULL));//creating the sead from courent time
    //shfful the deck of cardes
    std::vector<Card> cardes = crateDeakOfCards();
    for(int i =0;i<cardes.size();i++){
        int randomN = (rand()%cardes.size());
        Card temp = cardes[randomN];
        cardes[randomN]=cardes[i];
        cardes[i]=temp;
    }
    return cardes;
}

