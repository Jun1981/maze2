#include "maze.h"
#include "shinnenn.h"
#include "kabegiwa.h"

int kabegiwa(){

	switch (m.dir){
	case 0:
		

		if (m.now.x == 1){//左端
			if (canMove(DirLeft) == MapGoal){
				
				return DirLeft;;

			}
			else{
				m.cnt[m.now.x - 1][m.now.y] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}
		}

		if (m.now.x == x_size - 2){//右端
			if (canMove(DirRight) == MapGoal){
				
				return DirRight;
			}
			else{
				m.cnt[m.now.x + 1][m.now.y] = 1000;//壁
				return -1;
				//m.cnt[m.now.x][m.now.y] += 3;
			}

		}
		break;

	case 1:
		//壁際のゴール確認
		if (m.now.y == 1){//右向きの上
			if (canMove(DirUp) == MapGoal){
				
				return DirUp;
			}
			else
			{
				m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
				//	m.cnt[m.now.x][m.now.y] += 3;
			}

		}
		if (m.now.y == y_size - 2){//右向きの下
			if (canMove(DirDown) == MapGoal){
				
				return DirDown;
			}
			else{
				m.cnt[m.now.x][m.now.y + 1] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
				return -1;
			}

		}
		//////////////////////////////////////////
		break;
	case 2:
		//壁際のゴール確認
		if (m.now.x == 1){//下向き左端
			if (canMove(DirLeft) == MapGoal){
				
				return DirLeft;
			}
			else
			{
				m.cnt[m.now.x - 1][m.now.y] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}
		}


		if (m.now.x == x_size - 2){//下向き右端
			if (canMove(DirRight) == MapGoal){
				
				return DirRight;
			}
			else{
				//m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x + 1][m.now.y] = 1000;//壁
				return -1;
			}
		}
		//////////////////////////////////////////
		break;
	case 3:

		//壁際のゴール確認
		if (m.now.y == 1){//左向き上端
			if (canMove(DirUp) == MapGoal){
			
				return DirUp;
			}
			else{
				//	m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
			}

		}
		if (m.now.y == y_size - 2){//左向き下端
			if (canMove(DirDown) == MapGoal){
				
				return DirDown;
			}
			else{
				//m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x][m.now.y + 1] = 1000;//壁
				return -1;
			}
		}

		break;
	}


	return -1;
}