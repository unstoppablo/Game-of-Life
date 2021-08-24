#include <iostream>
#include "Grid.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <sstream>



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
  cout << "'Pause' , 'Enter' ('P'/'E'): ";
  cin >> choice;

  while (!(choice == 'P' or choice == 'E' or choice == 'e' or choice == 'p'))
  {
    cout << "Select a valid choice: 'Pause' , 'Enter' ('P'/'E'): ";
    cin >> choice;
  }
  

  cout << "What boundary mode would you like to play in? Classic, Doughnut, or Mirror('c'/'d'/'m') : ";
  cin >> boundary;

  
  while (!(boundary == 'c' or boundary == 'd' or boundary == 'm'))
  {
    cout << "Select a valid mode: Classic, Doughnut, or Mirror('c'/'d'/'m') : ";
    cin >> boundary;
  }

  cout << "Enter # of rows: ";
  cin >> new_row;
  cout << "Enter # of columns: ";
  cin >> new_column;
  cout << "Enter population density: ";
  cin >> new_popDensity;


// Classic Mode
  if (toupper(boundary) == 'C') 
  {

    if (toupper(choice) == 'P') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighbor();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (toupper(choice) == 'E') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        cout << "Press 'Enter' to continue"; 
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighbor();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }
  }


// Doughnut Mode
  else if (toupper(boundary) == 'D') 
  {
    if (toupper(choice) == 'P') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighborsDonut();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (toupper(choice) == 'E') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        cout << "Press 'Enter' to continue"; 
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighborsDonut();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }
  }


// Mirror Mode
  else if (toupper(boundary) == 'M') 
  {
    if (toupper(choice) == 'P') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        sleep(2);
        myGrid->printGrid();
        myGrid->calculateNeighborsMirror();
        myGrid->nextGeneration();
        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }

    else if (toupper(choice) == 'E') 
    {
      Grid *myGrid = new Grid(new_row, new_column, new_popDensity);
      myGrid->populateGrid();
      // sleep choice
      int i = 0;
      do 
      {
        cout << "Press 'Enter' to continue";
        cin.get();
        myGrid->printGrid();
        myGrid->calculateNeighborsMirror();
        myGrid->nextGeneration();

        ++i;
      }
      while (!myGrid->genEmpty);
      delete myGrid;
    }
  }
}
