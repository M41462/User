#ifndef TETROMINO_HPP
#define TETROMINO_HPP
#include "Blocks.hpp"
#include "Board.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <unordered_map>
#include <vector>

class Tetromino {
public:
  Tetromino();
  ~Tetromino();

  void drawTetromino(const int (&board)[Constants::ROWS][Constants::COLS],
                     const std::vector<Color> &colors);

  void updateTetromino(float &dt, Board &board,
                       const std::vector<Color> &colors);
  void movements(float dt,
                 const int (&board)[Constants::ROWS][Constants::COLS]);
  std::unordered_map<TetrominoType, TetrisShapes::Shape> &getTetriminoShapes() {
    return tetriminoShapes;
  }
  TetrominoType getNextTetrimino() { return this->nextTetrimino; }
  BlocksStruct &getBlocks() { return blocks; }

  void lockPiece(int (&board)[Constants::ROWS][Constants::COLS]);

  bool checkCollision(const int (&board)[Constants::ROWS][Constants::COLS]);
  void rotationLogic(const int (&board)[Constants::ROWS][Constants::COLS]);

  bool getGameOver() { return this->gameOver; }

private:
  bool gameOver = false;
  float fallTimer = 0.0f;
  std::unordered_map<TetrominoType, TetrisShapes::Shape> tetriminoShapes;
  void setBoundaries();
  BlocksStruct blocks;

  inline void spawnPiece();
  TetrominoType nextTetrimino;
};

#endif
