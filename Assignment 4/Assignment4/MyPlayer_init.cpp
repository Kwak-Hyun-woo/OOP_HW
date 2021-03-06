////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "MyPlayer_init.h"

#include "Commons.h"
#include "Snake.h"
#include "Fruit.h"

namespace snake_arena {
	// Constructor
	MyPlayer_init::MyPlayer_init(int map_size) :
		Player(map_size) {

	}

	// Destructor
	MyPlayer_init::~MyPlayer_init() {

	}

	// Your function to primarily implement
	Direction MyPlayer_init::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake,
		std::vector<Fruit*> fruits) {
		switch (turn % 4) {
		case 0:
			return DrtN();
		case 1:
			return DrtW();
		case 2:
			return DrtS();
		}
		return DrtE(); // when case 3
	}
}
