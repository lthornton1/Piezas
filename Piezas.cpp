#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  turn = X;
  board = std::vector<std::vector<Piece>>(BOARD_ROWS,std::vector<Piece>(BOARD_COLS,Blank));
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  board = std::vector<std::vector<Piece>>(BOARD_ROWS,std::vector<Piece>(BOARD_COLS,Blank));
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  //Since we have to flip the turn regardless of what happens, we store
  //the current turn in temp so we can use it, and then flip the turn
  Piece temp = turn;
  if (turn == X) {
    turn = O;
  } else {
    turn = X;
  }

  //If input was out of bounds return Invalid
  if (column < 0 || column >= BOARD_COLS){
    return Invalid;
  }

  //Loop bottom to top of board, when we find our first blank,
  //place piece and return the piece that was placed
  for (int i = 0; i <  BOARD_ROWS ; i++) {
    if (board[i][column] == Blank){
      board[i][column] = temp;
      return temp;
    }
  }//for

  //If we never found a blank space because coulmn was full, return blank
  return Blank;
}// dropPiece

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if (row < 0 || row >= BOARD_ROWS || column < 0 || column >= BOARD_COLS)
    return Invalid;
  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  //using these two small arrays we can drastically reduce our
  //cyclomatic complexity by using index of ox to verify we are
  //modifying the correct item, essentially forces X = 1 and O = 0
  //to make the logic simpler, withour having to use a size 256 array
  int max[2] = {};
  char ox[2] = {'O','X'};

  //Find the maximums for rows
  for(int i = 0; i < BOARD_ROWS; i++) {

    //If anything in the top row is blank return Invalid
    //Since we fill bottom to top, if top is full what is
    //below is necessarily filled
    if (board[i][BOARD_ROWS-1] == Blank) {
      return Invalid;
    }

    int cur = 0;
    int curIndex = 0;

    for(int j = 0; j < BOARD_COLS; j++) {

      if (ox[curIndex] == board[i][j]){
        cur++;
      }

      //Since curIndex can now only be one or 0 we can treat it like a bit
      //that we can flip to change which piece we are currently looking at
      //and since we for the Invalid check outside the loop we dont have to
      //worry about blank squares for the given iteration
      else {
       curIndex = curIndex ^ 1;
       cur = 1;
     }

     //Rather than having 2 seperate variables we can use this array to always
     //do the correct check regardless of which piece type were looking at
     if (cur > max[curIndex])
       max[curIndex] = cur;

    }
  }//For row max

  //Find the maximums for columns
  for(int i = 0; i < BOARD_COLS; i++) {

    int cur = 0;
    int curIndex = 1;

    for(int j = 0; j < BOARD_ROWS; j++) {
      if (ox[curIndex] == board[j][i]){
        cur++;
      }
      else {
       curIndex = curIndex ^ 1;
       cur = 1;
     }
     if (cur > max[curIndex])
       max[curIndex] = cur;
    }
  }//for column max


  if (max[0] < max[1])
    return X;
  else if (max[0] > max[1])
    return O;
  return Blank;

}//gameState
