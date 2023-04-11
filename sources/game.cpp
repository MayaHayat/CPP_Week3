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


void divideCards(Player &p1, Player &p2, vector <Card> &gamestack){
    for (size_t i = 0; i < 52; ++i) {
        if (i % 2 == 0)
            p1.playerstack.push(gamestack[i]);
        else
            p2.playerstack.push(gamestack[i]);
    }

}

// ----------- REQUESTED FUNCTIONS -------------

Game::Game(Player &p1, Player &p2) : p1(p1), p2(p2){

    if (this -> p1.getName().empty() || this -> p2.getName().empty()){
        throw std :: invalid_argument ("You must name 2 players in order to play this game. Please check names");
    }

    initializeStack(this -> gamestack);
    
    cout << gamestack.size() <<  " gamestack size " << endl;


    //std::random_shuffle(this -> gamestack.begin(), this -> gamestack.begin());
    random_device random;
    mt19937 g(random());

    // Shuffle the vector using the random number generator
    shuffle(gamestack.begin(), gamestack.end(), g);

    if (gamestack.size() != 52) {
        throw std :: invalid_argument ("The stack is either missing some cards or has too many, please make sure to have 52 before restarting the game \n");
    }

    divideCards(this ->p1, this ->p2, gamestack);

    // cout << p1.stacksize() <<  " p1 stacksize " << endl;
    // cout << p2.stacksize() <<  " p2 stacksize " << endl;
    // cout << p1.cardesTaken() <<  " p1 cardstaken " << endl;
    // cout << p2.cardesTaken() <<  " p2 cardstaken " << endl;


    // Initializing the remaining fields:
    this -> numOfDraws = 0;
    this -> gameIsOver = false;
    this -> p1.setNumWins(0);
    this -> p2.setNumWins(0);
}

void Game :: playTurn(){
    
    cout << p1.stacksize() << " " << p1.cardesTaken() << " " << p2.stacksize() << " " << p2.cardesTaken() << endl;

    // Make sure game is valid before playing :
    if (gameIsOver){
        throw logic_error ("Game is over, please restart a new game if you'd like to continue.");
        return;
    }

    if(&p1==&p2){        
    throw ("Both players have the same name please change one of them.");
    }

    if(p1.stacksize() == 0 || p2.stacksize() == 0){
        gameIsOver = true;
        return;
    }
        Card c1 = p1.playerstack.top();
        Card c2 = p2.playerstack.top();
        p1.playerstack.pop();
        p2.playerstack.pop();

        cout << c1.getNumber() << " c1 and c2: " << c2.getNumber() << " " << p1.playerstack.size() << endl;
        string suit1 = c1.getSuit();
        string suit2 = c2.getSuit();
        string toPush = this ->p1.getName() + " played ";// << c1.getNumber() <<  " " << suit1 <<"\n" << this -> p2.getName() << " played " << c2.getNumber() << " " << suit2;
        this->log.push_back(toPush);
    

        // Ace (1) loses to two (2) 
        int NumOfCardsAddingUp = 2;
        
        if (c1.getNumber() == 2 && c2.getNumber() == 1){
            p1.setNumWins(p1.getNumWins()+1);
            // p1 which is the winner takes both cards
            p1.setNumOfCardsWon(p1.getNumOfCardsWon() + 2);
            
        }

        if (c1.getNumber() == 1 && c2.getNumber() == 2){
            p2.setNumWins(p2.getNumWins()+1);
            // p2 which is the winner takes both cards
            p2.setNumOfCardsWon(p2.getNumOfCardsWon() + 2);
        }

        // Else if p1 wins the round:
        else if (c1.getNumber() > c2.getNumber()){
            p1.setNumWins(p1.getNumWins()+1);
            // p1 which is the winner takes both cards
            p1.setNumOfCardsWon(p1.getNumOfCardsWon() + 2);
        }

        // If p2 wins the round:
        else if (c1.getNumber() < c2.getNumber()){
            p2.setNumWins(p2.getNumWins()+1);
            // p2 which is the winner takes both cards
            p2.setNumOfCardsWon(p2.getNumOfCardsWon() + 2);
        }
        
        else {
            vector <Card> adding;
            while (c1.getNumber() == c2.getNumber()){
                adding.push_back(c1);
                adding.push_back(c2);
                c1 = this ->p1.playerstack.top();
                c2 = this -> p2.playerstack.top();
                adding.push_back(c1); // the upside down card
                adding.push_back(c2); // the upside down card
                this -> p1.playerstack.pop();
                this -> p2.playerstack.pop();
                c1 = this ->p1.playerstack.top();
                c2 = this -> p2.playerstack.top();
                this -> p1.playerstack.pop();
                this -> p2.playerstack.pop();
                NumOfCardsAddingUp += 4;
                cout << " ---------DRAW---------" << endl;
                //cout << NumOfCardsAddingUp << "  adding up  " << endl;
                if (p1.stacksize() == 0 && p2.stacksize() == 0){
                    break;
                }
                if (p1.stacksize() == 0 && p2.stacksize() == 0 && c1.getNumber() == c2.getNumber() && adding.size() < 6){
                    gameIsOver = true;
                    if (p1.getNumOfCardsWon() > p2.getNumOfCardsWon()){
                        cout << p1.getName() << " won!" <<  p1.cardesTaken() << endl;
                    }
                    else if (p1.getNumOfCardsWon() < p2.getNumOfCardsWon()){
                        cout << p2.getName() << " won! " <<  p2.cardesTaken() <<endl;
                    }
                    else{
                        cout << " Game ended with a tie, both players have the same number of cards in stack" << endl;
                    }
                }

                if (p1.stacksize() == 0 && p2.stacksize() == 0 && c1.getNumber() == c2.getNumber() && adding.size() > 5){
                    random_device random;
                    mt19937 g(random());

                    // Shuffle the vector using the random number generator
                    shuffle(gamestack.begin(), gamestack.end(), g);

                    divideCards(this ->p1, this ->p2, gamestack);
                }


                if (p1.stacksize() > 0 && p2.stacksize() > 0){
                    c1 = this -> p1.playerstack.top();
                    c2 = this -> p2.playerstack.top();
                    p1.playerstack.pop();
                    p2.playerstack.pop();
                    //NumOfCardsAddingUp +=2;
                }
            }
            if (c1.getNumber() > c2.getNumber()){
                this ->p1.setNumWins(p1.getNumWins()+1);
                this->p1.setNumOfCardsWon(this->p1.getNumOfCardsWon()+ NumOfCardsAddingUp);
                cout << p1.stacksize() << " " << p1.cardesTaken() << " " << p2.stacksize() << " " << p2.cardesTaken() << endl;
                }
            else if(c1.getNumber() < c2.getNumber()){
                this ->p2.setNumWins(p2.getNumWins()+1);
                this ->p2.setNumOfCardsWon(this->p2.getNumOfCardsWon()+ NumOfCardsAddingUp);
                cout << p1.stacksize() << " " << p1.cardesTaken() << " " << p2.stacksize() << " " << p2.cardesTaken() << endl;

            }

            if (p1.stacksize() == 0 && p2.stacksize() == 0){
            gameIsOver = true;
            if (p1.getNumOfCardsWon() > p2.getNumOfCardsWon()){
                cout << p1.getName() << " won!" << endl;
            }
            else if (p1.getNumOfCardsWon() < p2.getNumOfCardsWon()){
                cout << p2.getName() << " won!" << endl;
            }
            else{
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
    while (this -> p1.stacksize() != 0 && this -> p2.stacksize() != 0){
        playTurn();
    }
    gameIsOver = true;

}

void Game :: printWiner(){
    if (p1.cardesTaken() > p2.cardesTaken()){
        cout << p1.getName() + " wins! " << endl;
    }
    else if (p1.cardesTaken() < p2.cardesTaken()){
        cout << p2.getName() + " wins! " << endl;
    }
    else if(p1.cardesTaken() == p2.cardesTaken() && p1.getName() != p2.getName()){
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
    cout << p1.getName() << " won " << p1.getNumWins() << " times and got " << p1.cardesTaken() << " cards" << endl;
    cout << p2.getName() << " won " << p2.getNumWins() << " times and got " << p2.cardesTaken() << " cards" << endl;
    cout << "Overall there were " << (this ->numOfDraws) << " draws" << endl;
}