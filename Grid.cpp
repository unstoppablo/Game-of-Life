#include <iostream>
#include "Grid.h"
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

Grid::Grid() {
  row = 4;
  column = 5;
  popDensity = .3;
  genCount = 0;
  genEmpty = false;
  isStable = false;

  //creating the grid
  myGrid = new Cell *[row];
    for (int i = 0; i < row; ++i) {
      myGrid[i] = new Cell[column];
    }

    for (int i = 0; i < row;  ++i) {
      for(int j = 0; j < column; ++j)
        {
            Cell myCell;
            myGrid[i][j] = myCell;
        }
    }
}

Grid::Grid(int row, int column) {
  row = row;
  column = column;
  genEmpty = false;

  //creating the grid
  myGrid = new Cell *[row];
    for (int i = 0; i < row; ++i) {
      myGrid[i] = new Cell[column];
    }

    for (int i = 0; i < row;  ++i) {
      for(int j = 0; j < column; ++j)
        {
            Cell myCell;
            myGrid[i][j] = myCell;
        }
    }
}

Grid::Grid(int new_row, int new_column, float new_popDensity){
  row = new_row;
  column = new_column;
  popDensity = new_popDensity;
  genCount = 0;
  genEmpty = false;
  isStable = false;

  //creating the grid
  myGrid = new Cell *[row];
    for (int i = 0; i < row; ++i) {
      myGrid[i] = new Cell[column];
    }

    for (int i = 0; i < row;  ++i) {
      for(int j = 0; j < column; ++j)
        {
            Cell myCell;
            myGrid[i][j] = myCell;
        }
    }
}

Grid::~Grid(){
  delete myGrid;
}

// void Grid::setGenEmpty(bool new_Empty) {
//   genEmpty = new_Empty;
// }
//
// bool Grid::getGenEmpty(){
//   return genEmpty;
// }


int Grid::generateNumbers(int maxNum) {
  return abs((rand() % maxNum - 1));
}


//Populate the 2D array given the population density
void Grid::populateGrid() {
  srand(time(NULL)); //initializes the random number generator
  int totalCount = row * column;
  int numCells = totalCount * popDensity;

  int count = 0;
  int r, c = 0;

  while (count < numCells) {
    r = generateNumbers(row);
    c = generateNumbers(column);

    if (myGrid[r][c].getStatus() == 'x') {
      r = (++r) % row;
      c = (++c) % column;

      if (myGrid[r][c].getStatus() == 'x') {
        continue;
      }
    }
    myGrid[r][c].setStatus('x');
    count++;
  }
}

void Grid::printGrid() {

  cout << "Generation: " << genCount << endl;
  genCount += 1;

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      cout << myGrid[i][j].getStatus();
    }
    cout << "\n";
  }
}


void Grid::calculateNeighbor() // VOID BECAUSE it will update the array dynamically
{
    /*
    1. calculates current neighbors
    2. adds current neighbors to generations array
    */
    int neighborCtr = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // checking 1 pos down
            if ((i + 1) < row)
            {
                if (myGrid[i + 1][j].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking 1 pos up
            if ((i - 1) >= 0)
            {
                if (myGrid[i - 1][j].getStatus() == 'x')
                    neighborCtr += 1;
            }
            // checking 1 pos right
            if ((j + 1) < column)
            {
                if (myGrid[i][j + 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking 1 pos left
            if ((j - 1) >= 0)
            {
                if (myGrid[i][j - 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking up right
            if ((i - 1) >= 0 && (j + 1) < column)
            {
                if (myGrid[i - 1][j + 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking up left
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                if (myGrid[i - 1][j - 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking down right
            if ((i + 1) < row && (j + 1) < column)
            {
                if (myGrid[i + 1][j + 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // checking down left
            if ((i + 1) < row && (j - 1) >= 0)
            {
                if (myGrid[i + 1][j - 1].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            // cout << "i index: " << i << endl;
            // cout << "j index: " << j << endl;
            // cout << "Num neighbors: " << neighborCtr << endl;
            // cout << "_______________________" << endl;
            myGrid[i][j].setAvgNeighbors(neighborCtr);
            // we send the average current neighbor value to array update function
            myGrid[i][j].setGenerations(myGrid[i][j].getAvgNeighbors());
            myGrid[i][j].setwillLive(threshhold(myGrid[i][j])); // we pass our cell object to determine if it will live
            // cout << myGrid[i][j].status;
            neighborCtr = 0;
        }
        // cout << "\n";
    }
    // now we loop and update
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            myGrid[i][j].setStatus((myGrid[i][j].getwillLive()) ? 'x' : '-');
        }
    }
}


bool Grid::threshhold(Cell myObject)
{
    float numerator = 0.0;
    float denominator = 0.0;
    float averageNeighbors = 0;
    for (int x = 0; x < 3; ++x)
    {
        if (myObject.generationsArray[x] >= 0)
        {
            numerator += myObject.generationsArray[x];
            denominator += 1;
        }
    }
    if (denominator != 0.0)
    {
        averageNeighbors = numerator / denominator;
    }
    // now we compare threshold values
    if (averageNeighbors < 1.5)
    {
        return false;
    }
    else if (averageNeighbors >= 1.5 && averageNeighbors <= 2.5)
    {
        if (myObject.getStatus() == 'x')
        {
            return true;
        }
        return false;
    }
    else if (averageNeighbors > 2.5 && averageNeighbors <= 3.5)
    {
        return true;
    }
    else if (averageNeighbors > 3.5)
    {
        return false;
    }
}



void Grid::calculateNeighborsDonut()
{
    int neighborCtr = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // cout << "i index: " << i << endl;
            // cout << "j index: " << j << endl;
            if ((i - 1) >= 0)
            {
                if (myGrid[i - 1][j].getStatus() == 'x')
                {
                    // cout << "1: ";
                    neighborCtr += 1;
                }
            }
            else // so if we are at the border, aka (i-1)<0
            {
                if (myGrid[row - 1][j].getStatus() == 'x') // this checks same column but at bottom
                {
                    // cout << "2: ";
                    neighborCtr += 1;
                }
                if (j - 1 < 0) // here we have both i and j < 0 so we are at upper left corner and will check bottom right
                {
                    if (myGrid[row - 1][column - 1].getStatus() == 'x')
                    {
                        // cout << "3: ";
                        neighborCtr += 1;
                    }
                }
                if (j + 1 == column) // so if we are at top right corner
                {
                    if (myGrid[row - 1][0].getStatus() == 'x') //checking bottom left corner
                    {
                        // cout << "4: ";
                        neighborCtr += 1;
                    }
                }
            }
            // checking 1 pos left
            if ((j - 1) >= 0)
            {
                if (myGrid[i][j - 1].getStatus() == 'x')
                {
                    // cout << "5: ";
                    neighborCtr += 1;
                }
            }
            else
            {
                if (myGrid[i][column - 1].getStatus() == 'x')
                {
                    // cout << "6: ";
                    neighborCtr += 1;
                }
            }
            ////////////////////////////////////
            ////////////////////////////////////
            ////////////////////////////////////
            ////////////////////////////////////
            // checking 1 pos down
            if ((i + 1) < row)
            {
                if (myGrid[i + 1][j].getStatus() == 'x')
                {
                    // cout << "7: ";
                    neighborCtr += 1;
                }
            }
            else // if i+1 == row
            {
                if (myGrid[0][j].getStatus() == 'x')
                {
                    // cout << "8: ";
                    neighborCtr += 1;
                }
                if (j - 1 < 0) // so we are at bottom left
                {
                    if (myGrid[0][column - 1].getStatus() == 'x')
                    {
                        // cout << "9: ";
                        neighborCtr += 1;
                    }
                }
                if (j + 1 == column) // bottom right
                {
                    if (myGrid[0][0].getStatus() == 'x') // so we check top left
                    {
                        // cout << "10: ";
                        neighborCtr += 1;
                    }
                }
            }
            // checking 1 pos right
            if ((j + 1) < column)
            {
                if (myGrid[i][j + 1].getStatus() == 'x')
                {
                    // cout << "11: ";
                    neighborCtr += 1;
                }
            }
            // checking up right
            if ((i - 1) >= 0 && (j + 1) < column)
            {
                if (myGrid[i - 1][j + 1].getStatus() == 'x')
                {
                    // cout << "12: ";
                    neighborCtr += 1;
                }
            }
            // checking up left
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                if (myGrid[i - 1][j - 1].getStatus() == 'x')
                {
                    // cout << "13: ";
                    neighborCtr += 1;
                }
            }
            // checking down right
            if ((i + 1) < row && (j + 1) < column)
            {
                if (myGrid[i + 1][j + 1].getStatus() == 'x')
                {
                    // cout << "14: ";
                    neighborCtr += 1;
                }
            }
            // checking down left
            if ((i + 1) < row && (j - 1) >= 0)
            {
                if (myGrid[i + 1][j - 1].getStatus() == 'x')
                {
                    // cout << "15: ";
                    neighborCtr += 1;
                }
            }
            if (j + 1 == column) // if we arent at a corner
            {
                if (myGrid[i][0].getStatus() == 'x')
                {
                    // cout << "16: ";
                    neighborCtr += 1;
                }
            }
            myGrid[i][j].setAvgNeighbors(neighborCtr);
            // we send the average current neighbor value to array update function
            myGrid[i][j].setGenerations(myGrid[i][j].getAvgNeighbors());
            myGrid[i][j].setwillLive(threshhold(myGrid[i][j])); // we pass our cell object to determine if it will live
            // cout << myGrid[i][j].status;
            neighborCtr = 0;
        }
    }
    // now we loop and update
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            myGrid[i][j].setStatus(myGrid[i][j].getwillLive() ? 'x' : '-');
        }
    }
}

void Grid::calculateNeighborsMirror()
{
    int neighborCtr = 0;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    if (myGrid[i][j].getStatus() == 'x')
                    {

                        neighborCtr += 3; // corners are + 3 if occupied
                    }
                }
                // else if (j != column - 1) // so while we arent at the right corner
                // {
                //     if (myGrid[i][j] == "x")
                //     {
                //         cout << "2: ";
                //         neighborCtr += 1;
                //     }
                // }
                if (j + 1 == column) // so we are at corner
                {
                    if (myGrid[i][j].getStatus() == 'x')
                    {

                        neighborCtr += 3;
                    }
                }
            }
            else if (j == 0 && i > 0)
            {
                if (i + 1 == row) // bottom left corner
                {
                    if (myGrid[i][j].getStatus() == 'x')
                    {

                        neighborCtr += 3;
                    }
                }
                else if (myGrid[i][j].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            if (j + 1 == column) // or should it be else if?
            {
                if (i + 1 == row) // bottom right corner
                {
                    if (myGrid[i][j].getStatus() == 'x')
                    {

                        neighborCtr += 3;
                    }
                }
                else if (myGrid[i][j].getStatus() == 'x' && i != 0) // we already checked upper right
                {

                    neighborCtr += 1;
                }
            }
            if (i + 1 == row)
            {
                if ((j + 1 != row - 1) && j - 1 > 0) // ignore both left and right corners bc we account for that above
                {
                    if (myGrid[row - 1][j].getStatus() == 'x')
                    {

                        neighborCtr += 1;
                    }
                }
            }
            // else // so while i not at the end
            // {
            //     if (j + 1 != column) // checking diagonally down r
            //     {
            //         if (myGrid[i + 1][j + 1] == "x")
            //         {
            //             cout << "forgot to document lol" << endl;
            //             neighborCtr += 1;
            //         }
            //     }
            // }
            // make below an else and all inside it..?
            // checking 1 pos down
            if ((i + 1) < row)
            {
                if (myGrid[i + 1][j].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking 1 pos up
            if ((i - 1) >= 0)
            {
                if (myGrid[i - 1][j].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking 1 pos right
            // cout << "RIGHT BEFORE 3, 0 ERROR; j+1 = " << j + 1 << endl;
            // cout << "j+1 < column is: " << (j + 1 < column) << endl;
            if ((j + 1) < column)
            {
                if (myGrid[i][j + 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking 1 pos left
            if ((j - 1) >= 0)
            {
                if (myGrid[i][j - 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking up right
            if ((i - 1) >= 0 && (j + 1) < column)
            {
                if (myGrid[i - 1][j + 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking up left
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                if (myGrid[i - 1][j - 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking down right
            if ((i + 1) < row && (j + 1) < column)
            {
                if (myGrid[i + 1][j + 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            // checking down left
            if ((i + 1) < row && (j - 1) >= 0)
            {
                if (myGrid[i + 1][j - 1].getStatus() == 'x')
                {

                    neighborCtr += 1;
                }
            }
            if (i == 0 && j != 0 && j != column - 1)
            {
                if (myGrid[i][j].getStatus() == 'x')
                {
                    neighborCtr += 1;
                }
            }
            myGrid[i][j].setAvgNeighbors(neighborCtr);
            // we send the average current neighbor value to array update function
            myGrid[i][j].setGenerations(myGrid[i][j].getAvgNeighbors());
            myGrid[i][j].setwillLive(threshhold(myGrid[i][j])); // we pass our cell object to determine if it will live
            // cout << myGrid[i][j].status;
            neighborCtr = 0;
        }
    }
    // now we loop and update
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            myGrid[i][j].setStatus(myGrid[i][j].getwillLive() ? 'x' : '-');
        }
    }
}

void Grid::processFile(string input_file) {

  // Create a text string, which is used to output the text file
string myText;
istringstream stream;
istringstream stream2;
int row;
int column;
string strRow;
string strColumn;

string firstLine;
string secondLine;
string thirdLine;
string phonyGrid;

// Read from the text file
ifstream inFS;

//opening the file
cout << "Opening file" << endl;
inFS.open(input_file);

if (!inFS.is_open()) {
  cout << "Could not open file myfile.txt" << endl;
}

inFS >> input_file;
strRow = input_file;
row = stoi(strRow);
inFS >> input_file;
strColumn = input_file;
column = stoi(strColumn);


if (!inFS.eof()) {
  cout << "input failure before reaching end of life." << endl;
}

cout << "Closing file" << endl;
inFS.close();

}


void Grid::nextGeneration(){
  int count = 0;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      if (myGrid[i][j].getwillLive() == false) {
        myGrid[i][j].setStatus('-');
      }
      else if (myGrid[i][j].getwillLive() == true){
        myGrid[i][j].setStatus('x');
        count += 1;
      }
    }
  }
  if (count == 0) {
    genEmpty = true;
    cout << "All cells died! Game over." << endl;
  }
  // else if (gridArray[1] == gridArray[2]) {
  //   isStable = true;
  //   cout << "Simulation is stable! Game over." << endl;
  // }
}
