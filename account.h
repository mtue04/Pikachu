//  This file includes function declarations for Sign Up - Sign In - Leaderboard manipulation

#ifndef _ACCOUNT_H                                                          // Header Guard: This ensures that the header file is included only once during compilation.
#define _ACCOUNT_H


#include "defination.h"
#include "console.h"

void readData(vector<Player> &listP);                                       // This function is used to read the data of users from "users.dat" and store it to the listP array.
void writeData(vector<Player> &listP);                                      // This function is write the data of user from listP array to "users.dat" - binary file.
void readSaveFile(vector<Save> &saveG);                                     // This function is used to read the scores of users who have played the game and store it to saveG array, this function use for saving player's score.
void writeSaveFile(vector<Save> &saveG);                                    // This function is used to write the saveG array to "save.dat" - a binary file for saving the score of users.
void updateSaveFile(vector<Save> &saveG, string cur_Player, int score);     // This function is used to update the score of players and also write the new score to "save.dat" for saving.
int getCurScore (vector<Save> &saveG, string cur_Player);                   // Used to get the current Score of the current player (cur_Player).

void hidePassword(string &password);                                        // Convert password when users type into "*"
void SignUp(vector<Player> &listP, string &cur_player);                     // This function is used to sign up for a new account and also writes the new account's data to "users.dat".
void SignIn(vector<Player> &listP, bool &logInFlag, string &cur_player);    // This function is used to log in with an existing account and also provides the current player after the user logs in successfully.

void leaderBoardSorting(vector<Save> &saveG);                               // Used to Sort the saveG array.
void leaderBoardPrinting(vector<Save> &saveG);                              // Used to print the leaderboard.


#endif