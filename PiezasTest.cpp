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

TEST(PiezasTest, dropPieceCheck)
{
  Piezas obj;
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == X)
    check = true;
	ASSERT_TRUE(check);
}

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

TEST(PiezasTest, dropPieceBoundsCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  obj.dropPiece(0);
  Piece actual = obj.dropPiece(0);
  bool check = false;
  if (actual == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, dropPieceBoundsCheck2)
{
  Piezas obj;
  Piece actual = obj.dropPiece(-1);
  bool check = false;
  if (actual == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, dropPieceBoundsCheck3)
{
  Piezas obj;
  Piece actual = obj.dropPiece(-1);
  bool check = false;
  if (actual == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

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

TEST(PiezasTest, pieceAtCheck)
{
  Piezas obj;
  obj.dropPiece(0);
  bool check = false;
  if (obj.pieceAt(0,0) == X)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, pieceAtCheckNoDrops)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,0) == Blank)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, pieceAtCheckOutOfBounds1)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(-1,0) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, pieceAtCheckOutOfBounds2)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,-1) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, pieceAtCheckOutOfBounds3)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(5,0) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

TEST(PiezasTest, pieceAtCheckOutOfBounds4)
{
  Piezas obj;
  bool check = false;
  if (obj.pieceAt(0,5) == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

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

TEST(PiezasTest, gameStateEmpty)
{
  Piezas obj;
  bool check = false;
  if (obj.gameState() == Invalid)
    check = true;
	ASSERT_TRUE(check);
}

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
