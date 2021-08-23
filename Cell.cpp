#include <iostream>
#include "Cell.h"
using namespace std;


//Constructor
Cell::Cell(){
  status = '-';
  willLive = true;
  averageNeighbors = 0;
}

//Destructor
Cell::~Cell(){
  // delete generations;
};

void Cell::setStatus(char new_status){
   status = new_status;
}

char Cell::getStatus(){
  return status;
}

void Cell::setwillLive(bool new_willLive) {
  willLive = new_willLive;
}

bool Cell::getwillLive(){
  return willLive;
}

void Cell::setAvgNeighbors(float new_AvgNeighbors){
  averageNeighbors = new_AvgNeighbors;
}

float Cell::getAvgNeighbors(){
  return averageNeighbors;
}


void Cell::setGenerations(float avgNeighbor) {
  generationsArray[2] = generationsArray[1];
  generationsArray[1] = generationsArray[0];
  generationsArray[0] = avgNeighbor;
}
