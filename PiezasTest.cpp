/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

//Checks if the first piece dropped is X
TEST(PiezasTest, dropPieceCheck)
{
  Piezas obj;
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == X)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that the second piece dropped is O
TEST(PiezasTest, dropPieceCheck2)
{
  Piezas obj;
  obj.dropPiece(0);
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == O)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that droppiece returns Blank when a piece is placed into a full column
TEST(PiezasTest, dropPieceBoundsCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == Blank)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that if a piece is attempted to be placed into a negative column
//Invalid is returned
TEST(PiezasTest, dropPieceBoundsCheck2)
{
  Piezas obj;
  Piece actual = obj.dropPiece(-1);
  bool check = false;
  if (actual == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that if a piece is attempted to be placed into a nonexistent column
//Invalid is returned
TEST(PiezasTest, dropPieceBoundsCheck3)
{
  Piezas obj;
  Piece actual = obj.dropPiece(5);
  bool check = false;
  if (actual == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that drop piece flips turn after out of bounds place
TEST(PiezasTest, dropPieceCheckLostTurn)
{
  Piezas obj;
  obj.dropPiece(-1);
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == O)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that drop piece flips turn after attempting to place in a full column
TEST(PiezasTest, dropPieceLoseTurnBecauseFull)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  Piece actual = obj.dropPiece(1);
  bool check = false;
  if (actual == O)
    check = true;
	ASSERT_TRUE(check);
}

//Verifies that piece is properly placed, and piece returns the matching piece
TEST(PiezasTest, pieceAtCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  bool check = false;
  if (obj.pieceAt(0,0) == X)
    check = true;
	ASSERT_TRUE(check);
}

//Checks that piecesAt sees a blank when no drops have happened
TEST(PiezasTest, pieceAtCheckNoDrops)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,0) == Blank)
    check = true;
	ASSERT_TRUE(check);
}

//pieces at bounds checking
TEST(PiezasTest, pieceAtCheckOutOfBounds1)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(-1,0) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//pieces at bounds checking
TEST(PiezasTest, pieceAtCheckOutOfBounds2)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,-1) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//pieces at bounds checking
TEST(PiezasTest, pieceAtCheckOutOfBounds3)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(5,0) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//pieces at bounds checking
TEST(PiezasTest, pieceAtCheckOutOfBounds4)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,5) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//verifies that drop piece is dropping the correct piece in the correct spot
TEST(PiezasTest, pieceAtCheckMultipleDrops)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  bool check = false;
  if (obj.pieceAt(1,0) == O)
    check = true;
	ASSERT_TRUE(check);
}

//checks that reset does reset a non empty board
TEST(PiezasTest, resetCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.reset();
  bool check = false;
  if (obj.pieceAt(0,0) == Blank)
    check = true;
	ASSERT_TRUE(check);
}

//checks that reset doesnt reset turns, and only resests board
TEST(PiezasTest, resetTurnCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.reset();
  obj.dropPiece(0);
  bool check = false;
  if (obj.pieceAt(0,0) == O)
    check = true;
	ASSERT_TRUE(check);
}

//checks that an empyt game state returns invlaid
TEST(PiezasTest, gameStateEmpty)
{
  Piezas obj;
  bool check = false;
  if (obj.gameState() == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

//fills the board with all xs to verify that gameState can detect a winner
TEST(PiezasTest, gameStateXWins)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++) {
    for(int j = 0; j < BOARD_COLS; j++) {
      obj.dropPiece(j);
      obj.dropPiece(-1);
    }
  }
  bool check = false;
  if (obj.gameState() == X)
    check = true;
	ASSERT_TRUE(check);
}

//fills the board with all Os to verify that gameState can detect a winner
TEST(PiezasTest, gameStateOWins)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++) {
    for(int j = 0; j < BOARD_COLS; j++) {
      obj.dropPiece(-1);
      obj.dropPiece(j);
    }
  }
  bool check = false;
  if (obj.gameState() == O)
    check = true;
	ASSERT_TRUE(check);
}

//verifies that both X and O maxs are maintained at the same time as they fill
//up alternating columns
TEST(PiezasTest, gameStateTieCol)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS ; i++) {
    for(int j = 0; j < BOARD_COLS; j++) {
      obj.dropPiece(j);
    }
  }
  bool check = false;
  if (obj.gameState() == Blank)
    check = true;
	ASSERT_TRUE(check);
}

//verifies that both X and O maxs are maintained at the same time as they fill
//up alternating rows
TEST(PiezasTest, gameStateTieRow)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++) {
    for(int j = 0; j < BOARD_COLS; j++) {
      obj.dropPiece(j);
      obj.dropPiece(j);
    }
  }
  bool check = false;
  if (obj.gameState() == Blank)
    check = true;
	ASSERT_TRUE(check);
}

//verifies that both X and O maxs are maintained at the same time as they dont
//fill up rows or columns, but should have the same max
TEST(PiezasTest, gameStateTieNoFullRowsOrColumns)
{
  Piezas obj;
  for(int i = 0; i < BOARD_ROWS; i++) {
    for(int j = 0; j < BOARD_COLS; j++) {
      obj.dropPiece(j);
      obj.dropPiece(j);
      obj.dropPiece(j);
    }
  }
  bool check = false;
  if (obj.gameState() == Blank)
    check = true;
	ASSERT_TRUE(check);
}
