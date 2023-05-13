#include "GameState.hpp"
//#include <algorithm> 
//#include <iterator> 

//using std::iterator; 

int GameState::Wizards (const string &name_of_player, const string &type_of_gamepiece) {
  int count = 0; 
  for (int i = 0; i < vect.size(); i++) {
    if (vect.at(i).first == name_of_player) {
      if (vect.at(i).second == "Wizard") {
        count++; 
      }
    }
  }
  return count; 
}

void GameState::add_piece (const string &name_of_player, const string &type_of_gamepiece) {
  vect.push_back(make_pair(name_of_player, type_of_gamepiece)); 
}

/*void GameState::remove_piece (const string &name_of_player, const string &type_of_gamepiece) {
    vector<int>::iterator it = std::find(vect.begin(), vect.end(), make_pair(name_of_player, type_of_gamepiece));
    if (it != vect.end()) {
      vect.erase(make_pair(name_of_player, type_of_gamepiece)); 
  }
}

int GameState::NumPieces() {
  
}

int GameState::NumPieces(const string &name_of_player) {
  
} 

int GameState::NumPieces(const string &name_of_player, const string &type_of_gamepiece) {
  
}*/