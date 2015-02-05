#include "maze.h"
#include "shinnenn.h"

void kabegiwa_chk(){

	switch (m.dir){
	case 0:
		if (m.now.y == 1){//上端
			if (canMove(DirUp) == MapGoal){
				m.mv = DirUp; return;
			}
			else{
				m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}
		}

		if (m.now.x == 1){//左端
			if (canMove(DirLeft) == MapGoal){
				m.mv = DirLeft;
				return;

			}
			else{
				m.cnt[m.now.x - 1][m.now.y] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}
		}

		if (m.now.x == x_size - 2){//右端
			if (canMove(DirRight) == MapGoal){
				m.mv = DirRight;
				return;
			}
			else{
				m.cnt[m.now.x + 1][m.now.y] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}

		}
		break;

	case 1:
		//壁際のゴール確認
		if (m.now.y == 1){//右向きの上
			if (canMove(DirUp) == MapGoal){
				m.mv = DirUp;
				return;
			}
			else
			{
				m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
				//	m.cnt[m.now.x][m.now.y] += 3;
			}

		}
		if (m.now.y == y_size - 2){//右向きの下
			if (canMove(DirDown) == MapGoal){
				m.mv = DirDown;
				return;
			}
			else{
				m.cnt[m.now.x][m.now.y + 1] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}

		}
		//////////////////////////////////////////
		break;
	case 2:
		//壁際のゴール確認
		if (m.now.x == 1){//下向き左端
			if (canMove(DirLeft) == MapGoal){
				m.mv = DirLeft;
				return;
			}
			else
			{
				m.cnt[m.now.x - 1][m.now.y] = 1000;//壁
				//m.cnt[m.now.x][m.now.y] += 3;
			}
		}


		if (m.now.x == x_size - 2){//下向き右端
			if (canMove(DirRight) == MapGoal){
				m.mv = DirRight;
				return;
			}
			else{
				//m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x + 1][m.now.y] = 1000;//壁
			}
		}
		//////////////////////////////////////////
		break;
	case 3:

		//壁際のゴール確認
		if (m.now.y == 1){//左向き上端
			if (canMove(DirUp) == MapGoal){
				m.mv = DirUp;
				return;
			}
			else{
				//	m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
			}

		}
		if (m.now.y == y_size - 2){//左向き下端
			if (canMove(DirDown) == MapGoal){
				m.mv = DirDown;
				return;
			}
			else{
				//m.cnt[m.now.x][m.now.y] += 3;
				m.cnt[m.now.x][m.now.y + 1] = 1000;//壁
			}
		}

		break;
	}
}