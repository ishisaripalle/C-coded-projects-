#pragma once

#include <string> 
#include <vector> 

using std::string; 
using std::vector; 

class GameState {
  private: 
    vector< std::pair <string, string> > vect; 
  public: 
   // GameState() = default; 
    //int NumPieces(); 
    //int NumPieces(const string &name_of_player); 
    //int NumPieces(const string &name_of_player, const string &type_of_gamepiece);
    int Wizards (const string &name_of_player, const string &type_of_gamepiece);
    void add_piece(const string &name_of_player, const string &type_of_gamepiece); 
    ///void remove_piece(const string &name_of_player, const string &type_of_gamepiece); 
};