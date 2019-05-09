/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

static FILE* bsmy;
static FILE* bsop;
static CellContent my[FIELDSIZE][FIELDSIZE];
static CellContent op[FIELDSIZE][FIELDSIZE];
static CellContent guesses[FIELDSIZE][FIELDSIZE];

/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
  bsmy = fopen("battleship.my","r");
  bsop = fopen("battleship.op","r");
  fread(&my, sizeof(my), 1, bsmy);
  fread(&op, sizeof(op), 1, bsop);
  for (int i = 0; i < FIELDSIZE; i++) {
    for (int j = 0; j < FIELDSIZE; j++) {
      guesses[i][j] = Unknown;
    }
  }
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return OutOfRange;
  }
  return my[row][col];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return false;
  }
  if (op[row][col] == Boat)
  {
    PlaceWater(row-1,col-1);
    PlaceWater(row-1,col);
    PlaceWater(row-1,col+1);
    PlaceWater(row,col+1);
    PlaceWater(row,col-1);
    PlaceWater(row+1,col-1);
    PlaceWater(row+1,col);
    PlaceWater(row+1,col+1);
  }
  guesses[row][col] = op[row][col];
  return true;
}

void PlaceWater(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return;
  }
  guesses[row][col] = Water;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if(row < 0 || row > FIELDSIZE-1 || col < 0 || col > FIELDSIZE-1)
  {
    return OutOfRange;
  }
  return guesses[row][col];
}
