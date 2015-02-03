//=================================
//	迷路探索サンプル
//		毎回、上→右→下→左の順に通れるかチェックする
//		このプログラムは、ある条件を満たす迷路では、
//		先に進まなくなる。
//=================================


#include "shinnenn.h"
#include "maze.h"

#include "move.h"


//=================================
//	プレーヤ情報
//=================================
static	Funcs	funcs = { "深淵（ｒｙ" , init, walkAround };

//=================================
//	公開関数
//=================================
Funcs*	getGroup05Info	( void ) { return &funcs; }


//内部関数

map m;


static int once = 0;//最初だけ
static int	walkAround(void)
{
	if (once == 0){
		init();
		once = 1;


		return m.mv;
	}//最初のチェック	



	move();//移動計算

	//DrawFormatString(300, 300, "カウント", m.cnt[1][20]);
	

	
	return m.mv;

}







 static void init(void){


	

	m.now = getCurrentPosition();



	m.cnt[m.now.x][m.now.y] = 1000;
	m.stat[m.now.x][m.now.y] = wall;//壁
	m.old.x = m.now.x, m.old.y = m.now.y;


	if (m.now.x == 0) m.mv=m.dir = DirRight;//スタート地点が左端だったら
	else
		if (m.now.y == 0) m.dir = m.mv = DirDown;//上スタート
		else
			if (m.now.x == x_size-1) m.dir = m.mv = DirLeft;//右端
			else
				if (m.now.y == y_size-1)m.dir = m.mv = DirUp;//下端
}