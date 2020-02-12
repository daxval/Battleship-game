#ifndef OBJHW5_FUNCTIONS_H                                  //included needed libraries
#define OBJHW5_FUNCTIONS_H
#include "grid.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include "player.h"


using namespace std;

void readFromFile(Player & you);                            //declare needed functions

int convertFromLetterToNumber(char letter);

int convertFromStringToNumber(char number);

void setPlayersBoard(Player & player);

char convertIntegerToCharacter(int x);

bool checkForCollision(int & verticalPosition, int & horizontalPosition, int numberOfSpaces, Grid & player, char shipPositionType);

void addPlayerShip(Player &player, int numberOfSpaces, int index);

void placeOpponentsField(Player & player);

void placeOpponentsShip(Player & O, int numberOfSpaces, int index);

int findMenuInput();

void playerGuesses(Player & comp, Player & you, bool & game);

bool checkForBoatSunkOnComputer(Player & p);

void opponentGuesses(Player & you, Player & ai, bool & game);

bool checkForBoatSunkOnPlayer(Player & p);

int findAnotherInput();

void breaker();

#endif