#include<iostream>
#include<cstdio>
#include<algorithm>
#include<windows.h>
#include<conio.h>
using namespace std;
class Chess{
public:
	void CreateChessB(int x,int y){
		flag = true;
		xpos = x;ypos = y;
	}
	void CreateChessW(int x, int y){
		flag = false;
		xpos = x;ypos = y;
	}
	bool TypeOf(){return flag;}//return the type of Chess
	int qx(){return xpos;}//return chess xpos
	int qy(){return ypos;}//return chess ypos
private:
	int xpos,ypos;//position
	bool flag;//To judge Type of Chess
			  //0  White
			  //1  Black
};
class ChessBoard{
public:
	int SizeOf;//size of the Chessboard
	int Step = 0;//Step of a game
	int ChB[100][100];
	/*
	0  No Chess
	1 Black
	-1 White
	*/
	bool ChooseVision = true;
	int Cv = 1;
	void _GetKey(bool &Keyflag/*To judge if 'c' is pushed*/,bool &IfKey/*To judge if _kbhit()*/){
		if(_kbhit()){
			IfKey = true;
			char c = _getch();
			if(c == 'c'){
				Keyflag = true;
			}
			if(c == 'v'){//Control the choose vision
				if(Cv % 2 == 1){
					ChooseVision = false;
				}else{
					ChooseVision = true;
				}
				Cv++;
			}
			if(c == 'w' && PlayerChooseY > 1) PlayerChooseY--;
			else if(c == 's' && PlayerChooseY < SizeOf) PlayerChooseY++;
			else if(c == 'a' && PlayerChooseX > 1) PlayerChooseX--;
			else if(c == 'd' && PlayerChooseX < SizeOf) PlayerChooseX++;
		}
	}
	void PrintChessBoard(){
		system("cls");
		for(int i = 1;i <= SizeOf + 1;i++){
			for(int j = 1;j <= SizeOf + 1;j++){
				if(ChooseVision){
					//Out of chessboard
					if(ChB[i][j] != 0){
						if(ChB[i][j] == 1){
							printf("& ");
						}else if(ChB[i][j] == -1){
							printf("# ");
						}
						continue ;
					}
					if(i == SizeOf + 1 && j == SizeOf + 1){
						printf("  "); break;
					}else if(i == SizeOf + 1 && j == PlayerChooseX){
						printf("+ "); break;
					}else if(i == PlayerChooseY && j == SizeOf + 1){
						printf("+ "); break;
					}else if(i == SizeOf + 1 || j == SizeOf + 1){
						printf("  ");
					}

					//In chessboard choose
					if(i == PlayerChooseY && j == PlayerChooseX){
						printf("* ");
						continue;
					}else if(i == PlayerChooseY){
						printf("< ");
						continue;
					}else if(j == PlayerChooseX){
						printf("| ");
						continue;
					}
				}
				
				if(!ChooseVision){
					if(i == PlayerChooseY && j == PlayerChooseX){
						printf("+ ");
						continue;
					}
				}
				//Normal
				if(j != SizeOf + 1 && i != SizeOf + 1){
					if(ChB[i][j] == 0){
						if( ChooseVision){
							printf("- ");
						}else{
							printf("  ");
						}
					}else if(ChB[i][j] == 1){
						printf("& ");
					}else if(ChB[i][j] == -1){
						printf("# ");
					}
				}
			}
			printf("\n");
		}
		if(!ChooseVision){
			printf("\n[%d %d]",PlayerChooseX,PlayerChooseY);
		}
	}
	void PutChess(bool Type,int xpos,int ypos){
		if(Type){
			ChB[xpos][ypos] = 1;
		}else{
			ChB[xpos][ypos] = -1;
		}
	}
	int PlcX(){return PlayerChooseX;}
	int PlcY(){return PlayerChooseY;}
private:
	int PlayerChooseX = 1,PlayerChooseY = 1;
};
class Judge{
public:
	bool flag = true;
private:
};
ChessBoard cb;
Chess chess[10005];
Judge Judgement;
int main(){
	scanf("%d", &cb.SizeOf);
	while(Judgement.flag){
		int StepOf = cb.Step;
		bool Keyflag = false;
		bool IfKey = false;
		cb.PrintChessBoard();
		while(!Keyflag){
			cb._GetKey(Keyflag,IfKey);
			if(IfKey){
				cb.PrintChessBoard();
				IfKey = false;
			} 
			if(Keyflag){
				if(cb.ChB[cb.PlcY()][cb.PlcX()] != 0){
					printf("\nThis place has a chess!");
					Keyflag = false;
				}else{
					if(StepOf % 2 == 0){
						chess[StepOf].CreateChessB(cb.PlcY(),cb.PlcX());
					}else{
						chess[StepOf].CreateChessW(cb.PlcY(),cb.PlcX());
					}
					cb.PutChess(chess[StepOf].TypeOf(),cb.PlcY(),cb.PlcX());
				}
				
			}
		}
		cb.Step++;     
	}
	return 0;
}
