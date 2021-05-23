#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15

int plate[13][13];

int x = 0;
int y = 0;

int turn = 1;

void textcolor(int foreground, int background) 
{ 
int color=foreground+background*16; 
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}

void gameSet(){
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 13; j++){
			plate[i][j] = 0;
		}
	}
} 

void render(){
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 13; j++){
			if(i == y && j == x) textcolor(RED,BLACK);
			else textcolor(LIGHTGRAY,BLACK);
			switch(plate[i][j]){
				case 0:// 공백
					printf("■");
					break;
				case 1:// 백돌 
					if(!(i == y && j == x)) textcolor(WHITE,BLACK); 
					printf("○"); 
					break;
				case 2:// 흑돌 
					if(!(i == y && j == x)) textcolor(WHITE,BLACK); 
					printf("●");
					break; 
			}
		} 
		printf("\n");
	}
}

void end(){
	if(turn == 1) {
		printf("흑의 승리!\n");
		system("pause");
		exit(0);
	} 
	else {
		printf("백의 승리!\n");
		system("pause");
		exit(0);
	} 
}

void check(){
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 13; j++){
			int cnt = 0;
			for(int n = 0; n < 5; n++){//세로체크 
				if(plate[i+n][j] == turn) cnt++;
				else if(i+n > 12) break;
			}
			if(cnt >= 5) end();
			else cnt = 0;
			for(int n = 0; n < 5; n++){//가로체크 
				if(plate[i][j+n] == turn) cnt++;
				else if(i+n > 12) break;
			}
			if(cnt >= 5) end();
			else cnt = 0;
			for(int n = 0; n < 5; n++){//세로체크 
				if(plate[i+n][j+n] == turn) cnt++;
				else if(i+n > 12) break;
			}
			if(cnt >= 5) end();
			else cnt = 0;
			for(int n = 0; n < 5; n++){//세로체크 
				if(plate[i+n][j-n] == turn) cnt++;
				else if(i+n > 12) break;
			}
			if(cnt >= 5) end();
			else cnt = 0;
		}
	}
}

void cursor(){
	int input = getch();
	if(input == 224){
		input = getch();
		switch(input){
			case 72: //위 
			y--;
			if(y < 0) y = 0;
			break;
			case 80: //아래
			y++; 
			if(y > 12) y = 12;
			break;
			case 75: //왼쪽
			x--; 
			if(x < 0) x = 0;
			break;
			case 77: //오른쪽
			x++; 
			if(x > 12) x = 12;
			break;
		}
	}else if(input == 32 && (plate[y][x] == 0)){
		if(turn == 1) {
			plate[y][x] = 1;
			system("cls");
			render();
			check();
			turn = 2;
		}
		else if(turn == 2) {
			plate[y][x] = 2;
			system("cls");
			render();
			check();
			turn = 1;
		}
	}
}

int main(){
	gameSet();
	while(1){
		render();
		cursor(); 
		system("cls");
	}	
}  
