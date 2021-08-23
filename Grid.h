#ifndef GRID_H
#define GRID_H

#include <iostream>
#include "Cell.h"
using namespace std;

class Grid{

public:
  Grid(); //Constructor
  Grid(int row, int column);
  Grid(int new_row, int new_column, float new_popDensity);
  ~Grid(); //Destructor

  bool genEmpty;
  bool isStable;

  //core functions
  void populateGrid();
  void printGrid();
  void calculateNeighbor();
  bool threshhold(Cell myObject);
  void processFile(string input_file);
  void nextGeneration();
  void calculateNeighborsDonut();
  void calculateNeighborsMirror();

  int generateNumbers(int maxNum);


private:
  Cell** myGrid;
  int row;
  int column;
  float popDensity;
  int genCount;
};

#endif
