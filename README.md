PRE_GUI: code without graphic interface, prints a board of characters

Input position from xy=00 to xy=99~

Pieces added:
    all -flag

Functions missing:
    evaluate if game is over(check movable pieces + flag)
    store removed pieces (maybe?)
    

cmake-googletesting explained: https://www.youtube.com/watch?v=Lp1ifh9TuFI&t=695s
Unit tests added:
    Scout(begining)


commands:
make : creates stratego.exe
.\stratego.exe : runs game

build\test\Scout_test.exe : runs scout piece unit test
