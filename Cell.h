#ifndef CELL_H
#define CELL_H

#include <iostream>

using namespace std;

class Cell {

public:

  Cell();
  ~Cell();

  float generationsArray[3] = {-78.7, -78.7, -78.7};  //FIX THIS

  void setStatus(char new_status);
  char getStatus();

  void setwillLive(bool new_willLive);
  bool getwillLive();

  void setAvgNeighbors(float new_AvgNeighbors);
  float getAvgNeighbors();

  void setGenerations(float avgNeighbor);

private:
  // float* generations; //pointer that represents generation array
  char status;  //pointer that represents the cell value (X or -)
  bool willLive; //boolean determing whether the cell will live in the subsequent generation
  float averageNeighbors;





};
#endif
