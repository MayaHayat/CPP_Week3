#include <iostream>
#include "player.hpp"
#include "card.hpp"


using namespace std;


Player :: Player (string name){
    this -> name = name;
    this ->numOfWins = 0;
    this ->numCardsWon = 0;
    this -> winner = false;
}

// ----------- getters ------------

string Player :: getName(){
    return this -> name;
}

int Player :: stacksize(){
    return this ->playerstack.size();
}

int Player :: cardesTaken(){
    return this -> numCardsWon;
}

int Player :: getNumWins(){
    return this -> numOfWins;
}

int Player :: getNumOfCardsWon(){
    return this ->numCardsWon;
}


// -------------- setters -----------------
void Player :: setNumWins(int numOfWins){
    this -> numOfWins = numOfWins;
}

void Player :: setNumOfCardsWon(int num){
    this -> numCardsWon = num;
}


//----------- everything needs to be private therfore the following-----------------

bool Player :: emptyStack(){
    return this-> playerstack.empty();
}

void Player :: popStack(){
    this->playerstack.pop();
}

Card Player :: topStack(){
    return this ->playerstack.top();
}

void Player :: pushIntoStack( Card card1){
    this ->playerstack.push(card1);
}