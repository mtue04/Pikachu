/*  This file includes function declarations for sound effect
    Our project utilizes some sound sources from:
        + Verdanturf Town - https://www.youtube.com/watch?v=MHFBO-ASaE8 
        + https://freesound.org/                                        */

#ifndef _MUSIC_H                    // Header Guard: This ensures that the header file is included only once during compilation.
#define _MUSIC_H


#include "defination.h"

void bgSound(bool flag);            // Play background music

void tapSound();                    // Play if player choose one pokemon when playing

void shuffleSound();                // Play if shuffle board turn on

void successConnectSound();         // Play if 2 pokemon connected successfully 

void failConnectSound();            // Play if 2 pokemon connected unsuccessfully 


#endif