#include <iostream>
#include <vector>
#include "point.h"
#include <memory>
#include <random>
#include <ctime>


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
//time per block move in milliseconds
int frameTime{100};

//checks the game board, determines if the snake if going to run into the wall or itself
bool isAlive(snake player){
	short index = (*player.points.back()).getX() + 40*(*player.points.back()).getY() - 1;

}

void runGame(short width, short height){
	//create board filled with 0
	std::vector<short> board(width*height, 0);

    // Create a reusable random number generator that generates uniform numbers between 0 and 3
    std::uniform_int_distribution rng{ 0, 3 };

	//starts player as one block sized snake at position: 20, 17
	//numbers run from 1 - 40 for width
	//1 - 35 for height
	//player starts facing a random direction
	snake player{1, std::vector<std::shared_ptr<Point>>{std::move(std::make_shared<Point>(20,17))}, static_cast<direction>(rng(mersenne))};


	bool food{false};
	while(isAlive(player)){
		//already tested if player is going to be alive in the while loop
		//so this is finding out their next move, and also the eating food mechanics
		





	}
}

//number generator for the placing of the "food"
//uses logic of counting how many squares are not taken up by the snake
//the generating a number that represents which space from the start the "food" should spawn at
//std::uniform_int_distribution{0, width*height-player.length - 1};