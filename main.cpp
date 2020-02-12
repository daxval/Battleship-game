#include <iostream>
#include "functions.h"
#include "grid.h"
#include "player.h"
#include <vector>
using namespace std;

int main() {
    bool game = true;                                                               //declare menus as true
    bool menu = true;
    Player you, ai;                                                                 //declare both you and the opponent's classes
    while(menu == true) {                                                           //while menu is true
        switch (findMenuInput()) {                                                  //find the menu input for switch menu
            case 1:                                                                 //if case 1
                readFromFile(you);                                                  //read player's information
                setPlayersBoard(you);                                               //set player's field
                placeOpponentsField(ai);                                            //set opponents field
                while(game = true){                                                 //while the game is set to true
                    switch(findAnotherInput()) {                                    //set another switch statement for the turn based section
                        case 1:                                                     //if case 1
                            you.field.displayMatrix(you.field.matrix);              //display player's field
                            cout << endl;
                            break;                                                  //break from case
                        case 2:                                                     //if case 2
                            ai.blankField.displayMatrix(ai.blankField.matrix);      //display the blank field of the ai
                            cout << endl;
                            break;                                                  //break from case
                        case 3:                                                     //case 3
                        playerGuesses(ai, you, game);                               //call player's guess
                        checkForBoatSunkOnComputer(ai);                             //check for sunk boats on computer
                        opponentGuesses(you, ai, game);                             //call ai's guess on player's board
                        checkForBoatSunkOnPlayer(you);                              //check for boats sunk on player
                        break;                                                      //break from case
                        default:
                            cout << "Hold on bro, lets try this one again..." << endl;//set default statement for user
                            break;                                                  //break from case
                    }
                }
                break;                                                              //break from case
            case 2:                                                                 //if case 2
                menu = false;                                                       //set menu to equal false
                break;                                                              //break from case
            default:                                                                //set default statemtn
                cout << "Opsie, try again?" << endl;                                //prompt user of error
                break;                                                              //break from default case
        }
    }
    return 0;                                                                       //return zero
}