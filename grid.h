#include <iostream>     //include needed libraries
#include <array>
#include <vector>

using namespace std;

#ifndef OBJHW3_GRID_H
#define OBJHW3_GRID_H

class Grid;

class Grid{                                         //declare class Grid
private:

    int length, width;                              //set private variables for length and width

public:

    void setMatrix(Grid & G,int length, int width);//declare set function for matrix

    vector <vector<char>> matrix;                   //declare matrix as a member of Grid

    void displayMatrix(vector<vector<char>> matrix);//declare display matrix member function

};
#endif