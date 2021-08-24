# Game-of-Life
Conway's famous game of life, an automata of cellular generations. A simulation modelling the life cycle of cells.

Written using docker container, compile with g++. Originally written for a Data Structures assignment, modified and improved to add more features.

**Game modes to choose from:**
- Classic mode: All locations off the grid are considered to be empty.
- Doughnut mode: The grid is wrapped around itself horizontally and vertically, resulting in a donut shape. Here, any reference off the right-hand-side is wrapped around to the left-most column of the same row and vice-versa. Any reference off the top wraps to the bottom in the same column.
- Mirror Mode: References off the grid are bounced back as though the wall were a mirror. This means the reflection of a cell could count as its own neighbor. For a corner cell, if it was occupied, its reflection would count as 3 neighbors...1 for the vertical reflection, l for the horizontal reflection, and 1 for the diagonal reflection.

**Note: these game modes were written by Rene German and Erik Linstead, I do not claim to own or have created them. They are merely the modes I implemented in my code.**

**How to run:**
- Attach to required docker container to assure computer architecture is compatible, compile with "g++ *.cpp".
- You can select 'Enter' to manually display the next generation or 'Pause' to allow program to run automatically with brief pauses.
- You will be prompted to enter number of rows, columns, and population density. From there, the grid will be randomly populated.
- You will then select the boundary mode of the game (normal, mirror, donut).
- Upon the calculation of each generation, the grid will be outputted as a text grid.
- The program will stop of the grid either stabilizes or becomes empty. If the simulation is infinite, it will keep running.
