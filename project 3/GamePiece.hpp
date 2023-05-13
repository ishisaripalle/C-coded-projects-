#pragma once

#include <sstream>
#include <string> 
#include "GameState.hpp"

using std::string; 
using std::ostream; 

class GameState; 

class GamePiece {
  private: 
    //member variables 
    string name_of_player; 
    string type_of_gamepiece; 
    GameState *state;
  public:  
    //constructors and destructors
    GamePiece (const string &name_of_player, const string  &type_of_gamepiece, GameState *state); 
    GamePiece (const GamePiece &p);  
    //~GamePiece(); 
    //accessors
    //string GetPlayer(); 
   //string GetType(); 
    int GetPower(); 
    //int GetSpeed();
    //comparison operators 
    /*bool operator==(const GamePiece &p);
    bool operator!=(const GamePiece &p);
    bool operator<(const GamePiece &p);
    bool operator>(const GamePiece &p);
    bool operator<=(const GamePiece &p);
    bool operator>=(const GamePiece &p);
    //assignment operator 
    GamePiece& operator=(const GamePiece &p);*/
};

//ostream  
//ostream& operator<<(ostream &os, const GamePiece &p);