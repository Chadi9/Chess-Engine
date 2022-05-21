old.cpp is the source file

To run / use the program:

First download
- Chess-old-64bit.exe
- mscvp140.dll
- vcruntime140.dll

Put them all in the same folder, then run the Chess-old-64bit.exe file

You should see this screen pop up:
-----------------------------------------
| Br | Bk | Bb | BQ | BK | Bb | Bk | Br |
-----------------------------------------
| Bp | Bp | Bp | Bp | Bp | Bp | Bp | Bp |
-----------------------------------------
|    |    |    |    |    |    |    |    |
-----------------------------------------
|    |    |    |    |    |    |    |    |
-----------------------------------------
|    |    |    |    |    |    |    |    |
-----------------------------------------
|    |    |    |    |    |    |    |    |
-----------------------------------------
| Wp | Wp | Wp | Wp | Wp | Wp | Wp | Wp |
-----------------------------------------
| Wr | Wk | Wb | WQ | WK | Wb | Wk | Wr |
-----------------------------------------
White or black?

-- All inputs are typed in and entered. All case sensitive -- 
Type the side you are playing, and enter

How to Move:
1. When it is your move, you should see a prompt like this: Enter your move:
2. Type the square of the piece you want to move then a "-" then the square on which you want to move the piece too (ex. e2-e4). ALL LOWERCASE
3. The program will accept any move you put in, so you have to make sure it is the right one. 
4. The program will continously prompt you for moves until to type "stop" and enter. This is so you can enter moves like castling and en passant. 

After you move, the program will automatically move, and print the resulting board after both of your moves. It then will become your move once again.

Reading the board:

Wr - White Rook
Wk - White Knight
Wb - White Bishop
WK - White King
WQ - White Queen
Wp - White Pawn

Br - Black Rook
Bk - Black Knight
Bb - Black Bishop
BK - Black King
BQ - Black Queen
Bp - Black Pawn

Warnings:
Currently, promoting is not implemented. Once the pawn reaches the edge of the board, it will just stay there and do nothing.




