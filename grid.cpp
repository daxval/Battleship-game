#include "grid.h"
#include "functions.h"

void Grid::displayMatrix(vector<vector<char>> matrix) {
    cout << "[" << '#' << "] ";
    for(int y = 0; y < 10; y++){
        cout << "[" << convertIntegerToCharacter(y) <<  "] ";
    }
    cout << endl;
    for(int x = 0; x < matrix.size(); x++){                        //set a for loop to increment to the size of the given matrix's size.
        cout << "[" << x << "] ";
        for(int j = 0; j < matrix[x].size(); j++){                 //set a for loop to increment to the size of the given matrix's size.
            cout << "[" << matrix[x][j] << "] ";                   //display the brackets around the matrix's entries to display a grid
        }
        cout << endl;                                              //end line
    }
    cout << endl;                                                  //end line.
}
void Grid::setMatrix(Grid & G, int length, int width){
    vector <vector<char>> matrix(width, vector<char>(length, 0));    //set a vector of defined length width and length filled with zeros.
    G.matrix = matrix;                                             //set a matrix within a class to equal the matrix defined above.
}