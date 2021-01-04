#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "Commons.h"

#include <string>

#define MyPlayer(init)		Player200012345		// CHANGE THIS: Your StudentID 
#define PLAYER_NAME		"Hello Snake :)"	// CHANGE THIS: Name your player

namespace snake_arena {
	class MyPlayer(init) final : public Player {
	public:
		MyPlayer(init)(int map_size);
		virtual ~MyPlayer(init)() override;

		virtual std::string getName() const { return PLAYER_NAME; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);
	};
}

