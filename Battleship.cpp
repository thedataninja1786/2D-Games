#include <iostream> 
#include <vector> 
#include <string> 
using namespace std; 

vector<vector<int>> board; 

bool check_winner(vector<vector<int>> board){
    int total = 0; 
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            total += board[i][j];
        }
    }
    cout << total << endl; 
    if(total != 0){
        return false;
    }
    else return true;
}


void show_board(vector<vector<int>> board){
    for(int i = 0; i < board.size(); i++){
        for(int j =  0; j <  board[i].size(); j++){
            cout << "  " << board[i][j]; 
        }
        cout << endl;
    }
}

vector<vector<int>> populate_board(vector<vector<int>> board,int x, int y, char direction, int len){
    if ((direction == 'v') && (x + len < 6) && (y < 6 && y >= 0)){
        for(int i = 0; i < len; i++){
            board[x+i][y] = 1; 
        }
    }
    else if((direction == 'h') && (y + len < 6) && (x < 6 && x >= 0)){
        for(int i = 0; i < len; i++){
            board[x][y+i] = 1;
        }   
    }
    else{ 
        string ship; 
        cout << "Error!" << endl;
        cout << "Position at row " << x << " and column " << y << " is not valid for the " << direction << "direction.\n";
        cout << "Please choose another position!" << endl; 
        cin >> ship; 
        x = ship[0] - 48; y = ship[1] - 48;
        return populate_board(board,x,y,direction,len);
    }
    return board;
}

vector<vector<int>> create_player_board(){
    vector<int> tmp = {0,0,0,0,0,0};
    vector<vector<int>> board; 
    int i = 0;
    while(i < 6){
        board.push_back(tmp); 
        i += 1;
    }
    
    string ship1; string ship2; 
    char dir1; char dir2;
    std::cout << "There is a 6x6 board. \nPlease select the position of your battleships!" << std::endl;
    cout << "You will need to allocate either horrizonatlly or vertically a 1x4 ship and a 1x2 ship." << endl;
    cout << "Please enter the coordinates (x,y) of the first ship" << endl;
    std::cin >> ship1;
    cout << "Please enter the direction of the first ship. Choose h for horizontal, v for vertical" << endl;
    cin >> dir1; 
    int ship1_x = ship1[0] - 48; int ship1_y = ship1[1] - 48;
    board = populate_board(board,ship1_x, ship1_y, dir1, 4);
    cout << "Please enter the coordinates (x,y) of the second ship" << endl; 
    std::cin >> ship2;
    cout << "Please enter the direction for the second ship. Choose h for horizontal, v for vertical" << endl; 
    cin >> dir2; 
    int ship2_x = ship2[0] - 48; int ship2_y = ship2[1] - 48;
    board = populate_board(board,ship2_x, ship2_y, dir2, 2);
    return board;
}

vector<vector<int>> player_move(vector<vector<int>> board,int x, int y){
    // takes the board of the other player and handles the move of the current player
    if(board[x][y] == 1){
        cout << "Hit" << endl; 
        board[x][y] = 0;
    }
    else cout << "Miss!" << endl;
    return board; 
}


int main(){
    string move_p1; string move_p2; 
    vector<vector<int>> player_board_1;
    vector<vector<int>> player_board_2; 
    player_board_1 = create_player_board(); 
    show_board(player_board_1);
    player_board_2 = create_player_board(); 
    show_board(player_board_2);
    while(true){
        cout << "Player 1 enter your move!" << endl; 
        cin >> move_p1; 
        int move_p1_x = move_p1[0] - 48; 
        int move_p1_y = move_p1[1] - 48; 
        player_board_2 = player_move(player_board_2,move_p1_x,move_p1_y);
        
        cout << "Player two enter your move!" << endl; 
        cin >> move_p2; 
        int move_p2_x = move_p2[0] - 48; 
        int move_p2_y = move_p2[1] - 48; 
        player_board_1 = player_move(player_board_1,move_p2_x,move_p2_y);
        show_board(player_board_1);
        
        if(check_winner(player_board_2) == 1){
            cout << "Player 1 wins!" << endl; 
            cout << "Player 1 board:" << endl; 
            show_board(player_board_1);
            break; 
        }
        if(check_winner(player_board_1) == 1){
            cout << "Player 2 wins!" << endl; 
            cout << "Player 2 board:" << endl; 
            show_board(player_board_2);
            break; 
        }
    }
}
