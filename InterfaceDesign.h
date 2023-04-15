//  This file includes function declarations for Graphical User Interface manipulation

#ifndef _INTERFACEDESIGN_H                                  // Header Guard: This ensures that the header file is included only once during compilation.
#define _INTERFACEDESIGN_H


#include "defination.h"
#include "console.h"

void welComeScreen(int selected);                           // Draw welcome screen, including: "SIGN IN", "SIGN UP", "EXIT"
void blinkingStar();                                        // Blinking blinking

void mainMenu(int selected);                                // Draw main menu, including: "PLAY", "HELP", "RANKING", "CREDITS", "LOG OUT"

void gameMode(int selected);                                // Draw game mode, including: "EASY", "MEDIUM", "HARD", "CREATIVE MODE", "BACK"
void creativeMode(int selected, int numRows, int numCols);  // Draw creative mode, which players can choose the number of rows and columns to play

void help();                                                // Draw help screen, including: rule of game, game controls and how to earn points 

void credits();                                             // Draw credits

void pauseMenu(int selected);                               // Draw pause menu
void afterGameOption(int selected);                         // Draw after game finish, including: continue game or exit
void failGame(int selected);                                // Draw incomplete menu
void logOutConfirm(int selected);                           // Draw log out confirm screen
void exitConfirm(int selected);                             // Draw exit confirm screen 

void loadingBar();                                          // Draw loading bar for reality


#endif