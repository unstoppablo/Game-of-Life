#include <iostream>
#include "Grid.h"
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>



using namespace std;


int main(int argc, char **argv) {


  char choice;
  char boundary;
  string filename;

  int new_row;
  int new_column;
  float new_popDensity;

  cout << "You can allow program to run continuously or pause between generations." << endl;
  cout << "To allow it to simply run, you will select 'Enter', otherwise 'Pause'. See below. " << endl;
  cout << "'Pause' , 'Enter' ('p'/'e'): ";
  cin >> choice;

  cout << "What boundary mode would you like to play in? Classic, Doughnut, or Mirror('c'/'d'/'m') : ";
  cin >> boundary;



  
  cout << "Enter # of rows: ";
  cin >> new_row;
  cout << "Enter # of columns: ";
  cin >> new_column;
  cout << "Enter population density: ";
  cin >> new_popDensity;
  




//Classic Mode
  if (boundary == 'c') {

    if (choice == 'p') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighbor();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (choice == 'e') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        cout << "Press 'Enter' to continue"; 
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighbor();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      // while (!myGrid->genEmpty || myGrid->isStable);
      delete myGrid;
    }
  }


//Doughnut Mode
  else if (boundary == 'd') {
    if (choice == 'p') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighborsDonut();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (choice == 'e') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        cout << "Press 'Enter' to continue"; //FIX for generation 0
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighborsDonut();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      // while (!myGrid->genEmpty || myGrid->isStable);
      delete myGrid;
    }
  }


//Mirror Mode
  else if (boundary == 'm') {
    if (choice == 'p') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighborsMirror();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (choice == 'e') {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      //sleep choice
      int i = 0;
      do {
        cout << "Press 'Enter' to continue";
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighborsMirror();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      // while (!myGrid->genEmpty || myGrid->isStable);
      delete myGrid;
    }
  }





}
