#pragma GCC optimize ("O3")

#include<bits/stdc++.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

char board[7][8], maximiser, minimiser;
int MAXDEPTH;
void print(){
	for(int i=1;i<=6;i++){
		printf("|");
		for(int j=1;j<=7;j++){
			printf(" %c |", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
bool nomovesleft(){
	for(int i=1;i<=7;i++){
		if(board[1][i]=='_'){
			return false;
		}
	}
	return true;
}
bool wins(char c){
	// Horizontal
	for(int i=1;i<=6;i++){
		for(int j=1;j<=4;j++){
			if(board[i][j]==c && board[i][j+1]==c && board[i][j+2]==c && board[i][j+3]==c){
				return true;
			}
		}
	}

	// Vertical
	for(int j=1;j<=7;j++){
		for(int i=1;i<=3;i++){
			if(board[i][j]==c && board[i+1][j]==c && board[i+2][j]==c && board[i+3][j]==c){
				return true;
			}
		}
	}	

	// Diagonal
	for(int i=1;i<=3;i++){
		for(int j=1;j<=4;j++){
			if(board[i][j]==c && board[i+1][j+1]==c && board[i+2][j+2]==c && board[i+3][j+3]==c){
				return true;
			}	
		}
	}
	for(int i=1;i<=3;i++){
		for(int j=7;j>=4;j--){
			if(board[i][j]==c && board[i+1][j-1]==c && board[i+2][j-2]==c && board[i+3][j-3]==c){
				return true;
			}	
		}
	}

	return false;
}
void Insert(int col, char c){
	for(int i=6;i>=1;i--){
		if(board[i][col]=='_'){
			board[i][col]=c;
			return;
		}
	}
}
void Remove(int col){
	for(int i=1;i<=6;i++){
		if(board[i][col]!='_'){
			board[i][col]='_';
			return;
		}
	}	
}
int count2s(char c){
	// Horizontal
	int count=0;
	for(int i=1;i<=6;i++){
		for(int j=1;j<=6;j++){
			if(j>1 && board[i][j-1]=='_' && board[i][j]==c && board[i][j+1]==c){
				count++;
			}
			else if(j<6 && board[i][j]==c && board[i][j+1]==c && board[i][j+2]=='_'){
				count++;
			}
		}
	}

	// Vertical
	for(int j=1;j<=7;j++){
		for(int i=2;i<=5;i++){
			if(board[i-1][j]=='_' && board[i][j]==c && board[i+1][j]==c){
				count++;
			}
		}
	}

	// Diagonal
	for(int i=1;i<=5;i++){
		for(int j=1;j<=6;j++){
			if(j>1 && i>1 && board[i-1][j-1]=='_' && board[i][j]==c && board[i+1][j+1]==c){
				count++;
			}
			else if(j<6 && i<5 && board[i][j]==c && board[i+1][j+1]==c && board[i+2][j+2]=='_'){
				count++;
			}
		}
	}
	for(int i=1;i<=5;i++){
		for(int j=7;j>=2;j--){
			if(j<7 && i>1 && board[i-1][j+1]=='_' && board[i][j]==c && board[i+1][j-1]==c){
				count++;
			}
			else if(j>2 && i<5 && board[i][j]==c && board[i+1][j-1]==c && board[i+2][j-2]=='_'){
				count++;
			}
		}
	}

	return count;
}
int count3s(char c){
	// Horizontal
	int count=0;
	for(int i=1;i<=6;i++){
		for(int j=1;j<=5;j++){
			if(j>1 && board[i][j-1]=='_' && board[i][j]==c && board[i][j+1]==c && board[i][j+2]){
				count++;
			}
			else if(j<5 && board[i][j]==c && board[i][j+1]==c && board[i][j+2]==c && board[i][j+3]=='_'){
				count++;
			}
		}
	}

	// Vertical
	for(int j=1;j<=7;j++){
		for(int i=2;i<=4;i++){
			if(board[i-1][j]=='_' && board[i][j]==c && board[i+1][j]==c && board[i+2][j]==c){
				count++;
			}
		}
	}

	// Diagonal
	for(int i=1;i<=4;i++){
		for(int j=1;j<=5;j++){
			if(j>1 && i>1 && board[i-1][j-1]=='_' && board[i][j]==c && board[i+1][j+1]==c && board[i+2][j+2]==c){
				count++;
			}
			else if(j<5 && i<4 && board[i][j]==c && board[i+1][j+1]==c && board[i+2][j+2]==c && board[i+3][j+3]=='_'){
				count++;
			}
		}
	}
	for(int i=1;i<=4;i++){
		for(int j=7;j>=3;j--){
			if(j<7 && i>1 && board[i-1][j+1]=='_' && board[i][j]==c && board[i+1][j-1]==c && board[i+2][j-2]==c){
				count++;
			}
			else if(j>3 && i<4 && board[i][j]==c && board[i+1][j-1]==c && board[i+2][j-2]==c && board[i+3][j-3]=='_'){
				count++;
			}
		}
	}
	return count;
}
int minimax(int depth, char c, int alpha, int beta){
	if(wins(maximiser)){
		return 100-depth;
	}
	else if(wins(minimiser)){
		return -100+depth;
	}
	else if(nomovesleft()){
		return 0;
	}

	if(depth>=MAXDEPTH){
		return 5*(count2s(maximiser)-count2s(minimiser))+10*(count3s(maximiser)-count3s(minimiser));
	}

	int curbest, value;
	if(c==maximiser){
		curbest=-100;
		for(int j=1;j<=7;j++){
			if(board[1][j]=='_'){
				Insert(j, maximiser);
				curbest=max(curbest, minimax(depth+1, minimiser, alpha, beta));
				Remove(j);
				alpha=max(alpha, curbest);
				if(alpha>=beta){
					break;
				}
			}
		}
		return curbest;
	}
	else{
		curbest=100;
		for(int j=1;j<=7;j++){
			if(board[1][j]=='_'){
				Insert(j, minimiser);
				curbest=min(curbest, minimax(depth+1, maximiser, alpha, beta));
				Remove(j);
				beta=min(beta, curbest);
				if(alpha>=beta){
					break;
				}
			}	
		}
		return curbest;
	}
}
int findmove(){
	int curmove;
	int curbest=-100, value;
	
	for(int j=1;j<=7;j++){
		if(board[1][j]=='_'){
			Insert(j, maximiser);
			value=minimax(0, minimiser, -1000, 1000);
			if(value>curbest){
				curbest=value;
				curmove=j;
			}
			Remove(j);
		}
	}
	return curmove;
}
int main(){

	printf("Welcome To Connect4\nInitializing...\n");
	for(int i=1;i<=6;i++){
		for(int j=1;j<=7;j++){
			board[i][j]='_';	
		}
	}
	srand(time(0));
	int ch, x;
	int bestmove;
	printf("Completed\n\n");
	
	printf("Game Begins\n");

	// Selecting Difficulty level
	printf("Select your difficulty level\n1. Easy\n2. Pro\n3. Impossible\n");
	printf("Enter Your choice: \n");
	scanf("%d", &ch);
	MAXDEPTH=4 + 2*ch;
	
	// Selecting Turns
	printf("Do you want to go first?\nPress 1 if yes\n0 otherwise\n\n");
	scanf("%d", &ch);
	if(ch){
		maximiser='o';
		minimiser='x';
	}
	else{
		maximiser='x';
		minimiser='o';
		Insert((rand()%7)+1, maximiser);
	}

	// Game Loop
	while(true){
		print();
		if(wins(maximiser)){
			printf("I won, You lost!\n");
			break;
		}
		else if(nomovesleft()){
			printf("Boring\n");
			break;
		}
		else{
			printf("Your turn\n\n");
			while(true){
				scanf("%d", &x);
				if(board[1][x]=='_'){
					break;
				}
				printf("You're dumb!\n");
			}
			Insert(x, minimiser);
		}
		print();

		if(wins(minimiser)){
			printf("GG\n");
			break;
		}
		else if(nomovesleft()){
			printf("Boring\n");
			break;
		}
		else{
			printf("My turn\n\n");
			bestmove=findmove();
			Insert(bestmove, maximiser);
		}
	}
	return 0;
}