/*  This file includes function declarations for console manipulation
    This following source code uses some functions from these websites:
        + https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
        + https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console  */

#ifndef _CONSOLE_H                                                      // Header Guard: This ensures that the header file is included only once during compilation.
#define _CONSOLE_H


#include "defination.h"

void ClearScreen();                                                     // Clear the console screen

void ResizeWindow(int posX, int posY, int width, int height);           // Resize window console
void DisableResizeWindow();                                             // Disable the resizing of the console window

void gotoXY(SHORT x, SHORT y);                                          // Move the console cursor to the specific position

void OnOffCursor(bool OnOff);                                           // Turn the cursor on or off in the console

void setColor(int backgound_color, int text_color);                     // Set background color and text color

void SetUpGameConsole();                                                // Synthesize functions to set up console


#endif