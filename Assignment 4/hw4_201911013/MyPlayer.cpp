////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "MyPlayer.h"
#include "Commons.h"
#include "Snake.h"
#include "Fruit.h"

namespace snake_arena {
	// Constructor
	MyPlayer::MyPlayer(int map_size) :
		Player(map_size) {
	}

	// Destructor
	MyPlayer::~MyPlayer() {
	}
	// Your function to primarily implement
	Direction MyPlayer::selectDirection(
		int turn, Snake* player_snake, Snake* enemy_snake,
		std::vector<Fruit*> fruits) {

		// DrtN 위, DrtW 왼쪽, DrtS 아래, DrtE 오른쪽
		// Map_size = 15 * 15
		//변수 선언부분-------------------------------------

		std::vector<Pos> my_pos = player_snake->getPositions();      // 나의 몸통 좌표
		Direction pre_dir = player_snake->getDirection();            // 이전 입력받은 방향
		Pos my_head = my_pos[0];                                     // 나의 머리 좌표

		std::vector<Pos> enemy_pos = enemy_snake->getPositions();    // 적 몸통 좌표

		Pos fruit1_pos = fruits[0]->getPositions()[0];     // 과일1 위치
		Pos fruit2_pos = fruits[1]->getPositions()[0];     // 과일2 위치

		Pos my_next_head_n = my_pos[0] + DrtN();                   // 다음턴 n head 위치
		Pos my_next_head_e = my_pos[0] + DrtE();                   // 다음턴 e head 위치
		Pos my_next_head_s = my_pos[0] + DrtS();                   // 다음턴 s head 위치
		Pos my_next_head_w = my_pos[0] + DrtW();                   // 다음턴 w head 위치
		Pos my_next_head = my_pos[0] + pre_dir;         // 현재 방향으로 계속 움직일 때 다음턴의 head 위치
														
		int fruit1_my_dis = grid_distance(my_pos[0], fruit1_pos);				// 나 - 과일1 거리
		int fruit2_my_dis = grid_distance(my_pos[0], fruit2_pos);				// 나 - 과일2 거리
		int fruit1_enemy_dis = grid_distance(enemy_pos[0], fruit1_pos);			// 적 - 과일1 거리
		int fruit2_enemy_dis = grid_distance(enemy_pos[0], fruit2_pos);			// 적 - 과일2 거리

		bool where_fruit_from_me[2][4];	 // {N에 존재, E에 존재, S에 존재, W에 존재 }
										 //  head 기준 fruit 위치 정보 저장
		//---------------------------------------------
		to_fruit_dir_update(where_fruit_from_me, my_head, fruit1_pos, fruit2_pos);    //  turn 마다 where_fruit_from_me 업데이트

		int n_valid_num = bfs_check(my_next_head_n, my_pos, enemy_pos);
		int e_valid_num = bfs_check(my_next_head_e, my_pos, enemy_pos);
		int s_valid_num = bfs_check(my_next_head_s, my_pos, enemy_pos);
		int w_valid_num = bfs_check(my_next_head_w, my_pos, enemy_pos);

		int standard = 30;								// manual tuning
		bool n_closed = n_valid_num < standard;         // cutline 값보다 낮으면 true 높으면 false ==> true면 closed false면 open 
		bool e_closed = e_valid_num < standard;			// cutline 값보다 낮으면 true 높으면 false
		bool s_closed = s_valid_num < standard;			// cutline 값보다 낮으면 true 높으면 false
		bool w_closed = w_valid_num < standard;			// cutline 값보다 낮으면 true 높으면 false
		
		while (true) {                                 
			if (n_closed == true || e_closed == true|| s_closed == true || w_closed == true) {
				break;
			}
			if (standard == 0) {
				break;
			}
			n_closed = n_valid_num < standard;
			e_closed = e_valid_num < standard;
			s_closed = s_valid_num < standard;
			w_closed = w_valid_num < standard;

			standard -= 1;
		}
		bool pred_hit_n = pred_hit(enemy_snake, player_snake, my_next_head_n);		// 다음 턴에 부딪히면 true 아니면 false
		bool pred_hit_e = pred_hit(enemy_snake, player_snake, my_next_head_e);		// 다음 턴에 부딪히면 true 아니면 false
		bool pred_hit_s = pred_hit(enemy_snake, player_snake, my_next_head_s);		// 다음 턴에 부딪히면 true 아니면 false
		bool pred_hit_w = pred_hit(enemy_snake, player_snake, my_next_head_w);		// 다음 턴에 부딪히면 true 아니면 false


		Direction avoid_object = avoid_hit(n_closed, e_closed, s_closed, w_closed, pre_dir);
		Direction avoid_object2 = avoid_hit(pred_hit_n, pred_hit_e, pred_hit_s, pred_hit_w, pre_dir);

		Direction to_fruit1 = to_fruit(avoid_object, avoid_object2 ,pre_dir, fruit1_pos, my_head, where_fruit_from_me, 0, n_closed, e_closed, s_closed, w_closed);
		Direction to_fruit2 = to_fruit(avoid_object, avoid_object2 ,pre_dir, fruit2_pos, my_head, where_fruit_from_me, 1, n_closed, e_closed, s_closed, w_closed);

		if (fruit1_my_dis < fruit2_my_dis) {											// my 기준 어느 과일이 더 가까운 지 비교
			if (fruit1_my_dis < fruit1_enemy_dis) {										// 과일1이 적보다 내가 더 가까울 때
				return to_fruit1;	// to fruit 1
			}
			else {																		// 과일1이 나보다 적이 더 가까울 때
				return to_fruit2;	// to fruit 2
			}
		}
		else {
			if (fruit2_my_dis < fruit2_enemy_dis) {										// 과일2이 적보다 내가 더 가까울 때
				return to_fruit2;	// to fruit 2
			}
			else {																		// 과일2이 나보다 적이 더 가까울 때
				return to_fruit1;	// to fruit 1
			}
		}
	}   //selectDirection 끝나는 부분
	// -----------------------패쇄경로 빠져나오는 법-----------------------------------------
	int MyPlayer::bfs_check(Pos next_head, std::vector<Pos> my_pos, std::vector<Pos> enemy_pos) {			// 너비 우선탐색으로 가능한 길 개수 모색
		int count_safe = 1;
		bool visit[15][15];
		memset(visit, false, 15 * 15 * 1);
		
		int map[15][15];
		std::queue<Pos> temp_q;
		temp_q.push(next_head);
		//[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    1
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    2
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    3
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    4
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    5
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    6
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    7  
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    8
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    9
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    10
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    11
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    12
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    13
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    14
		// [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],    15
		// ]
		//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				map[i][j] = 0;
			}
		}

		for (auto i = my_pos.begin(); i != my_pos.end(); ++i) {
			map[(*i).y][(*i).x] = 1;
		}
		for (auto i = enemy_pos.begin(); i != enemy_pos.end(); ++i) {
			map[(*i).y][(*i).x] = 1;
		}
		if (next_head.x < 0 || 14 < next_head.x || next_head.y < 0 || 14 < next_head.y) {
			return 0;
		}
		if (map[next_head.y][next_head.x] == 1) {
			return 0;
		}
		visit[next_head.y][next_head.x] = true;

		while (!temp_q.empty()) {
			Pos safe = temp_q.front();
			temp_q.pop();

			std::vector<Pos> next_dir;
			if (safe.y != 0){
				next_dir.push_back(safe + DrtN()); 
			}
			if (safe.y != 14) {
				next_dir.push_back(safe + DrtS()); 
			}
			if (safe.x != 0) { 
				next_dir.push_back(safe + DrtW()); 
			}
			if (safe.x != 14) { 
				next_dir.push_back(safe + DrtE());
			}
			
			for (Pos& next_ : next_dir) {
				if (map[next_.y][next_.x] != 1 && !visit[next_.y][next_.x]) {
					temp_q.push(next_);
					visit[next_.y][next_.x] = true;
					count_safe += 1;
				}
			}
		}
		return count_safe;
	}

	bool MyPlayer::pred_hit(Snake* enemy, Snake* me, Pos next_head) {																			// 다음 턴에 부딪히는 지 안 부딪히는 지 알려주는 함수
		if (enemy->hit(next_head) || me->hit(next_head) || next_head.x > 14 || next_head.x < 0 || next_head.y> 14 || next_head.y < 0) {			// 적 몸통에 부딪히거나, 내 몸에 부딪히거나, 맵 밖일때
			return true;
		}
		else {
			false;
		}
	}


	Direction MyPlayer::to_fruit(Direction avoid_object, Direction avoid_object2, Direction pre_dir, Pos fruit_pos, Pos head, bool where_fruit_from_me[2][4], int select,
								 bool n_closed, bool e_closed, bool s_closed, bool w_closed) {	

		if (!n_closed || !e_closed || !s_closed || !w_closed) {					//true면 closed, false면 open 
			if (fruit_pos.y - head.y != 0) {  // 남, 북 방향 먼저 결정
				if (where_fruit_from_me[select][0] && !n_closed) {
					return DrtN();
				}
				else if (where_fruit_from_me[select][2] && !s_closed) {
					return DrtS();
				}
			}								// 이 후 동,서 방향 결정
			if (where_fruit_from_me[select][1]) {
				if (!e_closed) {
					return DrtE();
				}
			}
			else if (where_fruit_from_me[select][3]) {
				if (!w_closed) {
					return DrtW();
				}
			}
			return avoid_object;
		}
		return avoid_object2;
	}

	Direction MyPlayer::avoid_hit(bool hit_n, bool hit_e, bool hit_s, bool hit_w, Direction pre_dir) {   // 최종적으로 부딧히는 지 안 부딧히는 지 결정하는 함수
		int clock_wise;																					  // 시계 방향으로 돌면서 장애물 있는 지 check한 다음 가능한 방향을 찾아 return
		if (pre_dir == DrtN()) {
			clock_wise = 1;
		}
		else if (pre_dir == DrtE()) {
			clock_wise = 2;
		}
		else if (pre_dir == DrtS()) {
			clock_wise = 3;
		}
		else{
			clock_wise = 4;
		}
		for (int i = 0; i < 4; i++) {		// 북 - 동 - 남 - 서 (시계방향으로 탐색)
			switch (clock_wise % 4) {
				case 1:
					if (!hit_n) {			// N 방향 안부딪히면 N 방향 return
						return DrtN();
					}
					break;
				case 2:
					if (!hit_e) {			// E 방향 안부딪히면 E 방향 return
						return DrtE();
					}
					break;
				case 3:
					if (!hit_s) {			// S 방향 안부딪히면 S 방향 return
						return DrtS();
					}
					break;
				default:
					if (!hit_w) {			// W 방향 안부딪히면 W 방향 return
						return DrtW();
					}
			}
			clock_wise += 1;
		}
	}
	void MyPlayer::to_fruit_dir_update(bool where_fruit_from_me[2][4], Pos my_head, Pos fruit1_pos, Pos fruit2_pos) {
		// ------------fruit1 정보 update-----------------
		if (my_head.x - fruit1_pos.x < 0) {				// E 활성화
			where_fruit_from_me[0][1] = true;     
			where_fruit_from_me[0][3] = false;
		}												
		else {											// W 활성화
			where_fruit_from_me[0][1] = false;
			where_fruit_from_me[0][3] = true;
		}

		if (my_head.y - fruit1_pos.y < 0) {				// S 활성화       * y값이 작을수록 N쪽에 있다.
			where_fruit_from_me[0][2] = true;
			where_fruit_from_me[0][0] = false;
		}
		else {											// N 활성화
			where_fruit_from_me[0][2] = false;
			where_fruit_from_me[0][0] = true;
		}
		// ------------fruit2 정보 update-----------------
		if (my_head.x - fruit2_pos.x < 0) {				// E 활성화
			where_fruit_from_me[1][1] = true;
			where_fruit_from_me[1][3] = false;
		}
		else {											// W 활성화
			where_fruit_from_me[1][1] = false;
			where_fruit_from_me[1][3] = true;
		}

		if (my_head.y - fruit2_pos.y < 0) {				// S 활성화
			where_fruit_from_me[1][2] = true;
			where_fruit_from_me[1][0] = false;
		}
		else {											// N 활성화
			where_fruit_from_me[1][2] = false;
			where_fruit_from_me[1][0] = true;
		}
	}
	int MyPlayer::grid_distance(Pos a, Pos b) {        // 격자거리 계산
		return (abs(a.x - b.x) + abs(a.y - b.y));
	}
};