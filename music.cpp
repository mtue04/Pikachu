#include "music.h"

void bgSound(bool flag) {
    if (flag == true)
        PlaySound(TEXT("resource\\SoundEffect\\bgSound.wav"),NULL, SND_ASYNC);
    else 
        PlaySound(NULL, NULL, 0);
}

void tapSound() {
    PlaySound(TEXT("resource\\SoundEffect\\tap.wav"),NULL, SND_ASYNC);
}

void shuffleSound() {
    PlaySound(TEXT("resource\\SoundEffect\\shuffle.wav"),NULL, SND_ASYNC);
}

void successConnectSound() {
    PlaySound(TEXT("resource\\SoundEffect\\successSound.wav"),NULL, SND_ASYNC);
}

void failConnectSound() {
    PlaySound(TEXT("resource\\SoundEffect\\failSound.wav"),NULL, SND_ASYNC);
}