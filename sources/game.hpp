#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "player.hpp"
#include "card.hpp"

using namespace std;
namespace ariel {};
using namespace ariel;

class Game {
    
    //All are private by default, wrote this so it's easier to understand
    private: 
        
        Player &pl1;
        Player &pl2;
        
        vector <string> log; // used in order to keep what happens in each round
        vector <Card> gamestack; // initially would contain 52 cards, need to be shuffled before each game
        
        int numOfDraws;

        bool gameIsOver;

    public:
        

        //Empty constructor - not default since there's another one
        // Parametized constructor
        Game(Player &pl1, Player &pl2);

        void setPlayers(Player, Player);
        
        int getPlayers();
        
//------------------------ requested functions ---------------------
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();

        string toString();
        

};

#endif