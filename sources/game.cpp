#include <iostream>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

// ------------- HELP FUNCTIONS ---------------

void initializeStack(vector <Card> &gamestack) {
    for (int i = 0; i < 13; ++i) {
        gamestack.push_back(Card(i+1, "clubs"));
        gamestack.push_back(Card(i+1, "hearts"));
        gamestack.push_back(Card(i+1, "diamonds"));        
        gamestack.push_back(Card(i+1, "spades"));
    }
}


void divideCards(Player &pl1, Player &pl2, vector <Card> &gamestack){
    for (size_t i = 0; i < 52; ++i) {
        if (i % 2 == 0)
            pl1.pushIntoStack(gamestack[i]);
        else
            pl2.pushIntoStack(gamestack[i]);
    }

}

// ----------- REQUESTED FUNCTIONS -------------

Game::Game(Player &pl1, Player &pl2) : pl1(pl1), pl2(pl2){

    if (this -> pl1.getName().empty() || this -> pl2.getName().empty()){
        throw std :: invalid_argument ("You must name 2 players in order to play this game. Please check names");
    }

    initializeStack(this -> gamestack);
    
    //cout << gamestack.size() <<  " gamestack size " << endl;

    // The shuffle function was taken from:  https://en.cppreference.com/w/cpp/algorithm/random_shuffle
    
    random_device random;
    mt19937 g(random());

    // Shuffle the vector using the random number generator
    shuffle(gamestack.begin(), gamestack.end(), g);

    if (gamestack.size() != 52) {
        throw std :: invalid_argument ("The stack is either missing some cards or has too many, please make sure to have 52 before restarting the game \n");
    }

    divideCards(this ->pl1, this ->pl2, gamestack);


    // Initializing the remaining fields:
    this -> numOfDraws = 0;
    this -> gameIsOver = false;
    this -> pl1.setNumWins(0);
    this -> pl2.setNumWins(0);
}

void Game :: playTurn(){
    
    //cout << pl1.stacksize() << " " << pl1.cardesTaken() << " " << pl2.stacksize() << " " << pl2.cardesTaken() << endl;

    // Make sure game is valid before playing :
    if (gameIsOver){
        throw logic_error ("Game is over, please restart a new game if you'd like to continue.");
        return;
    }

    if(&pl1==&pl2){        
    throw ("Both players have the same name please change one of them.");
    }

    if(pl1.stacksize() == 0 || pl2.stacksize() == 0){
        gameIsOver = true;
        printLastTurn();
        return;
    }
    Card c1 = pl1.topStack();
    Card c2 = pl2.topStack();
    pl1.popStack();
    pl2.popStack();

    //cout << c1.getNumber() << " c1 and c2: " << c2.getNumber() << " " << pl1.stacksize() << endl;
    string suit1 = c1.getSuit();
    string suit2 = c2.getSuit();
    string num1 = std :: to_string(c1.getNumber()) + " of ";
    string num2 = std :: to_string(c2.getNumber()) + " of ";
    string winner = " ";

    if (c1.getNumber() == 1 && c2.getNumber() != 2){
        winner = this->pl2.getName() + " wins!";
    }

    else if (c2.getNumber() == 1 && c1.getNumber() != 2){
        winner = this->pl1.getName() + " wins!";
    }

    else if (c1.getNumber() > c2.getNumber()){
        winner = this->pl1.getName() + " wins!";
    }

    else if (c1.getNumber() < c2.getNumber()){
        winner = this->pl2.getName()+ " wins!";
    }
    
    else if (c1.getNumber() == c2.getNumber()){
        winner = "-> Draw!";
    }
    string toPush = this -> pl1.getName() + " played "+ num1 + suit1 + " and " + this ->pl2.getName() + " played " + num2 + suit2 + " " + winner ;
    this->log.push_back(toPush);

    // Ace wins all but 2
    if (c1.getNumber() == 1 && c2.getNumber() != 2){
        pl1.setNumWins(pl1.getNumWins()+1);
        // pl1 which is the winner takes both cards
        pl1.setNumOfCardsWon(pl1.getNumOfCardsWon() + 2);
        winner = this->pl1.getName() + " wins!";
            
    }

    // Ace wins all but 2
    else if (c1.getNumber() != 2 && c2.getNumber() == 1){
        pl2.setNumWins(pl2.getNumWins()+1);
        // pl2 which is the winner takes both cards
        pl2.setNumOfCardsWon(pl2.getNumOfCardsWon() + 2);
        winner = this->pl2.getName() + " wins!";
    }

    // Else if pl1 wins the round:
    else if (c1.getNumber() > c2.getNumber()){
        pl1.setNumWins(pl1.getNumWins()+1);
        // pl1 which is the winner takes both cards
        pl1.setNumOfCardsWon(pl1.getNumOfCardsWon() + 2);
        winner = this->pl1.getName() + " wins!";
    }

    // If pl2 wins the round:
    else if (c1.getNumber() < c2.getNumber()){
        pl2.setNumWins(pl2.getNumWins()+1);
        // pl2 which is the winner takes both cards
        pl2.setNumOfCardsWon(pl2.getNumOfCardsWon() + 2);
        winner = this->pl2.getName() + " wins!";
    }
        
    else {
        winner =  " Draw!";
        //cout << " ---------DRAW---------" << endl;

        vector <Card> adding; // cards that we put on table
        while (c1.getNumber() == c2.getNumber()){
            this ->numOfDraws++;

            // if cannot do war
            if (this -> pl1.stacksize() < 2 && this -> pl2.stacksize() < 2 ){
                    
                pl1.setNumOfCardsWon(pl1.getNumOfCardsWon() + pl1.stacksize()+1);
                pl2.setNumOfCardsWon(pl2.getNumOfCardsWon() + pl1.stacksize()+1);
                if (!pl1.emptyStack()) {
                    pl1.popStack();
                }
                if (!pl2.emptyStack()) {
                    pl2.popStack();
                }
                gameIsOver = true; 
                break;
            }

            // else begin war:
            adding.push_back(c1);
            adding.push_back(c2);
            //cout << adding.size() << " adding" << endl;
            c1 = this -> pl1.topStack();
            c2 = this -> pl2.topStack();
            adding.push_back(c1); // the upside down card
            adding.push_back(c2); // the upside down card
            //cout << adding.size() << " adding" << endl;
            this -> pl1.popStack();
            this -> pl2.popStack();
            c1 = this -> pl1.topStack();
            c2 = this -> pl2.topStack();
            this -> pl1.popStack();
            this -> pl2.popStack();
            //cout << c1.getNumber() << " c1 and c2: " << c2.getNumber() << " " << pl1.stacksize() << endl;
            adding.push_back(c1); 
            adding.push_back(c2);
            //cout << adding.size() << " adding" << endl;


            // Ace wins all but 2
            if (c1.getNumber() == 1 && c2.getNumber() != 2){
                pl1.setNumWins(pl1.getNumWins()+1);
                // pl1 which is the winner takes both cards
                int toAdd = adding.size();
                pl1.setNumOfCardsWon(pl1.getNumOfCardsWon() + toAdd);
                if (!adding.empty()){
                    adding.pop_back();
                }                    
            }

                // Ace wins all but 2
                else if (c1.getNumber() != 2 && c2.getNumber() == 1){
                    pl2.setNumWins(pl2.getNumWins()+1);
                    // pl2 which is the winner takes both cards
                    int toAdd = adding.size();
                    pl2.setNumOfCardsWon(pl2.getNumOfCardsWon() + toAdd);
                    if (!adding.empty()){
                        adding.pop_back();
                    }
                }

                // Else if pl1 wins the round:
                else if (c1.getNumber() > c2.getNumber() && c2.getNumber() != 1){
                    pl1.setNumWins(pl1.getNumWins()+1);
                    // pl1 which is the winner takes both cards
                    int toAdd = adding.size();
                    pl1.setNumOfCardsWon(pl1.getNumOfCardsWon() + toAdd);
                    if (!adding.empty()){
                        adding.pop_back();
                    }
                }

                // If pl2 wins the round:
                else if (c1.getNumber() < c2.getNumber() && c1.getNumber() != 1){
                    pl2.setNumWins(pl2.getNumWins()+1);
                    // pl2 which is the winner takes both cards
                    int toAdd = adding.size();
                    pl2.setNumOfCardsWon(pl2.getNumOfCardsWon() + toAdd);
                    if (!adding.empty()){
                        adding.pop_back();
                    }
                }

                if (pl1.stacksize() == 0 && pl2.stacksize() == 0 && c1.getNumber() == c2.getNumber() && adding.size() > 5){
                    random_device random;
                    mt19937 g(random());

                    // Shuffle the vector using the random number generator
                    shuffle(gamestack.begin(), gamestack.end(), g);

                    divideCards(this ->pl1, this ->pl2, gamestack);
                }


            }


            if (pl1.stacksize() == 0 && pl2.stacksize() == 0){
            gameIsOver = true;
            if (pl1.getNumOfCardsWon() > pl2.getNumOfCardsWon()){
                cout << pl1.getNumOfCardsWon() << " " << pl2.getNumOfCardsWon() << endl;
                cout << pl1.getName() << " won!" << endl;
            }
            else if (pl1.getNumOfCardsWon() < pl2.getNumOfCardsWon()){
                cout << pl1.getNumOfCardsWon() << " " << pl2.getNumOfCardsWon() << endl;
                cout << pl2.getName() << " won!" << endl;
            }
            else{
                cout << pl1.getNumOfCardsWon() << " " << pl2.getNumOfCardsWon() << endl;
                cout << " Game ended with a tie, both players have the same number of cards in stack" << endl;
            }
        }
        //cout << adding.size() << "  adding " << endl;

    }
}


void Game :: printLastTurn(){
    if (log.empty()){
        throw std::runtime_error("Log is empty, cannot print last turn");
    }
    string lastTurn = "";
    lastTurn = log.back();  //CHECK if need to be popped or nah
    cout << lastTurn << endl;
}

void Game :: playAll(){
    if (gameIsOver){
        throw std :: logic_error ("Game has ended please start a new game if wanted.");
    }
    while (this -> pl1.stacksize() != 0 && this -> pl2.stacksize() != 0){
        playTurn();
    }
    gameIsOver = true;

}

void Game :: printWiner(){
    if (pl1.cardesTaken() > pl2.cardesTaken()){
        cout << pl1.getName() + " wins! " << endl;
        printLastTurn();
    }
    else if (pl1.cardesTaken() < pl2.cardesTaken()){
        cout << pl2.getName() + " wins! " << endl;
        printLastTurn();
    }
    else if(pl1.cardesTaken() == pl2.cardesTaken() && pl1.getName() != pl2.getName()){
        cout << " No one wins! There's a tie! " << endl;
    }
}

void Game :: printLog(){
    for (size_t i = 0 ; i < log.size() ; i++){
        string ans = log[i];
        cout << ans << endl;
    }
}

void Game :: printStats(){
    cout << pl1.getName() << " won " << pl1.getNumWins() << " times and got " << pl1.cardesTaken() << " cards" << endl;
    cout << pl2.getName() << " won " << pl2.getNumWins() << " times and got " << pl2.cardesTaken() << " cards" << endl;
    cout << "Overall there were " << (this ->numOfDraws) << " draws" << endl;
}