#include "functions.h"                              //include needed libraries and files
#include "player.h"
#include <cstdlib>

void readFromFile(Player & you){                    //set read from file function
    string stringValue;                             //set string value variable
    int intValue;                                   //set integer value variable
    ifstream in;                                    //set infstream
    string p;                                       //set string value variable
    in.open("ship_placement1_good.csv");            //open file
    if(!in.is_open()){                              //if the file is not open
        cout << "Error file not open" << endl;      //display error
    }else{                                          //else
        while(!in.eof()){                           //while not at the end of the file
            getline(in, stringValue,',');           //set getline to store value into string value until a , is reached.
            you.shipName.push_back(stringValue);    //set string value into the back of shipName vector in you class.
            getline(in, stringValue, ',');          //set getline to store value into string value until a , is reached
            you.horizontalPlacement.push_back(convertFromLetterToNumber(stringValue[0]));//set horizontal placement in you class to equal to the converted string value of index 0
            you.verticalPlacement.push_back(convertFromStringToNumber(stringValue[1]));//set vertical placement in you class to equal to the converted string value of index 1
            getline(in, stringValue);               // use getline to store information into string value
            you.shipPlacementType.push_back(stringValue[0]);//store shiplacement as the string value's index 0
        }
    }
}

void setPlayersBoard(Player & player) {             //set set players board function as void
    player.blankField.setMatrix(player.blankField, 10, 10);//set players matrix as 10 wide and 10 long
    player.field.setMatrix(player.field, 10, 10);   //set player's blank matrix as 10 wide and 10 long
    for(int x = 0; x < 9; x++){
        for(int j = 0; j < 9; j++){
            player.field.matrix[x][j] = ' ';
            player.blankField.matrix[x][j] = ' ';
        }
    }
    for (int x = 0; x < player.shipName.size(); x++) {//set a for loop to incriment to te size of ship name vector within you
        if(player.shipName[x] == "Carrier"){        //if the given index equals carrier
            addPlayerShip(player, 5, x);            //call add player ship with 5 spaces and the given index
        }
        if(player.shipName[x] == "Battleship"){     //if given ship index equals battleship
            addPlayerShip(player, 4, x);            //call add player ship with 4 spaces and the given index
        }
        if(player.shipName[x] == "Cruiser"){        //if given ship index equals cruiser
            addPlayerShip(player, 3, x);            //call add player ship with 3 spaces and the given index
        }
        if(player.shipName[x] == "Submarine"){      //if given ship index equals submarine
            addPlayerShip(player, 3, x);            //call add player ship with 3 spaces and the given index
        }
        if(player.shipName[x] == "Destroyer"){      //if given ship index equals destroyer
            addPlayerShip(player, 2, x);            //call add player sip with 2 spaces and the given index
        }
    }
    cout << "Generation completed" << endl;          //generation complete
    breaker();
}

void addPlayerShip(Player &player, int numberOfSpaces, int index){//define add player ship function
    if (player.shipPlacementType[index] == 'H') {                 //if  player's ship index is equal to H
        while(!checkForCollision(player.verticalPlacement[index], player.horizontalPlacement[index], numberOfSpaces, player.field, player.shipPlacementType[index])){//while there is a collisions
            player.verticalPlacement[index] = rand()%10;          //set vertical placement at index to a random number from 0 to 9
            player.horizontalPlacement[index] = rand()%10;        //set horizontal placement at index to a random number from 0 to 9
            cout << "Error collision detected, randomizing location and checking for another collision" << endl;//declare collision and reposition
        }
            if (player.horizontalPlacement[index] <= (9-numberOfSpaces)) {//if players indexed ship will reach the bounds of the board, then flip the direction of the ship
                for (int j = player.horizontalPlacement[index]; j < (player.horizontalPlacement[index] + numberOfSpaces); j++) {//loop to incriment to the size of the ship
                    player.field.matrix[player.verticalPlacement[index]][j] = 'H';                                              //place an H at every location
                }
            } else {                                                                                                            //else
                for (int j = player.horizontalPlacement[index]; j > (player.horizontalPlacement[index] - numberOfSpaces); j--) {//loop to decriment tot he size of the ship
                    player.field.matrix[player.verticalPlacement[index]][j] = 'H';                                              //place an H at every location
                }
            }
            cout << player.shipName[index] << " added" << endl;                                                                 //display successful ship addition
            player.field.displayMatrix(player.field.matrix);                                                                    //display player's field

    }
    if (player.shipPlacementType[index] == 'V') {                                                                               //if ship's placement's index is a V
        while(!checkForCollision(player.verticalPlacement[index], player.horizontalPlacement[index], numberOfSpaces, player.field, player.shipPlacementType[index])){//check for collisions at the given points
            player.verticalPlacement[index] = rand()%10;        //set vertical placement at index to a random number from 0 to 9
            player.horizontalPlacement[index] = rand()%10;      //set vertical placement at index to a random number from 0 to 9
            cout << "Error collision detected, randomizing location and checking for another collision" << endl;//prompt user of collision and reposition
        }
            if (player.verticalPlacement[index] <= (9 - numberOfSpaces)) {//if players indexed ship will reach the bounds of the board, then flip the direction of the ship
                for (int j = (player.verticalPlacement[index] - 1); j < (player.verticalPlacement[index] + (numberOfSpaces-1)); j++) {//set a for loop to incriment to the size of the ship
                    player.field.matrix[j + 1][player.horizontalPlacement[index]] = 'V';                                              //place a V at every location
                }
            } else {                                                                                                                  //else
                for (int j = (player.verticalPlacement[index] - 1); j > (player.verticalPlacement[index] - (numberOfSpaces+1)); j--) {//set a for loop to decriment to the size of the ship
                    player.field.matrix[j + 1][player.horizontalPlacement[index]] = 'V';                                              //place a V at every location
                }
            }
            cout << player.shipName[index] <<  " added" << endl;                                                                      //display ship addition
            player.field.displayMatrix(player.field.matrix);                                                                          //display player's field
        }
    player.isSunk.push_back('N');
    breaker();
    cout << endl;
}

int convertFromLetterToNumber(char letter){             //set set convert lett to number function
    if(letter == 'A'|| letter == 'a'){                  //if letter is an A or a
        return 0;                                       //return 0
    }
    if(letter == 'B'|| letter == 'b'){                  //if letter is a B or b
        return 1;                                       //return 1
    }
    if(letter == 'C'|| letter == 'c'){                  //if letter is a C or c
        return 2;                                       //return 2
    }
    if(letter == 'D'|| letter == 'd'){                  //if letter is a D or d
        return 3;                                       //return 3
    }
    if(letter == 'E'|| letter == 'e'){                  //if letter is an E or e
        return 4;                                       //return 4
    }
    if(letter == 'F'|| letter == 'f'){                  //if letter is a F or f
        return 5;                                       //return 5
    }
    if(letter == 'G'|| letter == 'g'){                  //if letter is a G or g
        return 6;                                       //return 6
    }
    if(letter == 'H'|| letter == 'h'){                  //if letter is a H or h
        return 7;                                       //return 7
    }
    if(letter == 'I'|| letter == 'i'){                  //if letter is an I or i
        return 8;                                       //return 8
    }
    if(letter == 'J'|| letter == 'j'){                  //if letter is a J or j
        return 9;                                       //return 9
    }
    else{                                               //else
        int r = rand()%10;                              //set r to equal random number from 0 to 9
        return r;                                       //return r
    }
}
int convertFromStringToNumber(char number){             //set a convert from string to number function of type int
    if(number == '0'){                                  //if the number is equal to 0
        return 0;                                       //return 0
    }
    if(number == '1'){                                  //if the number is equal to 1
        return 1;                                       //return 1
    }
    if(number == '2'){                                  //if the number is equal to 2
        return 2;                                       //return 2
    }
    if(number == '3'){                                  //if the number is equal to 3
        return 3;                                       //return 3
    }
    if(number == '4'){                                  //if the number is equal to 4
        return 4;                                       //return 4
    }
    if(number == '5'){                                  //if the number is equal to 5
        return 5;                                       //return 5
    }
    if(number == '6'){                                  //if the number is equal to 6
        return 6;                                       //return 6
    }
    if(number == '7'){                                  //if the number is equal to 7
        return 7;                                       //return 7
    }
    if(number == '8'){                                  //if the number is equal to 8
        return 8;                                       //return 8
    }
    if(number == '9'){                                  //if the number is equal to 9
        return 9;                                       //return 9
    }
}
char convertIntegerToCharacter(int x){                  //set a convert from integer to character function
    if(x == 0){                                         //if number is 0
        return 'A';                                     //return A
    }
    if(x == 1){                                         //if number is 1
        return 'B';                                     //return B
    }
    if(x == 2){                                         //if number is 2
        return 'C';                                     //return C
    }
    if(x == 3){                                         //if number is 3
        return 'D';                                     //return D
    }
    if(x == 4){                                         //if number is 4
        return 'E';                                     //return E
    }
    if(x == 5){                                         //if number is 5
        return 'F';                                     //return F
    }
    if(x == 6){                                         //if number is 6
        return 'G';                                     //return G
    }
    if(x == 7){                                         //if number is 7
        return 'H';                                     //return H
    }
    if(x == 8){                                         //if number is 8
        return 'I';                                     //return I
    }
    if(x == 9){                                         //if number is 9
        return 'J';                                     //return J
    }
}
bool checkForCollision(int & verticalPosition, int & horizontalPosition, int numberOfSpaces, Grid & player, char shipPositionType){//define check for collision function
    if (shipPositionType == 'H') {                      //if ship's position type is horizontal
        if (horizontalPosition <= (9-numberOfSpaces)) { //if the ship reaches the bounds of the field, then flip the position of the ship
            for (int j = horizontalPosition; j < (horizontalPosition + numberOfSpaces); j++) {//set a for loop to incriment to the size of the ship
                if(player.matrix[verticalPosition][j] == 'H'|| player.matrix[verticalPosition][j] == 'V'){//if the position is marked with a V or H
                    return false;                       //return false
                }
            }
        } else {                                        //else
            for (int j = horizontalPosition; j > (horizontalPosition - numberOfSpaces); j--) {//set a for loop to decriment to the size of the ship
                if(player.matrix[verticalPosition][j] == 'H' || player.matrix[verticalPosition][j] == 'V' ){//if the position is marked with a V or H
                    return false;                       //return false
                }
            }
        }
    }
    if (shipPositionType == 'V') {                      //if ship's position type is vertical
        if (verticalPosition <= (9 - numberOfSpaces)) { //if ship raches the bounds of the field then flip the position of the ship
            for (int j = (verticalPosition - 1); j < (verticalPosition + (numberOfSpaces-1)); j++) {//set a for loop to incriment to the size of the ship
                if(player.matrix[j + 1][horizontalPosition] == 'V' || player.matrix[j + 1][horizontalPosition] == 'H' ){//if the positon is marked with a V or H
                    return false;                       //return false
                }
            }
        } else {                                        //else
            for (int j = (verticalPosition - 1); j > (verticalPosition - (numberOfSpaces+1)); j--) {//set a for loop to decriment to the size of the ship
                if(player.matrix[j + 1][horizontalPosition] == 'V' || player.matrix[j + 1][horizontalPosition] == 'H' ){//if the positon is marked with a V or H
                    return false;                       //return false
                }
            }
        }
    }
    return true;                                        //return true
}
void placeOpponentsField(Player & player){              //declare place oppoents field function as void
    cout << "Generating opponents field" << endl;       //prompt user of generation of opponents field
    player.field.setMatrix(player.field, 10, 10);       //set opponents field to be 10 wide and 10 long
    player.blankField.setMatrix(player.blankField, 10, 10);//set opponents blank field to be 10 wide and 10 long
    for(int x = 0; x < 9; x++){
        for(int j = 0; j < 9; j++){
            player.field.matrix[x][j] = ' ';
            player.blankField.matrix[x][j] = ' ';
        }
    }
    player.shipName.push_back("Carrier");               //set opponents first ship to be a carrier
    player.shipName.push_back("Battleship");            //set opponents second ship to be a battleship
    player.shipName.push_back("Cruiser");               //set opponents thirds ship to be a cruiser
    player.shipName.push_back("Submarine");             //set opponents fourth ship to be a submarine
    player.shipName.push_back("Destroyer");             //set opponents fith ship to be a destroyer
    for(int x = 0; x < 4; x++ ){                        //set a for loop to incriment to the size of 5
        int r = rand()%2;                               //set a random number from 0 to 1 to r
        player.isSunk.push_back('N');                         //set is sunk vector to false at all positions
        if(r == 0){                                     //if r equals 0
                player.shipPlacementType.push_back('V');//make ship placement type at index to equal a V
            }
        if(r == 1){                                     //if r equals 1
                player.shipPlacementType.push_back('H');//make ship placement type at index to equal a H
            }
            r = rand()%10;                              //set r to equal a random number from 0 to 9
                player.verticalPlacement.push_back(r);  //place r to the back of vertical placement vector
            r = rand()%10;                              //set r to equal a random number from 0 to 9
                player.horizontalPlacement.push_back(r);//place r to the back of horizontal placement vector
        if(x == 0){                                     //if x equals 0
            placeOpponentsShip(player, 5, x);           //place opponents ship with 5 spaces and index x
        }
        if(x == 1){                                     //if x equals 1
            placeOpponentsShip(player, 4, x);           //place opponents ship with 4 spaces and index x
        }
        if(x == 2){                                     //if x equals 2
            placeOpponentsShip(player, 3, x);           //place opponents ship with 3 spaces and index x
        }
        if(x == 3){                                     //if x equals 3
            placeOpponentsShip(player, 3, x);           //place opponents ship with 3 spaces and index x
        }
        if(x == 4){                                     //if x equals 4
            placeOpponentsShip(player, 2, x);           //place opponents ship with 2 spaces and index x
        }
    }
    //player.field.displayMatrix(player.field.matrix);
    cout << "Generation complete" << endl;              //prompt successful generation
}
void placeOpponentsShip(Player & player, int numberOfSpaces, int index){//define place opponents ship function
    if (player.shipPlacementType[index] == 'H') {                       //if ship placement type at index is an H
        while(!checkForCollision(player.verticalPlacement[index], player.horizontalPlacement[index], numberOfSpaces, player.field, player.shipPlacementType[index])){//while collision exists
            player.verticalPlacement[index] = rand()%10;                //set random number from 0 to 9 to equal vertical placement at index
            player.horizontalPlacement[index] = rand()%10;              //set random number from 0 to 9 to equal horizontal placement at index
            cout << "Error collision detected, randomizing location and checking for another collision" << endl;//prompt a collision is detected and relocation has occured
        }
        if (player.horizontalPlacement[index] <= (9-numberOfSpaces)) {  //if ship breaches bounds of matrix
            for (int j = player.horizontalPlacement[index]; j < (player.horizontalPlacement[index] + numberOfSpaces); j++) {//set a for loop to incriment to the size of the given ship
                player.field.matrix[player.verticalPlacement[index]][j] = 'H';//set the given position to H
            }
        } else {
            for (int j = player.horizontalPlacement[index]; j > (player.horizontalPlacement[index] - numberOfSpaces); j--) {//set a for loop to decriment to the size of the given ship
                player.field.matrix[player.verticalPlacement[index]][j] = 'H';//set the given position to H
            }
        }
    }
    if (player.shipPlacementType[index] == 'V') {                       //if ship placement type at index is a V
        while(!checkForCollision(player.verticalPlacement[index], player.horizontalPlacement[index], numberOfSpaces, player.field, player.shipPlacementType[index])){//while collision exists
            player.verticalPlacement[index] = rand()%10;                //set random number from 0 to 9 to equal vertical placement at index
            player.horizontalPlacement[index] = rand()%10;              //set random number from 0 to 9 to equal horizontal placement at index
            cout << "Error collision detected, randomizing location and checking for another collision" << endl;//prompt a collision is detected and relocation has occured
        }
        if (player.verticalPlacement[index] <= (9 - numberOfSpaces)) {//if ship breaches bounds of matrix
            for (int j = (player.verticalPlacement[index] - 1); j < (player.verticalPlacement[index] + (numberOfSpaces-1)); j++) {//set a for loop to incriment to the size of the given ship
                player.field.matrix[j + 1][player.horizontalPlacement[index]] = 'V';//set the given position to V
            }
        } else {
            for (int j = (player.verticalPlacement[index] - 1); j > (player.verticalPlacement[index] - (numberOfSpaces+1)); j--) {//set a for loop to decriment to the size of the given ship
                player.field.matrix[j + 1][player.horizontalPlacement[index]] = 'V';//set the given position to //set the given position to H
            }
        }
    }
}

int findMenuInput(){                                    //declare find menu input function as int
    breaker();
    int menuInput;                                      //declare menu input as an int value
    cout << "Alright, ready for the game???" << endl;   //prompt user of choices
    cout << "1.Hell ya!!" << endl;
    cout << "2.Nawh man..." << endl << endl;
    breaker();
    cin >> menuInput;                                   //take input and set to menu input
    return menuInput;                                   //return menu input
}

void playerGuesses(Player & comp, Player & you, bool & game){//declare player guesses function as type void
    int horizontalGuess, verticalGuess;                      //declare horizontal and vertical guess as integer type
    char convert;                                            //declare convert as a char type
    cout << "Hello player, what would you like to guess???" << endl;//prompt user of choice
    cout << "Please enter horizontal guess first.(from A to J)" << endl;
    cin >> convert;                                          //take input and set to convert
    verticalGuess = convertFromLetterToNumber(convert);      //set vertical guess to equal the conversion of convert to a number
    cout << "Please enter vertical guess." << endl;          //prompt user of second choice
    cin >> horizontalGuess;                                  //take input and set to horizontal guess
    if(comp.field.matrix[horizontalGuess][verticalGuess] == 'V'|| comp.field.matrix[horizontalGuess][verticalGuess] == 'H'){//if the given positon is a H or a V
        comp.field.matrix[horizontalGuess][verticalGuess] = 'X';//mark as an X on opponents field
        comp.blankField.matrix[horizontalGuess][verticalGuess] = 'X';//mark as n X on opponents blank field
        cout << "Hit!" << endl;
        you.opponentsHits++;                                //incriment the number of hits you have
        if(you.opponentsHits == 16) {                       //if check number of hits equals max number of hits
            game = false;                                   //game is set to false
            cout << "All ships destroyed...better luck next time" << endl;//display game over
        }
    }else {                                                  //else
        comp.field.matrix[horizontalGuess][verticalGuess] = 'O';//mark the given position as an O
        comp.blankField.matrix[horizontalGuess][verticalGuess] = 'O';//mark te given position as an O
        cout << "We are wasting money on these misses!" << endl;
    }
    cout << endl;
    breaker();
}

void opponentGuesses(Player & you, Player & ai, bool & game){//define opponent guess function as void
    cout << "The opponent fired!" << endl;
    int horizontalGuess, verticalGuess;                      //declare horizontal guess an vertical guess as an int
    horizontalGuess = rand()%10;                             //set both as a random number from 0 to 9
    verticalGuess = rand()%10;
    if(you.field.matrix[horizontalGuess][verticalGuess] == 'V'|| you.field.matrix[horizontalGuess][verticalGuess] == 'H'){//if either position is equal to a H or a V
        you.blankField.matrix[horizontalGuess][verticalGuess] = 'X';//mark the position as an X on the blank field
        you.field.matrix[horizontalGuess][verticalGuess] = 'X';//mark the position as an X on the field
        cout << "That's a hit for the computer!" << endl;
        ai.opponentsHits++;                                  //incriment ai's number of hits.
        if(you.opponentsHits == 16){                         //if opponents numbe rof hits is equal to max number of hits
            game = false;                                    //set game to equal false
            cout << "All ships destroyed...better luck next time" << endl;//prompt user of loss
        }
    }else {                                                   //else
        you.field.matrix[horizontalGuess][verticalGuess] = 'O';//set the given position on your field to equal an O
        you.blankField.matrix[horizontalGuess][verticalGuess] = 'O';//set the given position on your blank field to equal an O
        you.field.displayMatrix(you.field.matrix);           //display your field
        cout << "The computer missed!" << endl;
    }
    cout << endl;
}

bool checkSunkBoat(Player & player, int numberOfSpaces, int horizontalPosition, int verticalPosition, char shipPositionType){//declare check sunk boat as bool
    int numberOfHitsOnBoat = 0;                                         //set number of hits on boat to equal 0
    if (shipPositionType == 'H') {                                      //if ship position type is a H
        if (horizontalPosition <= (9-numberOfSpaces)) {                 //if the ship will reach bounds
            for (int j = horizontalPosition; j < (horizontalPosition + numberOfSpaces); j++) {//set a for loop to incriment to the size of the ship
                if(player.field.matrix[verticalPosition][j] == 'X'){    //if the given position is equal X
                    numberOfHitsOnBoat++;                               //incriment the number of hits on the Boat
                    if(numberOfHitsOnBoat == numberOfSpaces){           //if the number of hits on boat are equal to the number of spaces
                        return true;                                    //return true
                    }
                }
            }
        } else {//else
            for (int j = horizontalPosition; j > (horizontalPosition - numberOfSpaces); j--) {//set a for loop to incriment to the size of the ship
                if(player.field.matrix[verticalPosition][j] == 'X'){    //if the given position is equal to X
                    numberOfHitsOnBoat++;                               //incriment the number of hits on the boat
                    if(numberOfHitsOnBoat == numberOfSpaces){           //if the number of hits on the boat is equal to the number of spaces
                        return true;                                    //return true
                    }
                }
            }
        }
    }
    if (shipPositionType == 'V') {                                      //if ship position type ie equal to V
        if (verticalPosition <= (9 - numberOfSpaces)) {                 //if boat will reach the bounds of the matrix
            for (int j = (verticalPosition - 1); j < (verticalPosition + (numberOfSpaces-1)); j++) {//set a for loop to incriment to the the size of the boat
                if(player.field.matrix[j + 1][horizontalPosition] == 'X' ){//if the given position is equal to an X
                    numberOfHitsOnBoat++;                               //incriment number of hits on boat
                    if(numberOfHitsOnBoat == numberOfSpaces){           //if the number of hits on the boat equals the number of Spaces
                        return true;                                    //return true
                    }
                }
            }
        } else {                                                        //else
            for (int j = (verticalPosition - 1); j > (verticalPosition - (numberOfSpaces+1)); j--) {//set a for loop to incriment to the size of the boat
                if(player.field.matrix[j + 1][horizontalPosition] == 'X'){//if the given position is equal to an X
                    numberOfHitsOnBoat++;                                 //incriment number of hits on boat
                    if(numberOfHitsOnBoat == numberOfSpaces) {            //if numberOf Hits on boat are equal to the number of spaces

                        return true;                                      //return true
                    }
                }
            }
        }
    }
    return false;                                                         //return false
}

bool checkForBoatSunkOnComputer(Player & p){                            //check for boats sunk on computer function as bool
    for(int x = 0; x < p.shipName.size(); x++) {                        //set a for loop to incriment to the size of ship name vector
        if ((p.isSunk[x]) == 'N'){                                             //if the given index for is sunk is not true
            if (p.shipName[x] == "Carrier") {                           //if the ship name is a carrier
                if (checkSunkBoat(p, 5, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//if  check for sunk boat is equal to true
                    cout << "You sunk my carrier man...." << endl;      //display a sunk carrier msg
                    p.isSunk[x] = 'Y';                                 //set is sunk at index to equal true
                    return true;
                }
            }
            if (p.shipName[x] == "Battleship") {                        //if the given ship name at index is battlehsip
                if (checkSunkBoat(p, 4, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//if check for boat sunk is equal to true
                    cout << "You sunk my Battleship!" << endl;          //display a sunk battleship
                    p.isSunk[x] = 'Y';                                 //set is sunk at index to equal true
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Cruiser") {                           //if the given ship name at index is cruiser
                if (checkSunkBoat(p, 3, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//if check for boat sunk is equal to true
                    cout << "You sunk my cruiser man...." << endl;      //display a sunk cruiser
                    p.isSunk[x] = 'Y';                                 //set is sunk at index to equal true
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Submarine") {                         //if the given ship name at index is submarine
                if (checkSunkBoat(p, 5, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//if check for boat sunk is equal to true
                    cout << "You sunk my Submarine man...." << endl;    //display a sunk submarine message
                    p.isSunk[x] = 'Y';                                 //set is sunk at index to equal true
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Destroyer") {                         //if the given ship name at index is destroyer
                if (checkSunkBoat(p, 2, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//if check for boat sunk ie qual to true
                    cout << "You sunk my destroyer man...." << endl;    //display a sunk destroyer message
                    p.isSunk[x] = 'Y';
                    return true;                                        //return true
                }
            }
        }
    }
}

bool checkForBoatSunkOnPlayer(Player & p){                              //declare check for boat sunk on player function and set to true
    for(int x = 0; x < p.shipName.size(); x++) {                        //set a for loop to incriment to the size of shipName's size
        if (!p.isSunk[x]) {                                             //if the given index is not sunk
            if (p.shipName[x] == "Carrier") {                           //if the ship name is carrier
                if (checkSunkBoat(p, 5, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//call check sunk boat function with size 5
                    cout << "It got my carrier. Can't afford to lose any more..." << endl;//display message for sunk carrier
                    return true;
                }
            }
            if (p.shipName[x] == "Battleship") {                        //if the ship name at the given index is battelsehip
                if (checkSunkBoat(p, 4, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//call check sunk boat function with size 4
                    cout << "It sunk my dang battleship?!?!" << endl;   //display a sunk battleship message
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Cruiser") {                           //if the ship name at the given index is cruiser
                if (checkSunkBoat(p, 3, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//call check sunk boat function with size 3
                    cout << "Cruiser down...." << endl;                 //display a sunk cruiser message
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Submarine") {                         //if the ship name at the given index is submarine
                if (checkSunkBoat(p, 3, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//call check sunk boat function with size 4
                    cout << "You sunk something that was already underwater...huh..." << endl;//display a sunk submarine message
                    return true;                                        //return true
                }
            }
            if (p.shipName[x] == "Destroyer") {                         //if the ship name at the given index is destroyer
                if (checkSunkBoat(p, 2, p.horizontalPlacement[x], p.verticalPlacement[x], p.shipPlacementType[x])) {//call check sunk boat function with size 2
                    cout << "The hardest ship is down, I repeat the destroyer is down...." << endl;//display a sunk destroyer message
                    return true;                                        //return true
                }
            }
        }
    }
}
int findAnotherInput(){                     //declare find another input as int
    breaker();
    int input;                              //declare input as int
    cout << "Would you like to.... \n1. Check your own board?" << endl;//prompt user of choices
    cout << "2. or check the hits on the opponent? or....." << endl;
    cout << "3. Screw it, I'm taking my shot!" << endl;
    cout << endl;
    breaker();
    cin >> input;                           //take in input and set to input variable
    return input;                           //return input variable
}

void breaker(){
    for(int x = 0; x < 120; x++) {
        cout << "=";
    }
    cout << endl;
    for(int x = 0; x < 120; x++) {
        cout << "=";
    }
    cout << endl;
}