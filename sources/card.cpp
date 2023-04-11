#include <iostream>
#include "card.hpp"

Card :: Card (int number, string suit){
    this ->number = number;
    this ->suit =  suit;
}


// ---------- getters -----------
int Card :: getNumber(){
    return this ->number;
}

string Card :: getSuit(){
    return this -> suit;
}

// ---------- setters -----------

void Card :: setNumber(int number){
    this -> number = number;
}

void Card :: setSuit(string suit){
    this -> suit = suit;
}

void Card :: toString (){
    cout << "Number: " << this->number << " suit: " << this->suit << "\n";
}