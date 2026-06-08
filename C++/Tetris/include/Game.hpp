#ifndef GAME_HPP
#define GAME_HPP
#include "Board.hpp"
#include "Data.hpp"
#include "Tetromino.hpp"
#include <raylib.h>
enum GameStatus { MENU, PLAYING, LOSE };

class Game {
public:
  Game();
  ~Game();

  void run();
  void render();
  void update(float &dt);
  bool loadTetrisIcon();
  bool loadTetrisFont();
  bool loadTetrisMusic();
  bool loadTetrisGameOverMusic();
  const unsigned int getScore() { return this->score; };
  enum GameStatus getGameStatus() { return this->gameStatus; }
  void setGameStatus(enum GameStatus gameStatus) {
    this->gameStatus = gameStatus;
  }

  bool startGame() { return IsKeyPressed(KEY_ENTER); }

private:
  void drawNextTetromino();
  void drawGameOver();
  unsigned int score = 0;
  void drawScore();
  Image tetrisIcon;
  Font tetrisFont;
  Music tetrisMusic;
  Music tetrisGameOverMusic;
  Board board;
  Tetromino tetromino;
  Vector2 center;
  GameStatus gameStatus;
  Data data;
};

#endif
