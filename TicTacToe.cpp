#include <iostream> 
#include <cstdlib>
#include <time.h>
#include <algorithm> 
#include <string> 
#include <vector> 
#include <map> 
using namespace std; 

// player 1 plays x and player 2 plays 0
vector<int> moves = {};
vector<vector<char>> board = {
                             {'-','-','-'},
                             {'-','-','-'},
                             {'-','-','-'}
                             }; 
                             

vector<vector<char>> clear_board(){
    return   {{'-','-','-'},
             {'-','-','-'},
             {'-','-','-'}
             }; 
}                             


float pick_random_player(){
    srand(time(NULL));
    return (rand() % 2);
}

bool check_rows(){
    for(int i = 0; i < board.size();i++){
        if((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && board[i][1] != '-'){
          return true;
        }
    }
    return false;
}

string check_valid_move(string choice, vector<int> moves){
    int tmp = stoi(choice);
    if(std::count(moves.begin(),moves.end(),tmp)){
        cout << choice << " is already occupied!\n Please choose another position!";
        cin >> choice;
        check_valid_move(choice,moves);
    }
    return choice;
}

bool check_cols(){
    for(int j = 0; j < board.size(); j++){
        if((board[0][j] == board[1][j]) && (board[1][j] == board[2][j]) && board[1][j] != '-'){
            return true; 
        }
    }
    return false;
}

bool check_diagonals(){
    if((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && board[1][1] != '-') return true;
    if((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && board[1][1] != '-') return true;
    return false;
}

bool check_win(){
    if(check_rows() + check_cols() + check_diagonals() > 0) return true; 
    return false;
}

void draw_board(){
    for(int i = 0; i < board.size(); i++){
    cout << endl;
    for(int j = 0; j < board[i].size(); j++){
        if(j % 2 == 0 && j != 0){
            cout << "  " << board[i][j] << endl; 
        }
        else cout << "  " << board[i][j]; 
    }
  }
}

void move(float player){
    cout << "Player " << player << " please choose the position you would like to play!\n";
    char symbol; 
    if(player == 1){
        symbol = 'x';
    }
    else{
        symbol = '0';
    }
    string choice; 
    cin >> choice;
    choice = check_valid_move(choice, moves);
    int r = choice[0] - 48; int c = choice[1] - 48;
    board[r][c] = symbol;
    moves.push_back(stoi(choice));
}

int main(){
int ties = 0; 
map<int,int> score;
score.insert(pair<int,int>(1,0));
score.insert(pair<int,int>(2,0));

while(true){
    moves.clear(); 
    board = clear_board();
    vector<int> players = {1,2}; 
    float first_player = players[pick_random_player()];
    players.erase(std::remove(players.begin(),players.end(),first_player),players.end());
    float second_player = players[0];
    cout << "Player " << first_player << " begins!" << endl;
    float i = 0;  
    while(i <= 9){
        move(first_player);
        draw_board(); 
        if(check_win()){
           cout << "Player " << first_player << " wins!"<< endl;
           score[first_player] += 1;
           break;
        }  
        i += 1;
        
        if(i == 9){
            cout << "It's a tie!";
            ties += 1; 
            break; 
        }
        
        move(second_player);
        draw_board(); 
        if(check_win()){
           cout << "Player " << second_player << " wins!"<< endl;   
           score[second_player] += 1;
           break; 
        }  
        i += 1;
    }
    cout << "There are " << score[1] << " player_1 win(s), " << score[2] << " player_2 win(s) and " << ties << " ties." << endl;
    cout << "Press y to play again, anything else to quit!" << endl; 
    char user_input; 
    cin >> user_input; 
    if(user_input != 'y'){
        break; 
    }
  }
}


