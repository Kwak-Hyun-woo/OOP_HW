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

#include <algorithm>
#include <string>
#include <queue>

#define MyPlayer		Player201911013		// CHANGE THIS: Your StudentID 
#define PLAYER_NAME		"KwakHyunwoo"   	// CHANGE THIS: Name your player

namespace snake_arena {
	class MyPlayer final : public Player {
	public:
		MyPlayer(int map_size);
		virtual ~MyPlayer() override;

		virtual std::string getName() const { return PLAYER_NAME; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);

	private:
		int bfs_check(Pos next_head, std::vector<Pos> my_pos, std::vector<Pos> enemy_pos);
		int grid_distance(Pos a, Pos b);
		Direction avoid_hit(bool hit_n, bool hit_e, bool hit_s, bool hit_w, Direction pre_dir);
		void to_fruit_dir_update(bool where_fruit_from_me[2][4], Pos my_head, Pos fruit1_pos, Pos fruit2_pos);
		Direction to_fruit(Direction avoid_object, Direction avoid_object2, Direction pre_dir, Pos fruit_pos, Pos head, bool where_fruit_from_me[2][4], int select,
							bool n_closed, bool e_closed, bool s_closed, bool w_closed);
		bool pred_hit(Snake* enemy, Snake* me, Pos next_head);
	};
}

