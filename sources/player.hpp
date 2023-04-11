#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <stack>

#include "card.hpp"

using namespace std;
namespace ariel {};
using namespace ariel;

class Player {
    
    //All are private by default, wrote this so it's easier to understand
    private: 
        string name;

        int numCardsWon;

        int numOfWins;

        bool winner ;

        stack <Card> playerstack;


    
    public:
        //Empty constructor - not default since there's another one
        // Parametized constructor
        Player(string name);

        string getName();

        void setName(string);


        int getNumWins();

        void setNumWins(int numOfWins);

        int getNumOfCardsWon();
        void setNumOfCardsWon(int num);
    
        // stack <Card> playerstack;

        bool emptyStack();

        void popStack();

        Card topStack();

        int stackSizeP();

        void pushIntoStack( Card card1);


        

        

//------------------------ requested functions ---------------------
        // amount of cards left in stack
        int stacksize(); 
        // amount of cards won by the current player
        int cardesTaken(); 
            

};

#endif