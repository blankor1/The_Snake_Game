#include<stdio.h>   
#include<stdlib.h>  
#include<conio.h>   
#include<dos.h>     
#include<windows.h> 

#define LEFT 027    //left and right key on keyboard
#define RIGHT 026
#define DOWN 025
#define UP 024,
#define ESC 27
#define N 100        //Maximum length of the snake

int speed;
int score = 0;
//int key;

struct FOOD
{
	int x;   //x coordinate of food
	int y;   //y coordinate of food
	int flag;   //flag that indicate whether food should appear
}food;

struct Snake
{
	int x[N];
	int y[N];
	int node;    //the node number of the snake
	int dir;
	int life;
}snake;

int gotoxy(int x, int y) //make cursor to this position
{
	HANDLE handle; 
	COORD coord; 
	coord.X = x; 
	coord.Y = y; 
	handle = GetStdHandle(STD_OUTPUT_HANDLE); //the the output handler of console(value = -11)
	SetConsoleCursorPosition(handle, coord); //move the cursor
}

int cleardevice()
{
	system("cls");            //clear the console
}

void GameOver(void)
{
	cleardevice();
	gotoxy(20, 10);
	printf("GAME OVER! BYE BYE");
	gotoxy(20, 12);
	printf("THE SCORE YOU GOT IS : %d",score);
	Sleep(3);
}

int Speed()
{
	int m;        //get the spead
	gotoxy(20, 6);
	printf("Snake Game\n\n                  Please select the difficulty level");
	gotoxy(20, 10);
	printf("level 1\n");
	gotoxy(20,12);
	printf("level 2\n");
	gotoxy(20, 14);
	printf("level 3\n");
	
	scanf_s("%d", &m);

	switch (m)
	{
	case 1:
		return 400;
	case 2:
		return 200;
	case 3:
		return 100;
	default:
		cleardevice();
		Speed();
	}
}

int dwall()
{
	int i,j;
	for (i = 0; i <= 54; i++)
		for (j = 0; j <= 26; j++)
		{
			gotoxy(i, 0);
			printf("#");
			gotoxy(i, 26);
			printf("#");
			gotoxy(0, j);
			printf("¡ö");
			gotoxy(54, j);
			printf("¡ö");
		}
}

void Play(void)
{   
	int i;
	int key;
	srand((unsigned long)time(0));
	food.flag = 1;                    //1 means new food is needed, 0 means food already existed
	snake.life = 0;                   //snake still alive
	snake.dir = 1;                    //initial head to right
	snake.x[0] = 4; snake.y[0] = 4;   //initial the position of snake's head
	snake.x[1] = 4; snake.y[1] = 3;
	snake.x[2] = 4; snake.y[2] = 2;
	snake.node = 3;                  //node number of the snake

	do
	{
		while (!_kbhit())                         //while no key is pressed, snake keep moving
		{
			if (food.flag==1)                   //new food needed
				
				{
					srand(time(NULL));
					food.x = rand() % 50 + 2;
					food.y = rand() % 24 + 2;
					food.flag = 0;                  //food already existed
				} 

				if (food.flag == 0)                      //draw the food
				{
					gotoxy(food.x,food.y);
					printf("*");
				}

				for (i = snake.node - 1; i > 0; i--)
				{
					snake.x[i] = snake.x[i - 1];
					snake.y[i] = snake.y[i - 1];
				}
	
				switch (snake.dir)
				{
				case 1:snake.x[0] += 1; break;   //go right
				case 2:snake.x[0] -= 1; break;   //left
				case 3:snake.y[0] -= 1; break;   //up
				case 4:snake.y[0] += 1; break;   //down
				}

				for (i = 3; i < snake.node; i++)
				{
					//judge if the snake touch itself
					if (snake.x[i] == snake.x[0] && snake.y[i] == snake.y[0])
					{
						GameOver();             //game over
						snake.life = 1;         //the snake is dead
						break;
					}
				}

				//judge if the snake hit the wall
				if (snake.x[0] < 1 || snake.x[0]>53 || snake.y[0] < 1 || snake.y[0]>25)
				{
					GameOver();
					snake.life = 1;
					break;
				}

			
				//judge if the snake eaten that food
				if (snake.x[0] == food.x&&snake.y[0] == food.y)
				{   
					score = score + 10;
					gotoxy(food.x, food.y);
					printf(" ");                  //cover the food
					gotoxy(food.x, food.y);
					printf("#");
					snake.node++;                 //snake becomes longer
					food.flag = 1;                //new food needed
				}

	
		//draw the snake
		for (i = 0; i < snake.node; i++)
		{
			gotoxy(snake.x[i], snake.y[i]);
			printf("#");
		}
		Sleep(speed);
		printf(" ");              //cover the last node of snake
		gotoxy(snake.x[snake.node - 1], snake.y[snake.node - 1]);
		printf(" ");
		}

		if (snake.life == 1)
			break;

			key = _getch();        //receive the key command
			if (GetAsyncKeyState(VK_UP) && snake.dir != 4)        //up
				snake.dir = 3;
			else if (GetAsyncKeyState(VK_DOWN) && snake.dir != 3)  //down
				snake.dir = 4;
			else if (GetAsyncKeyState(VK_RIGHT)&&snake.dir != 2)   //right
				snake.dir = 1;
			else if (GetAsyncKeyState(VK_LEFT) && snake.dir != 1)   //left
				snake.dir = 2;
			else if (key == 27)//if it is ESC, then exit
				exit(0);
			
		
	} while (key != ESC);
}


main()
{
	system("color E");
	speed = Speed();
	cleardevice();
	dwall();
	Play();
	_getch();
}