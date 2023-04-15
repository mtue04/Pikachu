/*  This file includes function declarations for game board manipulation and GUI of game screen
    This following source code references the idea of 
        + Nguyễn Văn Quân (https://nguyenvanquan7826.wordpress.com/2014/03/25/thuat-toan-game-pokemon-pikachu/)  
        + Nguyễn Anh Kiệt_22127220_22CLC10_HCMUS - Nguyễn Lê Thanh Duy_22127474_22CLC10_HCMUS                  
        + Ngô Văn Khải_22127174_22CLC10_HCMUS - Nguyễn Quốc Tín_22127416_22CLC10_HCMUS                          */

#ifndef _GAMEBOARD_H            // Header Guard: This ensures that the header file is included only once during compilation.
#define _GAMEBOARD_H


#include "defination.h"
#include "InterfaceDesign.h"
#include "music.h"
#include "account.h"

// Part 1: Stages difficulty increase
void level2(GameBoard &board);          // blocks moving up
void level3(GameBoard &board);          // blocks moving left
void level4(GameBoard &board);          // blocks moving down
void level5(GameBoard &board);          // blocks moving right

// Part 2: Handle game board: generate, print, free memory
void generateGameBoard(GameBoard &board);                                                    // Generate randomly game board
void printCell(GameBoard board, int x, int y, int background_color, int text_color);         // Print each cell of board to handle independently         
void drawBG(GameBoard board, int x, int y, int background_color, int text_color);            // To ordinary game, draw background into empty cells    
void printBorder(GameBoard board);                                                           // Print border of game board       
void printGameBoard(GameBoard &board, Position pCurrent, int level);                         // Print game board (synthesize printCell and drawBG to show game board)
void freeMemory(GameBoard &board);                                                           // Free memory of GameBoard, including char** pokemons, bool** highlighted
void freeBG(GameBoard &board);                                                               // Free memory of GameBoard, including string** bg

// Part 3: Handle game logic
bool isLegalChoice(GameBoard board, Position pCurrent);                         // Check if the choice is not NULL
bool isOver(GameBoard board);                                                   // Check if game is over
bool checkLineX(GameBoard board, int y1, int y2, int x);                        // Horizontal line check            (I Matching)
bool checkLineY(GameBoard board, int x1, int x2, int y);                        // Vertical line check              (I Matching)
int checkRectX(GameBoard board, Position p1, Position p2);                      // Check the horizontal rectangle   (L Matching and Z Matching)
int checkRectY(GameBoard board, Position p1, Position p2);                      // Check the vertical rectangle     (L Matching and Z Matching)
int checkMoreLineX(GameBoard board, Position p1, Position p2, int type);        // Check more horizontal line       (U Matching)
int checkMoreLineY(GameBoard board, Position p1, Position p2, int type);        // Check more vertical line         (U Matching)
bool canBeConnected(GameBoard board, Position p1, Position p2);                 // Check if two pokemons can be connected by below functions
int countCheckToShuffle(GameBoard &board);                                      // Count the number of cases that can be connected (Assist to shuffle board and move suggestion)
void shuffleBoard(GameBoard &board);                                            // If the board cannot continue because of players' fault, this function will appear to shuffle board
void moveSuggestion(GameBoard &board);                                          // Move suggestion (Called when players enter button)

// Part 4: Draw line (Visual effects)
void drawArrowXFrom(GameBoard board, Position p);                   // Draw ⮜
void drawArrowXTo(GameBoard board, Position p);                     // Draw ⮞
void drawArrowYFrom(GameBoard board, Position p);                   // Draw ⮝
void drawArrowYTo(GameBoard board, Position p);                     // Draw ⮟
void drawLineX(GameBoard board, int y1, int y2, int x);             // Draw horizontal line
void drawLineY(GameBoard board, int x1, int x2, int y);             // Draw vertical line
int drawLine(GameBoard board, Position p1, Position p2);            // Synthesize functions to draw line from the first pokemon to the second one

// Part 5: Synthesize functions and draw interface for game screen
void countdown(time_t originalTime, int timeLeft, bool &overTime);                                                                                                          // Show time left
void drawIn4Board(GameBoard board, string cur_player, vector<Save> saveG, int level);                                                                                       // Draw information board to show player's information, game information, etc.
void handleEvent(GameBoard &board, Position &pCurrent, Position &p1, Position &p2, string cur_player, vector<Save> &saveG, int &pointAtBoard, int level, bool &finished);   // input character and handle event
void handleGameBoard(GameBoard &board, string cur_player, vector<Save> &saveG, int level, bool &finished);                                                                  // Synthesize two above functions and handle game board
void afterGame(GameBoard &board, int &level, bool &back_, bool &finished);                                                                                                  // After game board selection, including: next level, restart, back


#endif