#include <windows.h>

#include <iostream>
#include <vector>
#include "point.h"
#include <memory>
#include <random>
#include <ctime>
#include <chrono>
#include <conio.h>



// Initialize our mersenne twister with a random seed based on the clock
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
 
//enumeration for the way that the snake can face
enum direction{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX_DIRECTION
};
//struct for snake
struct snake{
	int length;
	std::vector<std::shared_ptr<Point>> points;
	direction direct;
};

/**
 * @param player struct for the snake location data
 * @param board used for board information
 * @return boolean of if the snake is about to run into the wall or itself
 *
 * Checks next space to see if it is a snake part or a border
 */
bool isAlive(snake player, const std::vector<short> &board){
	short index = (*player.points.back()).getX() + 40*((*player.points.back()).getY()-1) - 1;
	if(player.direct == UP){
		if(index <= 39)
			return false;
		else if(board[index - 40] == 1)
			return false;
		else
			return true;
	}else if(player.direct == DOWN){
		if(index >= 1360)
			return false;
		else if(board[index + 40] == 1)
			return false;
		else
			return true;
	}else if(player.direct == RIGHT){
		if((index+1) % 40 == 0 && index != 0)
			return false;
		else if(board[index + 1] == 1)
			return false;
		else
			return true;
	}else if(player.direct == LEFT){
		if(index % 40 == 0)
			return false;
		else if(board[index-1] == 1)
			return false;
		else
			return true;
	}else{
		std::cout << "System Error";
		exit(1);
	}
}

/**
 * @param player struct to get location of head
 * @param board to find out the things on each square
 * @return boolean based on if the snake is about to eat a "food"
 *
 * Determines whether the snake is about to eat the food by checking the next space it is about to move into
 */
bool eatFood(snake &player, const std::vector<short> &board, const short index){
	if(player.direct == UP){
		if(board[index - 40] == 2)
			return true;
		else
			return false;
	}else if(player.direct == DOWN){
		if(board[index + 40] == 2)
			return true;
		else
			return false;
	}else if(player.direct == RIGHT){
		if(board[index + 1] == 2)
			return true;
		else
			return false;
	}else if(player.direct == LEFT){
		if(board[index-1] == 2)
			return true;
		else
			return false;
	}else{
		std::cout << "System Error";
		exit(1);
	}
}

/**
 * @param player struct included for location information
 * @param board included for board information
 * @param food included to indicate whether the snake is about to "eat" the "food"
 *
 * This removes the end block of the snake to the next space it would move into
 * Checks if it is about to eat food, if it is, it doesn't move the back to the front and changes the food into part of the snake
 */
void moveSnake(snake &player, std::vector<short> &board, bool &food){
	int x{(*player.points.back()).getX()}, y{(*player.points.back()).getY()};
	short index =  x + 40*(y-1) - 1;
	bool trig{eatFood(player, board, index)};
	if(player.direct == UP){
		board[index - 40] = 1;
		player.points.push_back(std::make_shared<Point>(x,y - 1));
	}else if(player.direct == DOWN){
		board[index + 40] = 1;
		player.points.push_back(std::make_shared<Point>(x,y + 1));
	}else if(player.direct == RIGHT){
		board[index + 1] = 1;
		player.points.push_back(std::make_shared<Point>(x + 1,y));
	}else if(player.direct == LEFT){
		board[index-1] = 1;
		player.points.push_back(std::make_shared<Point>(x - 1,y));
	}
	if(trig){
		food = false;
		++player.length;
	}else{
		board[(*player.points[0]).getX() + 40*((*player.points[0]).getY()-1) - 1] = 0;
		player.points.erase(player.points.begin());
		std::cout << player.points.size();
	}
}

//variables for color changing
HANDLE hStdout; 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

/**
 * @param board used for board data
 *
 * prints out the actual interface
 * snake is colored white
 * the background is black
 * the food is red
 * Loops through the board and print spaces with changing the background color
 */
void printBoard(const std::vector<short> board){
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	printf("\n");
	for (int i = 0; i < board.size(); ++i)
	{
		if(board[i] == 0){
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
		}else if(board[i] == 1){
			SetConsoleTextAttribute(hStdout, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		}else if(board[i] == 2){
			SetConsoleTextAttribute(hStdout, BACKGROUND_RED);
		}
		printf("  ");
		if((i+1) % 40 == 0)
			printf("\n");
	}
}

/**
 * @param struct player used for length data
 * @param board included for board data
 *
 * This calculates a random number from 1 to the number of spaces not taken up by the snake.
 * It then loops through n number of blank spaces and then places the food
 */
void placeFood(snake player, std::vector<short> &board){
	std::uniform_int_distribution foodPlacer{1, 1400-player.length - 1};
	int number{foodPlacer(mersenne)};
	for (int i = 0; i < board.size(); ++i)
	{
		if(board[i] == 0){
			if(!--number){
				board[i] = 2;
				return;
			}
		}
	}
}

/**
 * the game loop
 */
void runGame(){
	//create board filled with 0
	std::vector<short> board(1400, 0);

    // Create a reusable random number generator that generates uniform numbers between 0 and 3
    std::uniform_int_distribution rng{ 0, 3 };

	//starts player as one block sized snake at position: 20, 17
	//numbers run from 1 - 40 for width
	//1 - 35 for height
	//player starts facing a random direction
	snake player{1, std::vector<std::shared_ptr<Point>>{std::move(std::make_shared<Point>(20,17))}, static_cast<direction>(rng(mersenne))};

	//setting up the board for initial position
	//create random number generator for placing the field
	board[659] = 1;
	placeFood(player, board);
	bool food{true};

	bool trigger{true};
	while(trigger){
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		char move{};
		if(player.direct == UP){
			move = 'w';
		}else if(player.direct == DOWN){
			move = 's';
		}else if(player.direct == RIGHT){
			move = 'd';
		}else if(player.direct == LEFT){
			move = 'a';
		}
		while((std::chrono::steady_clock::now() - begin).count() < 500000000){
			char hold{};
			if(kbhit()){
				hold = getch();
			}
			//std::cout << hold;
			if(!std::cin.fail()){
				if(hold == 'w'){
					move = 'w';
				}else if(hold == 's')
					move = 's';
				else if(hold == 'd')
					move = 'd';
				else if(hold == 'a')
					move = 'a';
			}
		}
		if(move == 'w'){
			player.direct = UP;
		}else if(move == 's'){
			player.direct = DOWN;
		}else if(move == 'd'){
			player.direct = RIGHT;
		}else if(move == 'a'){
			player.direct = LEFT;
		}

		if(!isAlive(player, board))
			break;
		
		moveSnake(player, board, food);	

		if(!food){
			placeFood(player, board);
			food = true;
		}

		printBoard(board);


	}
}