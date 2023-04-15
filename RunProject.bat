@echo off
REM Set console window size and buffer settings
cmd /c mode con:cols=106 lines=30 bufferSize=5000 numBuffers=4 cursorSize=larger
cmd /c mode con:font=Consolas&16
cmd /c mode con: sb 106 30 
cmd /c mode con: wnd 106 30

REM Change CHCP to UTF-8
chcp 65001
cls

REM Generate and run game
g++ -o main.exe main.cpp -lwinmm
main.exe