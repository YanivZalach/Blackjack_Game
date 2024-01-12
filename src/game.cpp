#include <iostream>
#include <vector>
//game functinalty
#include "classes.h"
#include "data.h"
#include "game.h"


//the game corent state
void printGameStatus(Player& player,Diler& dealer){
    system("cls"); //for mac and linux:  system("clear");
    std::cout<<"Your cards: ";
    player.printCards();
    std::cout<<"Your open card:";
    player.printShowCard();
    std::cout<<"The dealer's open card:";
    dealer.printShowCard();
}

//printing the end game resoult
void printEndGame(Player& player,Diler& dealer){
    std::cout<<"Showing the cards!"<<std::endl;
    std::cout<<"The dealer got: "<<std::endl;
    dealer.printCards();
    if(dealer.maxSum()<=21 &&(dealer.maxSum()>=player.maxSum()||player.maxSum()>21)){
        std::cout<<"YOU LOST THE GAME..."<<std::endl;
        if(dealer.maxSum()==player.maxSum()){
            std::cout<<"THE HOUSE WINS IN A TIE"<<std::endl;
        }
    }
    else if(player.maxSum()<=21){
        std::cout<<"YOU WON THE GAME!!!"<<std::endl;
    }
    else{
        std::cout<<"You have both lost..."<<std::endl;
    }
}

//the opening of the game
void startGame(Player& player,Diler& dealer,std::vector<Card>& cards){
    std::cout<<"STARTING THE GAME"<<std::endl;
    std::cout<<"2 cardes for each, one open"<<std::endl;
    dealer.addValueCardDiler(cards.back());// inserting the last element
    cards.pop_back();//removing it
    dealer.addValueCardDiler(cards.back());
    cards.pop_back();
    player.addValueCard(cards.back());
    cards.pop_back();
    player.addValueCard(cards.back());
    cards.pop_back();

    //read time - add timer
}

//the rounds of the game
bool cardGameTake(Player& player,Diler& dealer,std::vector<Card>& cards){
    //if the player had ended to take cards
    bool playerWantToDrow = true;
    bool dealerWantToDrow = true;
    int i =0;//making shore we dont pass chackLimit
    while ((playerWantToDrow||dealerWantToDrow)&&(chackLimit>i))
    {
        if(got21(player,dealer,cards)){
            return false;
        }
        //printing the round
        std::cout<<"Round "<<(i+3)<<std::endl;//i starts from 0, and we have 2 cards
        if(playerWantToDrow ==true){
            playerWantToDrow = playerDrow(player,cards);
        }
        if(dealerWantToDrow ==true){
            dealerWantToDrow = dealerDrow(dealer, player,cards);
        }
        //time to read - add timer
        printGameStatus( player, dealer);
        i++;//incresing i
    }
    return true;
}

//did on eny of the player got blackjack?
bool got21(Player& player,Diler& dealer,std::vector<Card>& cards){
    //21?
    //both
    if(dealer.maxSum()==21&&player.maxSum()==21){
        std::cout<<"WHIT!"<<std::endl;
		// Add timer
        std::cout<<"YOU BOTH GOT A BLACKJACK!!!"<<std::endl;
        return true;
    }
    //player
    if(player.maxSum()==21){
        std::cout<<"WHIT!"<<std::endl;
		// Add timer
        std::cout<<"YOU WIN, YOU GOT A BLACKJACK!!!"<<std::endl;
         return true;
    }
    //dealer
    if(dealer.maxSum()==21){
        std::cout<<"WHIT!"<<std::endl;
		// Add timer
        std::cout<<"YOU LOST, THE DEALER GOT A BLACKJACK!!!"<<std::endl;
         return true;
    }
    return false;
}

//the player drows a card
bool playerDrow(Player& player,std::vector<Card>& cards){
    //the player drows a card
    char inputTakeCard;
    //input from the player
    std::cout<<"Take anther card?"<<'\n'<<"(y=take/N=stop)"<<std::endl;
    std::cin>>inputTakeCard;
    if(inputTakeCard=='y'||inputTakeCard=='Y')
    {
        player.addValueCard(cards.back());
        cards.pop_back();
        std::cout<<"You drow a card!"<<std::endl;
        return true;
    }
    //else - stop taking cards
    std::cout<<"You stoped drowing!"<<std::endl;
    return false;
}

//the dealer drows a card
bool dealerDrow(Diler& dealer,Player& player,std::vector<Card>& cards){
    //the dealer drows a card
    int dealerDecision = dealer.probCardValue(player.getShowCard().values[0]);
    if (dealerDecision == 1) {
        std::cout<<"The dealer drow a card!"<<std::endl;
        dealer.addValueCardDiler(cards.back());
        cards.pop_back();
        return true;
    } 
    //else
    std::cout<<"The dealer stoped drowing!"<<std::endl;
    return false;
}

//at the end of the game 
bool antherRound(){
    //a new game?
    std::cout<<"Anther round(y/N)?"<<std::endl;
    char run;
    std::cin >> run;
    if(run == 'y'|| run =='Y'){
        return true;
    }
    return false;
}

