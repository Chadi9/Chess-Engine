#include <iostream>
#include <vector>
#include <map>
#include <chrono>
/*
1: White Pawn
2: White Knight
3: White Bishop
4: White Rook
5: White Queen
6: White King

7: Black Pawn
8: Black Knight
9: Black Bishop
10: Black Rook
11: Black Queen
12: Black King
*/

/*
Color true is white, false is black
*/

//Global Vars
std::map<int, int> points;
int stop_depth =5;
int check_depth = 1;
std::map<int, std::string> characters;
std::map<char, int> rows;
int possibilities = 0;
float endgame_val = 0;
int white_or_black = 0;
std::vector<std::vector<int>> all_comp_moves(stop_depth);

//Maps
std::vector<std::vector<std::vector<int>>> maps = {};



//Display Funcs
void display(std::vector<std::vector<int>> board){
    std::string row = "-----------------------------------------";
    std::string curr;
    if (white_or_black == 0){
        for (int i = 7; i >=0; i--){
            std::cout << row << '\n';
            curr = "";
            for (int j = 0; j < 8; j++){
                curr += "| " + characters[board[i][j]] + " ";
            }
            curr += "|";
            std::cout << curr << "\n";
        }
        std::cout << row << "\n";
    } else{
        for (int i = 0; i <8; i++){
            std::cout << row << '\n';
            curr = "";
            for (int j = 7; j >=0; j--){
                curr += "| " + characters[board[i][j]] + " ";
            }
            curr += "|";
            std::cout << curr << "\n";
        }
        std::cout << row << "\n";
    }
    

}


//Helper Funcs
std::vector<std::vector<int>> get_moves(int y, int x, std::vector<std::vector<int>> board){
    std::vector<std::vector<int>> moves = {};
    int piece = board[y][x];
    
    bool color = true;
    int new_piece = piece;
    if (piece > 6){
        new_piece = piece - 6;
        color = false;
    }
    //Pawn Moves
    if (new_piece == 1){
        if (color == true){
            //If pawn about to promote
            if (y == 6){
                if (board[y + 1][x] == 0){
                    moves.push_back({y + 1,x,2});
                    moves.push_back({y + 1,x,3});
                    moves.push_back({y + 1,x,4});
                    moves.push_back({y + 1,x,5});
                }

                if (x - 1 > -1){
                    if (board[y + 1][x - 1] > 6){
                        moves.push_back({y+1,x-1,2});
                        moves.push_back({y+1,x-1,3});
                        moves.push_back({y+1,x-1,4});
                        moves.push_back({y+1,x-1,5});
                    }
                }
                if (x + 1 < 8){
                    if (board[y + 1][x + 1] > 6){
                        moves.push_back({y + 1, x +1,2});
                        moves.push_back({y + 1, x +1,3});
                        moves.push_back({y + 1, x +1,4});
                        moves.push_back({y + 1, x +1,5});
                    }
                }
                return moves;
            }
         
            //Else
            if (board[y + 1][x] == 0){
                moves.push_back({y + 1,x,piece});
                if (y == 1 && board[y + 2][x] == 0){
                    moves.push_back({y + 2, x,piece});
                }
            }

            if (x - 1 > -1){
                if (board[y + 1][x - 1] > 6){
                    moves.push_back({y+1,x-1,piece});
                }
            }
            if (x + 1 < 8){
                if (board[y + 1][x + 1] > 6){
                    moves.push_back({y + 1, x +1,piece});
                }
            }

                       
        } else {
            //If pawn about to promote
            if (y == 1){
                if (board[y - 1][x] == 0){
                    moves.push_back({y - 1,x,8});
                    moves.push_back({y - 1,x,9});
                    moves.push_back({y - 1,x,10});
                    moves.push_back({y - 1,x,11});
                }

                if (x - 1 > -1){
                    if (board[y - 1][x - 1] <= 6 && board[y - 1][x - 1] != 0){
                        moves.push_back({y-1,x-1,8});
                        moves.push_back({y-1,x-1,9});
                        moves.push_back({y-1,x-1,10});
                        moves.push_back({y-1,x-1,11});
                    }
                }
                if (x + 1 < 8){
                    if (board[y - 1][x + 1] <= 6 && board[y - 1][x + 1] != 0){
                        moves.push_back({y - 1, x +1,8});
                        moves.push_back({y - 1, x +1,9});
                        moves.push_back({y - 1, x +1,10});
                        moves.push_back({y - 1, x +1,11});
                    }
                }
                return moves;
            }

            if (board[y - 1][x] == 0){
                moves.push_back({y - 1, x,piece});
                if (y == 6 && board[y - 2][x] == 0){
                    moves.push_back({y - 2, x,piece});
                }
            }
            if (x - 1 > -1){
                if (board[y - 1][x - 1] <= 6 && board[y -1 ][x - 1] != 0){
                    moves.push_back({y-1,x-1,piece});
                }
            }
            if (x + 1 < 8){
                if (board[y - 1][x + 1] <= 6 && board[y - 1][x + 1] != 0){
                    moves.push_back({y - 1, x +1,piece});
                }
            }   
        }
    }
    //Knight Moves
    else if (new_piece == 2){
        if (y + 1 < 8){
            if (x + 2 < 8){
                if ((board[y + 1][x + 2] <= 6) != color || board[y+1][x+2] == 0){
                    moves.push_back({y+1,x+2,piece});
                }
            }
            if (x - 2 > -1){
                if ((board[y + 1][x - 2] <= 6) != color || board[y+1][x-2] == 0){
                    moves.push_back({y+1,x-2,piece});
                }
            }
        }
            
        if (y - 1 > -1){
            if (x + 2 < 8){
                if ((board[y - 1][x + 2] <= 6) != color || board[y-1][x+2] == 0){
                    moves.push_back({y-1,x+2,piece});
                }
            }
            if (x - 2 > -1){
                if ((board[y - 1][x - 2] <= 6) != color || board[y-1][x-2] == 0){
                    moves.push_back({y-1,x-2,piece});
                }   
            }
        }

        if (y + 2 < 8){
            if (x + 1 < 8){
                if ((board[y + 2][x + 1] <= 6) != color || board[y+2][x+1] == 0){
                    moves.push_back({y+2,x+1,piece});
                }
            }
            if (x- 1 > -1){
                if ((board[y + 2][x - 1] <= 6) != color || board[y+2][x-1] == 0){
                    moves.push_back({y+2,x-1,piece});
                }
            }
        }

        if (y - 2 > -1){
            if (x + 1 < 8){
                if ((board[y - 2][x + 1] <= 6) != color || board[y-2][x+1] == 0){
                    moves.push_back({y-2,x+1,piece});
                }
            }

            if (x - 1 > -1){
                if ((board[y - 2][x - 1] <= 6) != color || board[y-2][x-1] == 0){
                    moves.push_back({y-2,x-1,piece});
                }
            }
        }
        
    }
    //Bishop / Queen Moves
    else if (new_piece == 3 || new_piece == 5){
        int temp_x = x;
        int temp_y = y;
        //The four bishop directions
        while (true){
            temp_x += 1;
            temp_y += 1;
            if (temp_x < 8 && temp_y < 8){
                if (board[temp_y][temp_x] == 0){
                    moves.push_back({temp_y,temp_x,piece});
                } else if ((board[temp_y][temp_x] <= 6) != color){
                    moves.push_back({temp_y,temp_x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        temp_x = x;
        temp_y = y;
        while (true){
            temp_x -= 1;
            temp_y += 1;
            if (temp_x > -1 && temp_y < 8){
                if (board[temp_y][temp_x] == 0){
                    moves.push_back({temp_y,temp_x,piece});
                } else if ((board[temp_y][temp_x] <= 6) != color){
                    moves.push_back({temp_y,temp_x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        temp_x = x;
        temp_y = y;
        while (true){
            temp_x += 1;
            temp_y -= 1;
            if (temp_x < 8 && temp_y > -1){
                if (board[temp_y][temp_x] == 0){
                    moves.push_back({temp_y,temp_x,piece});
                } else if ((board[temp_y][temp_x] <= 6) != color){
                    moves.push_back({temp_y,temp_x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        temp_x = x;
        temp_y = y;
        while (true){
            temp_x -= 1;
            temp_y -= 1;
            if (temp_x > -1 && temp_y > -1){
                if (board[temp_y][temp_x] == 0){
                    moves.push_back({temp_y,temp_x,piece});
                } else if ((board[temp_y][temp_x] <= 6) != color){
                    moves.push_back({temp_y,temp_x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
    //King moves
    else if (new_piece == 6){

        if (y + 1 < 8){
            if (x + 1 < 8){
                if ((board[y + 1][x + 1] <= 6) != color || board[y+1][x+1] == 0){
                    moves.push_back({y+1,x+1,piece});
                }
            }
            if (x - 1 > -1){
                if ((board[y + 1][x- 1] <= 6) != color || board[y+1][x-1] == 0){
                    moves.push_back({y+1,x-1,piece});
                }
            }

            if ((board[y + 1][x] <= 6) != color || board[y+1][x] == 0){
                moves.push_back({y+1,x,piece});
            }
        } 

        if (y - 1 > -1){
            if (x + 1 < 8){
                if ((board[y - 1][x + 1] <= 6) != color || board[y-1][x+1] == 0){
                    moves.push_back({y-1,x+1,piece});
                }
            }
            if (x - 1 > -1){
                if ((board[y - 1][x- 1] <= 6) != color || board[y-1][x-1] == 0){
                    moves.push_back({y-1,x-1,piece});
                }
            }

            if ((board[y - 1][x] <= 6) != color || board[y-1][x] == 0){
                moves.push_back({y-1,x,piece});
            }
        }

        if (x + 1 < 8){
            if ((board[y][x + 1] <= 6) != color || board[y][x + 1] == 0){
                moves.push_back({y,x + 1,piece});
            }
        }

        if (x - 1 > -1){
            if ((board[y ][x - 1] <= 6) != color || board[y][x - 1] == 0){
                moves.push_back({y,x - 1,piece});
            }
        }
        
    }
    
    //Rook / Queen Moves
    if (new_piece == 4 || new_piece == 5){
        //Getting four directions
        int temp = y;
        while (true){
            temp += 1;
            if (temp < 8){
                if (board[temp][x] == 0){
                    moves.push_back({temp,x,piece});
                } else if ((board[temp][x] <= 6) != color){
                    moves.push_back({temp,x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        temp = y;
        while (true){
            temp -= 1;
            if (temp > -1){
                if (board[temp][x] == 0){
                    moves.push_back({temp,x,piece});
                } else if ((board[temp][x] <= 6) != color){
                    moves.push_back({temp,x,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        temp = x;
        while (true){
            temp += 1;
            if (temp < 8){
                if (board[y][temp] == 0){
                    moves.push_back({y,temp,piece});
                } else if ((board[y][temp] <= 6) != color){
                    moves.push_back({y,temp,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        temp = x;
    
        while (true){
            temp -= 1;
            
            if (temp > -1){
                if (board[y][temp] == 0){
                    moves.push_back({y,temp,piece});
                } else if ((board[y][temp] <= 6) != color){
                    moves.push_back({y,temp,piece});
                    break;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }


    return moves;
    

}

std::vector<std::vector<int>> get_captures(int y, int x, std::vector<std::vector<int>> board){
    std::vector<std::vector<int>> moves = {};
    int piece = board[y][x];
    
    bool color = true;
    int new_piece = piece;
    if (piece > 6){
        new_piece = piece - 6;
        color = false;
    }
    //std::cout << "HERHE " << board[y][x] << "\n";
    //Pawn Moves
    if (new_piece == 1){
        if (color == true){
            if (y + 1 < 8){
                if (x - 1 > -1){
                    if (board[y + 1][x - 1] > 6){
                        moves.push_back({y+1,x-1,piece});
                    }   
                }
                if (x + 1 < 8){
                    if (board[y + 1][x + 1] > 6){
                        moves.push_back({y + 1, x +1,piece});
                    }
                }
            }         
        } else {
            if (y - 1 > -1){
                if (x - 1 > -1){
                    if (board[y - 1][x - 1] <= 6 && board[y -1 ][x - 1] != 0){
                        moves.push_back({y-1,x-1,piece});
                    }
                }
                if (x + 1 < 8){
                    if (board[y - 1][x + 1] <= 6 && board[y - 1][x + 1] != 0){
                        moves.push_back({y - 1, x +1,piece});
                    }
                } 
            }  
        }
    }
    
    //Knight Moves
    else if (new_piece == 2){
        if (y + 1 < 8){
            if (x + 2 < 8){
                if ((board[y + 1][x + 2] <= 6) != color && board[y+1][x+2] != 0){
                    moves.push_back({y+1,x+2,piece});
                }
            }
            if (x - 2 > -1){
                if ((board[y + 1][x - 2] <= 6) != color && board[y+1][x-2] != 0){
                    moves.push_back({y+1,x-2,piece});
                }
            }
        }
            
        if (y - 1 > -1){
            if (x + 2 < 8){
                if ((board[y - 1][x + 2] <= 6) != color && board[y-1][x+2] != 0){
                    moves.push_back({y-1,x+2,piece});
                }
            }
            if (x - 2 > -1){
                if ((board[y - 1][x - 2] <= 6) != color && board[y-1][x-2] != 0){
                    moves.push_back({y-1,x-2,piece});
                }   
            }
        }

        if (y + 2 < 8){
            if (x + 1 < 8){
                if ((board[y + 2][x + 1] <= 6) != color && board[y+2][x+1] != 0){
                    moves.push_back({y+2,x+1,piece});
                }
            }
            if (x- 1 > -1){
                if ((board[y + 2][x - 1] <= 6) != color && board[y+2][x-1] != 0){
                    moves.push_back({y+2,x-1,piece});
                }
            }
        }

        if (y - 2 > -1){
            if (x + 1 < 8){
                if ((board[y - 2][x + 1] <= 6) != color && board[y-2][x+1] != 0){
                    moves.push_back({y-2,x+1,piece});
                }
            }

            if (x - 1 > -1){
                if ((board[y - 2][x - 1] <= 6) != color && board[y-2][x-1] != 0){
                    moves.push_back({y-2,x-1,piece});
                }
            }
        }
        
    }
    
    //Bishop / Queen Moves
    else if (new_piece == 3 || new_piece == 5){
        int temp_x = x;
        int temp_y = y;
        //The four bishop directions
        while (true){
            temp_x += 1;
            temp_y += 1;
            if (temp_x < 8 && temp_y < 8){
                if (board[temp_y][temp_x] != 0){
                    if ((board[temp_y][temp_x] <= 6) != color){
                        moves.push_back({temp_y,temp_x,piece});
                        break;
                    } else {
                        break;
                    }            
                }
            } else{
                break;
            }
        }
        temp_x = x;
        temp_y = y;
        while (true){
            temp_x -= 1;
            temp_y += 1;
            if (temp_x > -1 && temp_y < 8){
                if (board[temp_y][temp_x] != 0){
                    if ((board[temp_y][temp_x] <= 6) != color){
                        moves.push_back({temp_y,temp_x,piece});
                        break;
                    } else {
                        break;
                    }            
                }
            } else{
                break;
            }
        }

        temp_x = x;
        temp_y = y;
        while (true){
            temp_x += 1;
            temp_y -= 1;
            if (temp_x <  8 && temp_y > -1){
                if (board[temp_y][temp_x] != 0){
                    if ((board[temp_y][temp_x] <= 6) != color){
                        moves.push_back({temp_y,temp_x,piece});
                        break;
                    } else {
                        break;
                    }            
                }
            } else{
                break;
            }
        }

        temp_x = x;
        temp_y = y;
        while (true){
            temp_x -= 1;
            temp_y -= 1;
            if (temp_x > -1 && temp_y > -1){
                if (board[temp_y][temp_x] != 0){
                    if ((board[temp_y][temp_x] <= 6) != color){
                        moves.push_back({temp_y,temp_x,piece});
                        break;
                    } else {
                        break;
                    }            
                }
            } else{
                break;
            }
        }
    }
    
    //King moves
    else if (new_piece == 6){

        if (y + 1 < 8){
            if (x + 1 < 8){
                if ((board[y + 1][x + 1] <= 6) != color && board[y+1][x+1] != 0){
                    moves.push_back({y+1,x+1,piece});
                }
            }
            if (x - 1 > -1){
                if ((board[y + 1][x- 1] <= 6) != color && board[y+1][x-1] != 0){
                    moves.push_back({y+1,x-1,piece});
                }
            }

            if ((board[y + 1][x] <= 6) != color && board[y+1][x] != 0){
                moves.push_back({y+1,x,piece});
            }
        } 

        if (y - 1 > -1){
            if (x + 1 < 8){
                if ((board[y - 1][x + 1] <= 6) != color && board[y-1][x+1] != 0){
                    moves.push_back({y-1,x+1,piece});
                }
            }
            if (x - 1 > -1){
                if ((board[y - 1][x- 1] <= 6) != color && board[y-1][x-1] != 0){
                    moves.push_back({y-1,x-1,piece});
                }
            }

            if ((board[y - 1][x] <= 6) != color && board[y-1][x] != 0){
                moves.push_back({y-1,x,piece});
            }
        }

        if (x + 1 < 8){
            if ((board[y][x + 1] <= 6) != color && board[y][x + 1] != 0){
                moves.push_back({y,x + 1,piece});
            }
        }

        if (x - 1 > -1){
            if ((board[y ][x - 1] <= 6) != color && board[y][x - 1] != 0){
                moves.push_back({y,x - 1,piece});
            }
        }
        
    }
    
    //Rook / Queen Moves
    if (new_piece == 4 || new_piece == 5){
        //Getting four directions
        int temp = y;
        while (true){
            temp += 1;

            if (temp < 8){
                if (board[temp][x] != 0){
                    if ((board[temp][x] <= 6) != color){
                        moves.push_back({temp,x,piece});
                        break;
                    } else {
                        break;
                    }
                }
            } else{
                break;
            }

        }
        temp = y;
        while (true){
            temp -= 1;

           if (temp > -1){
                if (board[temp][x] != 0){
                    if ((board[temp][x] <= 6) != color){
                        moves.push_back({temp,x,piece});
                        break;
                    } else {
                        break;
                    }
                }
            }
            else{
                break;
            }

        }

        temp = x;
        while (true){
            temp += 1;
            
            if (temp < 8){
                if (board[y][temp] != 0){
                    if ((board[y][temp] <= 6) != color){
                        moves.push_back({y,temp,piece});
                        break;
                    } else {
                        break;
                    }
                }
            } else{
                break;
            }
             

        }

        temp = x;
    
        while (true){
            temp -= 1;

            if (temp > -1){
                if (board[y][temp] != 0){
                    if ((board[y][temp] <= 6) != color){
                        moves.push_back({y,temp,piece});
                        break;
                    } else {
                        break;
                    }
                }
            }else{
                break;
            }
        }
    }
    
    return moves;
    

}

std::vector<std::vector<int>> order_moves(std::vector<std::vector<int>> moves, std::vector<std::vector<int>> board){
    std::vector<int> curr = {0,0,0};
    std::vector<std::vector<int>> return_moves(moves.size());
    std::vector<std::vector<int>> new_moves(moves.size() * 2);
    int start = moves.size();
    int end = moves.size();

    new_moves[start] = moves[0];
    for (int i = 1; i < moves.size(); i++){
        curr = moves[i];
        if (board[curr[0]][curr[1]] != 0){
            new_moves[start - 1] = curr;
            start -= 1;
        } else{
            new_moves[end + 1] = curr;
            end += 1;
        }
    }
    for (int i = start; i <= end; i++){
        return_moves[i - start] = new_moves[i];
    }
    return return_moves;
}

int eval(std::vector<std::vector<int>> board){
  
    int total = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] != 0){
                total += points[board[i][j]];
                if (board[i][j] > 6){
                    //King eval depends on stage of game
                    if (board[i][j] == 12){
                        total -= (maps[board[i][j] - 1][i][j])* (10 - (int)endgame_val);
                        total -= maps[12][i][j] * (int)endgame_val;
                    } else{
                        total -= (maps[board[i][j] - 1][i][j]);
                        //total -= get_moves(i,j,board).size();
                    }       
                                 
                    
                } else {
                    //King eval depends on stage of game
                    if (board[i][j] == 6){
                        total += (maps[board[i][j] - 1][i][j])* (10 - (int)endgame_val);
                        total += maps[12][i][j] * (int)endgame_val;
                    } else{
                        total += maps[board[i][j] - 1][i][j];
                        //total += get_moves(i,j,board).size();
                    }
                    
                }
                
            }
        }
    }
    return total;

}


int search_captures(std::vector<std::vector<int>> board, int maximum = -100000, int minimum = 100000, int side = 0){
    int count = 0;  
    int total = 0;
    int returned = 0;
    int old_val =0;
    int curr_piece;
    int new_piece;
    if (side - stop_depth == check_depth){
        possibilities += 1;
        return eval(board);
    }
    std::vector<std::vector<int>> moves;
    //If Black
    if (side% 2 == 0){
       
        total = 100000;
        
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                //Only Checking For Black
                if (board[i][j] > 6){
                    curr_piece = board[i][j];
                    moves = get_captures(i,j,board);
                    if (moves.size() == 0){
                        continue;
                    }
                   
                    count += 1;

                    //Looping through capture moves
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        new_piece = moves[k][2];
                        old_val = board[moves[k][0]][moves[k][1]];
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                       
                        //Recursion
                        if (old_val % 6 == 0){
                            return -100000;
                        }
                        returned = search_captures(board, maximum, total, side + 1);
                    
                        if (returned < total){
                            total = returned;  
                        }
                        //Alpha-Beta Pruning
                        
                        if (total < maximum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;
                    }
                }
            }
        }   
   
        if (count == 0){
            possibilities += 1;
            return eval(board);
        }
        if (total == 100000){
            return 0;
        }
        return total;
    

    //If White
    } else{
        total = -100000;

        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                //Only Checking For White
                if (board[i][j] <= 6 && board[i][j] != 0){
                    moves = get_captures(i,j,board);
                    curr_piece = board[i][j];
                    if (moves.size() == 0){
                        continue;
                    }
                   
                    count += 1;
                    //Loop through capture moves
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        new_piece = moves[k][2];
                        old_val = board[moves[k][0]][moves[k][1]];
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                        

                        //Recursion
                        if (old_val % 6 == 0){
                            return 100000;
                        }
                        returned = search_captures(board, total, minimum, side + 1);
                      
                        if (returned > total){
                            total = returned;
                        }
                        //Alpha-Beta Pruning
                        
                        if (total > minimum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;
                    }
                }
            }
        }     
     
        if (count == 0){
            possibilities += 1;
            return eval(board);
        }
        if (total == -100000){
            return 0;
        }
        return total;
    }
}

//Main Func
int min_max(std::vector<std::vector<int>> board, int maximum = -100000, int minimum = 100000, int depth = 0){
    if (depth == stop_depth){
        //possibilities += 1;
   
        //std::cout << possibilities << "\n";
        
        
        return search_captures(board,maximum,minimum,depth);
    }

    int total = 0;
    std::vector<std::vector<int>> moves= {};
    int old_val = 0;
    int returned = 0;
    int new_piece = 0;
    int curr_piece = 0;
    //If Black
    if (depth% 2 == 0){
       
        total = 100000;
     
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                //Only Checking For Black
                if (board[i][j] > 6){
                    curr_piece = board[i][j];
                    moves = get_moves(i,j,board);
                   // std::cout << curr_piece << '\n';
                    //moves = order_moves(moves,board);

                    //First loop through "good" moves
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        //std::cout << "LEN " << moves[k].size() << "\n";
                        //std::cout << moves[k][0] << " " << moves[k][1] << "\n";
                        new_piece = moves[k][2];
                        
                        //std::cout << "NEW PIECE: " << new_piece << "\n";
                        old_val = board[moves[k][0]][moves[k][1]];
                        if (old_val == 0){
                            continue;
                        }
                        if (depth == 0){
                            std::cout << k << " - " << possibilities << '\n';
                        }
                        
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                       
                        //Recursion
                        if (old_val % 6 == 0){
                            all_comp_moves[depth] = {i * 8 + j,  moves[k][0] * 8 + moves[k][1],new_piece};
                            return -100000;
                        }
                        returned = min_max(board, maximum, total, depth + 1);
                    
                        if (returned < total){
                            total = returned;  
                            all_comp_moves[depth] = {i * 8 + j,  moves[k][0] * 8 + moves[k][1],new_piece}; 
                        }
                        //Alpha-Beta Pruning
                        if (total < maximum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;
                    

                    }


                    //Second Loop through everything else
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        new_piece = moves[k][2];
                        old_val = board[moves[k][0]][moves[k][1]];
                        
                        if (old_val != 0){
                            continue;
                        }
                        if (depth == 0){
                            std::cout << k << " - " << possibilities << '\n';
                        }
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                  
                        //Recursion
                        returned = min_max(board, maximum, total, depth + 1);
                       
                        if (returned < total){
                            total = returned;
                            all_comp_moves[depth] = {i * 8 + j,  moves[k][0] * 8 + moves[k][1],new_piece};
                           
                            
                        }
                        //Alpha-Beta Pruning
                        if (total < maximum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;

                    }

                }

            }
        }        
        if (total == 100000){
            return 0;
        }
        return total;
    

    //If White
    } else{
        total = -100000;

        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                //Only Checking For White
                if (board[i][j] <= 6 && board[i][j] != 0){
                    curr_piece = board[i][j];
                    moves = get_moves(i,j,board);
                    //moves = order_moves(moves,board);
                    //First loop through "good" moves
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        new_piece = moves[k][2];
                        old_val = board[moves[k][0]][moves[k][1]];
                        if (old_val == 0){
                            continue;
                        }
                       
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                        

                        //Recursion
                        if (old_val % 6 == 0){
                            all_comp_moves[depth] = {i * 8 + j,  moves[k][0] * 8 + moves[k][1],new_piece};
                            return 100000;
                        }
                        returned = min_max(board, total, minimum, depth + 1);
                      
                        if (returned > total){
                            total = returned;
                            all_comp_moves[depth] = {i * 8 + j,  moves[k][0] * 8 + moves[k][1],new_piece};
                        }
                        //Alpha-Beta Pruning
                        if (total > minimum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;
                       

                    }
                    //Second loop for everything else
                    for (int k = 0; k < moves.size(); k++){
                        
                        //Making Move
                        new_piece = moves[k][2];
                        old_val = board[moves[k][0]][moves[k][1]];
                        
                        if (old_val != 0){
                            continue;
                        }
                       
                        //std::cout << k << " " << moves.size() << "  " << moves[k].size() << "\n";
                        board[moves[k][0]][moves[k][1]] = new_piece;
                        board[i][j] = 0;
                        

                        //Recursion
                        returned = min_max(board, total, minimum, depth + 1);
                       
                        if (returned > total){
                            total = returned;
                            all_comp_moves[depth] = {i * 8 + j, moves[k][0] * 8 + moves[k][1],new_piece};
                        }
                        //Alpha-Beta Pruning
                        if (total > minimum){
                            return total;
                        }

                        //Resetting move
                        board[i][j] = curr_piece;
                        board[moves[k][0]][moves[k][1]] = old_val;

                    }
                }

            }
        }      
        if (total == -100000){
            return 0;
        }  
        return total;
    }


}


//Setup Funcs
std::vector<int> setup_pieces(std::vector<int> pieces){
    for (int i = 0; i < 2; i++){
        for (int j =0 ; j < 8; j++){
            pieces.push_back(i * 8 + j);
            pieces.push_back((7 - i) * 8 + j);
        }
    }
    return pieces;
}

std::vector<std::vector<int>> setup_board(std::vector<std::vector<int>> board){
    board[0][0] = 4;
    board[0][1] = 2;
    board[0][2] = 3;
    board[0][3] = 5;
    board[0][4] = 6;
    board[0][5] = 3;
    board[0][6] = 2;
    board[0][7] = 4;
    for (int i = 0; i < 8; i++){
        board[1][i] = 1;
    }

    board[7][0] = 10;
    board[7][1] = 8;
    board[7][2] = 9;
    board[7][3] = 11;
    board[7][4] = 12;
    board[7][5] = 9;
    board[7][6] = 8;
    board[7][7] = 10;
    for (int i = 0; i < 8; i++){
        board[6][i] = 7;
    }

    return board;
    
}

std::vector<std::vector<std::vector<int>>> setup_maps(std::vector<std::vector<std::vector<int>>> maps){
    std::vector<std::vector<int>> empty_map = {};
    std::vector<int> row(8,0);
    for (int i = 0; i < 8; i++){
        empty_map.push_back(row);
    }

    std::vector<std::vector<int>> white_pawn_map = {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {10,10,10,10,10,10,10,10},
        {10,10,20,20,20,20,10,10},
        {20,20,20,30,30,20,20,20},
        {30,30,40,40,40,40,30,30},
        {40,50,50,50,50,50,50,40},
        {60,60,60,60,60,60,60,60}
    };

    std::vector<std::vector<int>> black_pawn_map = {
        {60,60,60,60,60,60,60,60},
        {40,50,50,50,50,50,50,40},
        {30,30,40,40,40,40,30,30},
        {20,20,20,30,30,20,20,20},
        {10,10,20,20,20,20,10,10},
        {10,10,10,10,10,10,10,10},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}      
    };

    std::vector<std::vector<int>> knight_map = {
        {0,0,0,0,0,0,0,0},  
        {0,10,10,10,10,10,10,0},  
        {0,10,20,20,20,20,10,0},  
        {0,10,20,30,30,20,10,0},  
        {0,10,20,30,30,20,10,0},  
        {0,10,20,20,20,20,10,0},  
        {0,10,10,10,10,10,10,0},
        {0,0,0,0,0,0,0,0}      
    };
    
    std::vector<std::vector<int>> bishop_map = {
        {10,0,0,0,0,0,0,10},
        {0,20,10,10,10,10,20,0},
        {0,10,30,20,20,30,10,0},
        {0,10,20,30,30,20,10,0},
        {0,10,20,30,30,20,10,0},
        {0,10,30,20,20,30,10,0},
        {0,20,10,10,10,10,20,0},
        {10,0,0,0,0,0,0,10}
    };

    std::vector<std::vector<int>> white_rook_map = {
        {0,0,10,20,20,10,0,0},
        {0,0,10,20,20,10,0,0},
        {10,10,20,20,20,20,10,10},
        {0,0,10,10,10,10,0,0},
        {0,0,0,10,10,0,0,0},
        {10,10,10,10,10,10,10,10},
        {20,20,20,30,30,20,20,20},
        {0,0,0,0,0,0,0,0}
    };

    std::vector<std::vector<int>> black_rook_map = {
        {0,0,0,0,0,0,0,0},
        {20,20,20,30,30,20,20,20},
        {10,10,10,10,10,10,10,10},
        {0,0,0,10,10,0,0,0},
        {0,0,10,10,10,10,0,0},
        {10,10,20,20,20,20,10,10},
        {0,0,10,20,20,10,0,0},
        {0,0,10,20,20,10,0,0}
    };

    std::vector<std::vector<int>> white_king_map = {
        {3,2,1,0,0,1,2,3},
        {1,0,0,0,0,0,0,1},
        {0,0,-1,-1,-1,-1,0,0},
        {-1,-1,-1,-2,-2,-1,-1,-1},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,1},
        {3,2,1,0,0,1,2,3}
    };

    std::vector<std::vector<int>> black_king_map = {
        {3,2,1,0,0,1,2,3},
        {1,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-1,-1,-1,-2,-2,-1,-1,-1},
        {0,0,-1,-1,-1,-1,0,0},
        {1,0,0,0,0,0,0,1},
        {3,2,1,0,0,1,2,3}      
    };

    std::vector<std::vector<int>> endgame_king_map = {
        {0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,0},
        {0,1,2,2,2,2,1,0},
        {0,1,2,3,3,2,1,0},
        {0,1,2,3,3,2,1,0},
        {0,1,2,2,2,2,1,0},
        {0,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0}
    };



  
    maps.push_back(white_pawn_map);
    maps.push_back(knight_map);
    maps.push_back(bishop_map);
    maps.push_back(white_rook_map);
    maps.push_back(empty_map);
    maps.push_back(white_king_map);
    maps.push_back(black_pawn_map);
    maps.push_back(knight_map);
    maps.push_back(bishop_map);
    maps.push_back(black_rook_map);
    maps.push_back(empty_map);
    maps.push_back(black_king_map);
    maps.push_back(endgame_king_map);
    return maps;
}

int main(){
    //Initializing point system
    points[1] = 100;
    points[2] = 290;
    points[3] = 310;
    points[4] = 500;
    points[5] = 900;
    points[6] = 1000000;
    points[7] = -100;
    points[8] = -290;
    points[9] = -310;
    points[10] = -500;
    points[11] = -900;
    points[12] = -1000000;

    //Initializing characters
    characters[0] = "  ";
    characters[1] = "Wp";
    characters[2] = "Wk";
    characters[3] = "Wb";
    characters[4] = "Wr";
    characters[5] = "WQ";
    characters[6] = "WK";
    characters[7] = "Bp";
    characters[8] = "Bk";
    characters[9] = "Bb";
    characters[10] = "Br";
    characters[11] = "BQ";
    characters[12] = "BK";

    //Initializing rows
    rows['a'] = 0;
    rows['b'] = 1;
    rows['c']  = 2;
    rows['d'] = 3;
    rows['e'] = 4;
    rows['f'] = 5;
    rows['g'] = 6;
    rows['h'] = 7;
    rows['1'] = 0;
    rows['2'] = 1;
    rows['3'] = 2;
    rows['4'] = 3;
    rows['5'] = 4;
    rows['6'] = 5;
    rows['7'] = 6;
    rows['8'] = 7;


    std::vector<std::vector<int>> board;
  
    
    std::vector<int> temp(8);
    for (int i = 0; i < 8; i++){
        board.push_back(temp);
    }
  

   
  
    board = setup_board(board);
    maps = setup_maps(maps);
 
    
    display(board);
    int eval = 0;
    int player_end = 0;
    std::vector<int> player_piece(2,0);
    std::vector<int> player_destination(2,0);
    std::vector<int> comp_piece(2,0);
    std::vector<int> comp_destination(2,0);
    std::vector<int> comp_move(2,0);

    std::string player_move = "";
   
    std::cout << "White or black? ";
    std::cin >> player_move;
    
    if (player_move == "black"){
        white_or_black = 1;
        while (true){
            //Getting Comp Move
            auto begin = std::chrono::high_resolution_clock::now();
            eval = min_max(board,-100000,100000,1);
            comp_move = all_comp_moves[white_or_black];
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            comp_piece = {(comp_move[0] - (comp_move[0] % 8)) / 8, comp_move[0] % 8};
            comp_destination = {(comp_move[1] - (comp_move[1] % 8)) / 8, comp_move[1] % 8};

            //Making Comp Move
            if (board[comp_destination[0]][comp_destination[1]] != 0 && board[comp_destination[0]][comp_destination[1]] % 6 != 1){
                endgame_val += 0.5;
                
            }
            board[comp_destination[0]][comp_destination[1]] = comp_move[2];
            board[comp_piece[0]][comp_piece[1]] = 0;
            

            //Outputting
            display(board);
            std::cout << "\nComp Move: " << comp_move[0] << " - " << comp_move[1] << "\n";
            std::cout << "Comp Eval: " << eval << "\n";
            std::cout << "Possibilities: " << possibilities << "\n";
            std::cout << "Time Taken(milliseconds): " << elapsed.count() << '\n';

            //Getting Player Move
            possibilities = 0;
            while (true){

                std::cout << "\nEnter your move: ";
                std::cin >> player_move;
                if (player_move == "stop"){
                    break;
                }
                player_piece = {rows[player_move[1]], rows[player_move[0]]};
                player_destination = {rows[player_move[3]],rows[player_move[2]]};

                //Making Player Move
                if (board[player_destination[0]][player_destination[1]] != 0 && board[player_destination[0]][player_destination[1]] % 6 != 1){
                    endgame_val += 0.5;
                    if (endgame_val > 10){
                        endgame_val = 10;
                    }
                }
                player_end = board[player_piece[0]][player_piece[1]];
                if (player_end == 7 && player_piece[0] == 1){
                    std::cout << "Promote to: ";
                    std::cin >> player_end;
                }
                board[player_destination[0]][player_destination[1]] = player_end;
                board[player_piece[0]][player_piece[1]] = 0;     
            }            
        }
    } else{
        white_or_black = 0;
        stop_depth -= 1;
    
        while (true){
            //Getting Player Move
            possibilities = 0;
            while (true){

                std::cout << "\nEnter your move: ";
                std::cin >> player_move;
                if (player_move == "stop"){
                    break;
                }
                player_piece = {rows[player_move[1]], rows[player_move[0]]};
                player_destination = {rows[player_move[3]],rows[player_move[2]]};

                //Making Player Move
                if (board[player_destination[0]][player_destination[1]] != 0 && board[player_destination[0]][player_destination[1]] % 6 != 1){
                    endgame_val += 0.5;
                    if (endgame_val > 10){
                        endgame_val = 10;
                    }
                }
                player_end = board[player_piece[0]][player_piece[1]];
                if (player_end == 1 && player_piece[0] == 6){
                    std::cout << "Promote to: ";
                    std::cin >> player_end;
                }
                board[player_destination[0]][player_destination[1]] = player_end;
                board[player_piece[0]][player_piece[1]] = 0;     
            }
            //Getting Comp Move
            auto begin = std::chrono::high_resolution_clock::now();
            eval = min_max(board);
            
            comp_move = all_comp_moves[white_or_black];
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            comp_piece = {(comp_move[0] - (comp_move[0] % 8)) / 8, comp_move[0] % 8};
            comp_destination = {(comp_move[1] - (comp_move[1] % 8)) / 8, comp_move[1] % 8};

            //Making Comp Move
            if (board[comp_destination[0]][comp_destination[1]] != 0 && board[comp_destination[0]][comp_destination[1]] % 6 != 1){
                endgame_val += 0.5;
            }
            board[comp_destination[0]][comp_destination[1]] = comp_move[2];
            board[comp_piece[0]][comp_piece[1]] = 0;


            //Outputting
            display(board);
            std::cout << "\nComp Move: " << comp_move[0] << " - " << comp_move[1] << "\n";
            std::cout << "Comp Eval: " << eval << "\n";
            std::cout << "Possibilities: " << possibilities << "\n";
            std::cout << "Time Taken(milliseconds): " << elapsed.count() << '\n';
            

              
    }
    }

    /*
    
    while (true){
        //Getting Player Move
        possibilities = 0;
        std::cout << "\nEnter your move: ";
        std::cin >> player_move;
        player_piece = {rows[player_move[1]], rows[player_move[0]]};
        player_destination = {rows[player_move[3]],rows[player_move[2]]};

        //Making Player Move
        board[player_destination[0]][player_destination[1]] = board[player_piece[0]][player_piece[1]];
        board[player_piece[0]][player_piece[1]] = 0;
        
        //Getting Comp Move
        auto begin = std::chrono::high_resolution_clock::now();
        eval = min_max(board);
        comp_move = all_comp_moves[0];
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        comp_piece = {(comp_move[0] - (comp_move[0] % 8)) / 8, comp_move[0] % 8};
        comp_destination = {(comp_move[1] - (comp_move[1] % 8)) / 8, comp_move[1] % 8};

        //Making Comp Move
        board[comp_destination[0]][comp_destination[1]] = board[comp_piece[0]][comp_piece[1]];
        board[comp_piece[0]][comp_piece[1]] = 0;

        //Outputting
        display(board);
        std::cout << "\nComp Move: " << comp_move[0] << " - " << comp_move[1] << "\n";
        std::cout << "Comp Eval: " << eval << "\n";
        std::cout << "Possibilities: " << possibilities << "\n";
        std::cout << "Time Taken(milliseconds): " << elapsed.count() << '\n';

    }*/
 
    
    std::cout << "\n\n";
    

    

}   
