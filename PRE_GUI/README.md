PRE_GUI: code without graphic interface, prints a board of characters

Input position from xy=00 to xy=99

Pieces added:
    all

Functions missing:
    store removed pieces (maybe?, do in qt)
    setup board (players inicial input, wait for qt implementation)
    

cmake-googletesting explained: https://www.youtube.com/watch?v=Lp1ifh9TuFI&t=695s
Unit tests added:
    Scout(all)
    Gameover(for red pieces only)


commands:
make : creates stratego.exe
.\stratego.exe : runs game

build\test\alltests.exe : runs unit tests
