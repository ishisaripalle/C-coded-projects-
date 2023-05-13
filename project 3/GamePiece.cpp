#include <iostream> 
#include "GamePiece.hpp"

GamePiece::GamePiece (const string &name, const string &type, GameState *s) {
  name_of_player = name;
  type_of_gamepiece = type; 
  state = s; 
  (*state).add_piece(name_of_player, type_of_gamepiece); 
}

GamePiece::GamePiece (const GamePiece &p) {
  name_of_player = p.name_of_player;
  type_of_gamepiece = p. type_of_gamepiece; 
  state = p.state;
}

/*GamePiece::~GamePiece() {
  (*state).remove_piece(name_of_player, type_of_gamepiece); 
}*/

/*string GamePiece::GetPlayer() {
  return name_of_player; 
}

string GamePiece::GetType() {
  return type_of_gamepiece; 
}*/

int GamePiece::GetPower() {
  if (type_of_gamepiece == "Warrior") {
    return 5; 
  }
  if (type_of_gamepiece == "Scout") {
    return 1; 
  }
  if (type_of_gamepiece == "Wizard") {
    return (*state).GameState::Wizards(name_of_player, type_of_gamepiece);  
  }
  return 0; 
}

/*int GamePiece::GetSpeed() {
  int speed; 
  if (type_of_gamepiece == "Warrior") {
      int speed = 2; 
  }
  if (type_of_gamepiece == "Scout") {
      int speed = 8; 
  }
  if (type_of_gamepiece == "Wizard") {
      //speed equal 12 - total num of wizards on enemy team
  }
  return speed;
}*/

int main () {
  GameState state; 
  GamePiece p("Hufflepuff", "Wizard", &state);
  std::cout << p.GetPower() << std::endl; 
  GamePiece p2(p);
  std::cout << p2.GetPower() << std::endl;
  std::cout << p.GetPower() << std::endl;
  GamePiece p3("Hufflepuff", "Wizard", &state);
  std::cout << p3.GetPower() << std::endl;
}