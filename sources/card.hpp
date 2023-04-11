#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;
namespace ariel {};
using namespace ariel;

class Card {
    
    //All are private by default, wrote this so it's easier to understand
    private: 
        int number;
        string suit;
    
    public:
        //Empty constructor - not default since there's another one
        Card();
        // Parametized constructor
        Card(int number, string suit);

        void setNumber(int);
        void setSuit(string);

        int getNumber();
        string getSuit();
        
        void toString();
};

#endif