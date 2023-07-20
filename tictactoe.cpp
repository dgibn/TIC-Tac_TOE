#include <bits/stdc++.h>
using namespace std;

#define SIDE 3

#define COMPUTER 0
#define HUMAN 1
#define COMPUTERMOVE 'X'

#define HUMANMOVE 'O'

void showBoard(char board[][SIDE]){
    cout << "\t "<< board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t"<<"-----------"<<endl;
    cout << "\t "<< board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t"<<"-----------"<<endl;
    cout << "\t "<< board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void showInstructions(){
    cout << "\n" << "Choose a cell numbered from 1-9 as below and play: Good Luck !!!"<<endl;
    cout << "\t "<< 1 << " | " << 2 << " | " << 3 << endl;
    cout << "\t"<<"-----------"<<endl;
    cout << "\t "<< 4 << " | " << 5 << " | " << 6 << endl;
    cout << "\t"<<"-----------"<<endl;
    cout << "\t "<< 7 << " | " << 8 << " | " << 9<< endl;
}

void initialise(char board[][SIDE]){
    for (int i=0;i<SIDE;i++){
        for (int j=0;j<SIDE;j++){
            board[i][j]='*';
        }
    }
}

void declareWinner(int player){
    if (player==COMPUTER){
        cout<< "AI RULES!!!"<<endl;
    }
    else{
        cout << "HUMANS ROCK!!" << endl;
    }
}


bool diagonal(char board[][SIDE]){
    if (board[0][0]!='*' && board[1][1]==board[2][2] && board[2][2]==board[0][0]){
        return true;
    }
    if (board[0][2]!='*' && board[1][1]==board[2][0] && board[2][0]==board[0][2]){
        return true;
    }
    return false;
}

bool row(char board[][SIDE]){
    if (board[0][0]!='*' && board[0][1]==board[0][2] && board[0][2]==board[0][0]){
        return true;
    }
    if (board[1][2]!='*' && board[1][1]==board[1][0] && board[1][0]==board[1][2]){
        return true;
    }
    if (board[2][2]!='*' && board[2][1]==board[2][0] && board[2][0]==board[2][2]){
        return true;
    }

    return false;
}

bool column(char board[][SIDE]){
    if (board[0][0]!='*' && board[1][0]==board[2][0] && board[2][0]==board[0][0]){
        return true;
    }
    if (board[0][1]!='*' && board[0][1]==board[2][1] && board[2][1]==board[1][1]){
        return true;
    }
    if (board[0][2]!='*' && board[1][2]==board[2][2] && board[0][2]==board[2][2]){
        return true;
    }

    return false;
}

bool gameOver(char board[][SIDE]){
    return (row(board) || column(board) || diagonal(board));
}

int minimax(char board[][SIDE],int depth,bool isAI){
    int score=0;
    int best=0;

    if (gameOver(board)==true){
        if (isAI==true){
            return -10;
        }
        if (isAI==false){
            return 10;
        }
    }
    else{
        if (depth<9){
            if (isAI==true){
                best=INT_MIN;
                for (int i=0;i<SIDE;i++){
                    for (int j=0;j<SIDE;j++){
                        if (board[i][j]=='*'){
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,depth+1,false);
                            board[i][j]='*';
                            if (score>best){
                                best=score;
                            }
                        }
                    }
                }
                return best;    
            }
            else{
                best=INT_MAX;
                for (int i=0;i<SIDE;i++){
                    for (int j=0;j<SIDE;j++){
                        if (board[i][j]=='*'){
                            board[i][j]=HUMANMOVE;
                            score=minimax(board,depth+1,true);
                            board[i][j]='*';
                            if (score<best){
                                best=score;
                            }
                        }
                    }
                } 
                return best;
            } 
        }
        else{
            return 0;
        }
    }
    return 0;
}

int bestMove(char board[][SIDE],int move){
    int x=-1,y=-1,best=INT_MIN,score=0;
    
    for (int i=0;i<SIDE;i++){
        for (int j=0;j<SIDE;j++){
            if (board[i][j]=='*'){
                board[i][j]=COMPUTERMOVE;
                score=minimax(board,move+1,false);
                board[i][j]='*';
                if (score>best){
                    best=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
}


void playTicTacToe(int player){ 
    char board[SIDE][SIDE];

    int move=0,x=0,y=0; 
    initialise(board);

    showInstructions();

    while (gameOver(board)==false && move!=SIDE*SIDE){

        int number;
        
        if (player==COMPUTER){
            number=bestMove(board,move);
            x=number/SIDE;
            y=number%SIDE;

            board[x][y]=COMPUTERMOVE;

            cout << "Computer has played "<<COMPUTERMOVE<<" in cell "<< number+1<<endl;
            showBoard(board);
            move++;
            player=HUMAN;
        }

        else if (player==HUMAN){
            cout <<  "you can play in the following tiles :"<<endl;

            for (int i=0;i<SIDE;i++){
                for (int j=0;j<SIDE;j++){
                    if (board[i][j]=='*'){
                        cout << i*3 +j+1;
                    }   
                }
            }
            cout << endl;
            cout << "Enter your move:";
            cin >> number;

            cout << endl;
            number--;
            x=number/SIDE;
            y=number%SIDE;

            if (board[x][y]=='*' && number < 9 && number>=0){

                board[x][y]=HUMANMOVE;

                cout << "You have put "<< HUMANMOVE << " in cell "<< number+1<< endl;;
                showBoard(board);
                move++;
                player=COMPUTER;
            }

            else if (board[x][y]!='*' && number< 9 && number>=0){
                cout << "Occupied!"<<endl;
            }
            else if (number<0 || number>8){
                cout<< "Invalid!"<<endl;
            }
        }
    }

    if (gameOver(board)==false && move==SIDE*SIDE){
        cout << "Draw!" <<endl;
    }

    else{
        if (player==HUMAN){
            player=COMPUTER;
        }
        else{
            player=HUMAN;
        }

        declareWinner(player);
    }
}



int main(){

    cout << "----------------------------------------------"<<endl;
    cout << "                Tic Tac Toe"<< endl;
    cout << "----------------------------------------------"<< endl;
    
    char cont='y';

    while (cont=='y'){
        char choice;

        cout << "Do you want to start first <y/n> ? :";
        cin >> choice;

        if (choice=='n'){
            playTicTacToe(COMPUTER);
        }

        else if (choice=='y'){
            playTicTacToe(HUMAN);
        }

        else{
            cout << "Invalid Option" <<endl;
        }

        cout << "Continue ?? <y/n>:";
        cin >> cont;
        cout << endl;
    }
    return 0;
}
