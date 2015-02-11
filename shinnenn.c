//2015/02/09  4:07

//=================================
// $BLBO)C5:w%5%s%W%k(B
// $BKh2s!">e"*1&"*2<"*:8$N=g$KDL$l$k$+%A%'%C%/$9$k(B
// $B$3$N%W%m%0%i%`$O!"$"$k>r7o$rK~$?$9LBO)$G$O!"(B
// $B@h$K?J$^$J$/$J$k!#(B
//=================================
#include "shinnenn.h"
#include "maze.h"
//#include "move.h"
  #include "r_move.h"

//#include "s_move.h"
//=================================
// $B%W%l!<%d>pJs(B
//=================================
static	Funcs funcs = { "神々の遊び", init, walkAround };
//=================================
// $B8x3+4X?t(B
//=================================
Funcs* getGroup05Info(void) { return &funcs; }


int x_size, y_size;

int self_chk= 0;//自分のマップチェック用




//$BFbIt4X?t(B
mp m;
static int once = 0;//$B:G=i$@$1(B


static int	walkAround(void){
	
		x_size = getMazeWidth();
		y_size = getMazeHeight();
	

	if (once == 0){
		init();
		once = 1;
		return m.mv;
	}
	r_move();//右優先	
	return m.mv;
}


static void init(void){

	int i, j;

	//マップカウンタをリセット
	for (i = 0; i < 50; i++){
		for (j = 0; j < 30; j++){
			m.cnt[i][j] = 0;
		}
	}
	m.now = getCurrentPosition();

	if (m.now.x == 0 && m.now.y == 12)self_chk=1;//自己マップ第一条件確認

	m.cnt[m.now.x][m.now.y] = 1000;
	m.stat[m.now.x][m.now.y] = wall;//$BJI(B
	m.old.x = m.now.x, m.old.y = m.now.y;
	if (m.now.x == 0){
		
	    if (canMove(DirDown) == MapGoal)m.mv = DirDown;
		else if (canMove(DirUp) == MapGoal)m.mv = DirUp;
		else m.mv = m.dir = DirRight;
	}

	if (m.now.y == 0)
	if (canMove(DirRight) == MapGoal)m.mv = DirRight;
		else if (canMove(DirLeft) == MapGoal)m.mv = DirLeft;
		
		else m.dir = m.mv = DirDown;//$B>e%9%?!<%H(B

	if (m.now.x == x_size - 1) {
		
		if (canMove(DirDown) == MapGoal)m.mv = DirDown;
		else if (canMove(DirUp) == MapGoal)m.mv = DirUp;
		else m.dir = m.mv = DirLeft;//$B1&C<(B
	}


	if (m.now.y == y_size - 1){
		if (canMove(DirRight) == MapGoal)m.mv = DirRight;
		else if (canMove(DirLeft) == MapGoal)m.mv = DirLeft;
		else  m.dir = m.mv = DirUp;//$B2<C<(B
	}
}

//完成形？

//2015年2月8日


#include"maze.h"
#include "shinnenn.h"

#include "s_sort.h"
#include <stdlib.h>//qsort$BMQ(B

//#include "move.h"

#include "r_move.h"

#include "kabegiwa.h"

int t_cnt[4] = { 0 };//一時カウント

static int old_dir;

static int times = 0;

static int stk_cnt[100][100] = { 0 };



//void r_move(void);
//int mv_chk(mp* x);//$B<~0O$NDL9T2s?t$r%A%'%C%/$70lHV>/$J$$J}8~$XJV$9!J>e#0!$1&#1!$2<#2!":8#3!K(B
static int dirsort(void);//$B<~0O$NDL9T2s?t%A%'%C%/$7$F0lHV>/$J$$J}8~$rJV$9(B
static int mv_chk(mp* x);


void r_move(void){
	int same;

	//if (m.cnt[m.now.x][m.now.y] == 6){
	// m.cnt[m.now.x][m.now.y] = 1000; //$BJI(B
	//}
	m.now = getCurrentPosition();//$B8=:_0LCV$r<hF@(B
	same = mv_chk(&m);

	times++;//今何手目か

	stk_cnt[m.now.x][m.now.y] = times;


	m.cnt[m.now.x][m.now.y]++; //現在位置カウント


	switch (m.dir){
	case 0://上


		/*if (self_chk == 4){
		if (m.now.x == 4 && m.now.y == 12){
		self_chk = 5;

		old_dir = m.dir = m.mv = DirRight;

		break;
		}
		}*/

		//前と座標が変わってなかったら一歩前を壁とする
		if (same == 1){ m.cnt[m.now.x][m.now.y - 1] = 1000; }



		//壁の近くでゴールチェック
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}


		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }

		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }


		//////*右が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1000 && m.cnt[m.now.x + 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		////////左上が１で壁に囲まれてたら進む
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1000 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1000){
			if (m.cnt[m.now.x - 2][m.now.y - 1] == 1000 && m.cnt[m.now.x][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		//////*右上が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x + 1][m.now.y - 1] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1000){
			if (m.cnt[m.now.x + 1][m.now.y] == 1000 && m.cnt[m.now.x + 1][m.now.y - 2] == 1000){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		//左２つが
		if (m.cnt[m.now.x - 2][m.now.y ] >= 1 && m.cnt[m.now.x - 2][m.now.y] != 1000 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1000){
			if ( m.cnt[m.now.x-2][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		//上が壁で左下が壁の場合で左が帰りの通路
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1000 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1000){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}

		



		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }

		old_dir = m.dir = m.mv = dirsort();
			

		break;
	case 1://右		
		//前と座標が変わってなかったら一歩前を壁とする
		if (same == 1){ m.cnt[m.now.x + 1][m.now.y] = 1000; }


		/*if (self_chk == 1){

		if (m.now.x == 1 && m.now.y == 12){
		if (canMove(DirRight) == MapAisle)
		old_dir = m.dir = m.mv = DirRight;
		break;
		}


		if (m.now.x==2 && m.now.y==12){

		if (canMove(DirRight) == MapWall){
		self_chk = 2;
		old_dir = m.dir = m.mv = DirDown;
		break;
		}
		}else
		old_dir = m.dir = m.mv = DirRight;
		break;
		}

		if (self_chk == 3){
		if (m.now.x==4&& m.now.y==13){
		self_chk = 4;
		old_dir = m.dir = m.mv = DirUp;

		break;


		}else
		old_dir = m.dir = m.mv = DirRight;

		}
		if (self_chk == 5){
		old_dir = m.dir = m.mv = DirRight;
		break;

		}*/



		//壁の近くでゴールチェック
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}



		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }

		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }

		//////*下が１で壁に囲まれてたら
		if (m.cnt[m.now.x][m.now.y + 1] >= 1 && m.cnt[m.now.x][m.now.y + 1] != 1000 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1000 && m.cnt[m.now.x + 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 2; break;
			}
		}
		//////*右上が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x + 1][m.now.y - 1] != 1000 && same == 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1000){
			if (m.cnt[m.now.x + 1][m.now.y] == 1000 && m.cnt[m.now.x + 1][m.now.y - 2] == 1000){
				old_dir = m.dir = m.mv = 0; break;
			}
		}
		////右下が１で壁に囲まれてたら
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1000 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1000){
			if (m.cnt[m.now.x][m.now.y + 1] == 1000 && m.cnt[m.now.x + 2][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//下が壁で右上が壁の場合で右が帰りの通路
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1000 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1000){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }


		old_dir = m.dir = m.mv = dirsort();
		

		break;
	case 2://下




		/*if (self_chk == 2){
		if (m.now.x == 2 && m.now.y == 13){
		self_chk = 3;
		old_dir = m.dir = m.mv = DirRight;
		break;
		}


		}
		*/




		//前と座標が変わってなかったら一歩前を壁とする
		if (same == 1){ m.cnt[m.now.x][m.now.y + 1] = 1000; }

		//壁の近くでゴールチェック
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}


		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }

		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }

		////*左が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1000 && m.cnt[m.now.x - 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		////右下が１で壁に囲まれてたら
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1000 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1000){
			if (m.cnt[m.now.x][m.now.y + 1] == 1000 && m.cnt[m.now.x + 2][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		//////*左下が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1000){
			if (m.cnt[m.now.x - 1][m.now.y] == 1000 && m.cnt[m.now.x - 1][m.now.y + 2] == 1000){
				old_dir = m.dir = m.mv = 2; break;
			}
		}

		//下が壁で右上が壁の場合で右が帰りの通路
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1000 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1000){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }

		old_dir = m.dir = m.mv = dirsort();
		
		break;
	case 3://左


		//前と座標が変わってなかったら一歩前を壁とする
		if (same == 1){ m.cnt[m.now.x - 1][m.now.y] = 1000; }

		//壁の近くでゴールチェック
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}

		//封鎖
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }


		//////上が１で壁に囲まれてたら進む
		if (m.cnt[m.now.x][m.now.y - 1] >= 1 && m.cnt[m.now.x][m.now.y - 1] != 1000 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1000 && m.cnt[m.now.x + 1][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 0; break;
			}
		}
		//////*左下が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1000 && same == 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1000){
			if (m.cnt[m.now.x - 1][m.now.y] == 1000 && m.cnt[m.now.x - 1][m.now.y + 2] == 1000){
				old_dir = m.dir = m.mv = 2; break;
			}
		}

		////////左上が１で壁に囲まれてたら進む
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1000 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1000){
			if (m.cnt[m.now.x - 2][m.now.y - 1] == 1000 && m.cnt[m.now.x][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}


		//上が壁で左下が壁の場合で左が帰りの通路
		if (m.cnt[m.now.x - 1][m.now.y ] >= 1 && m.cnt[m.now.x - 1][m.now.y ] != 1000 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1000){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1000 ){
				old_dir = m.dir = m.mv = 3; break;
			}
		}



		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }



		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }

		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }

		old_dir = m.dir = m.mv = dirsort();
		
		break;
	}


	//old_dir=m.dir=m.mv = dirsort();
	m.old.x = m.now.x; m.old.y = m.now.y;
}
//$BA0$HF1$8$@$C$?$i#1$r$=$l0J30$O#0$rJV$9(B
int mv_chk(mp* x){
	if (x->now.x == x->old.x &&x->now.y == x->old.y)
		return 1;
	else
		return 0;
}
static int dirsort(void){
	tmp _t;
	tmp *pt;
	pt = &_t;



	//右から
	switch (m.dir){
	case 0://上



		_t.sortcnt[0] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up  
		_t.sortdir[0] = 0;



		_t.sortcnt[1] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left		
		_t.sortdir[1] = 3;

		_t.sortcnt[2] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[2] = 1;

		_t.sortcnt[3] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[3] = 2;

		s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else 	if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;

		break;
	case 1://Right

		_t.sortcnt[0] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[0] = 1;
		_t.sortcnt[1] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[1] = 0;

		_t.sortcnt[2] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[2] = 2;

		_t.sortcnt[3] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		_t.sortdir[3] = 3;
		//
		 s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;





		break;

	case 2://Down
		_t.sortcnt[0] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[0] = 2;
		_t.sortcnt[1] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[1] = 1;


		_t.sortcnt[2] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		_t.sortdir[2] = 3;

		_t.sortcnt[3] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[3] = 0;


		s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else 	if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;

		break;
	case 3://Left

		_t.sortcnt[0] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left       
		_t.sortdir[0] = 3;
		_t.sortcnt[1] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down        
		_t.sortdir[1] = 2;


		_t.sortcnt[2] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[2] = 0;

		_t.sortcnt[3] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[3] = 1;

		s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);
		
		if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else 	if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else 	if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;



		break;
	}
	return _t.sortdir[0];
}

#include "s_sort.h"
#include "shinnenn.h"



//＊状況に応じて型を変更する


int med3(int x, int y, int z)
/* x, y, z の中間値を返す */
{
	if (x < y)
		if (y < z) return y; else if (z < x) return x; else return z; else
			if (z < y) return y; else if (x < z) return x; else return z;
}

//構造体のメンバソート
void s_sort(tmp* a, int left, int right)
/* クイックソート
* a     : ソートする配列を含んだの元の構造体
* left  : ソートするデータの開始位置
* right : ソートするデータの終了位置
*/


{



	if (left < right) {
		int i = left, j = right;
		int temp, temp2, pivot = med3(a->sortcnt[i], a->sortcnt[i + (j - i) / 2], a->sortcnt[j]); /* (i+j)/2ではオーバーフローしてしまう */
		while (1) { /* a[] を pivot 以上と以下の集まりに分割する */
			while (a->sortcnt[i] < pivot) i++; /* a[i] >= pivot となる位置を検索 */
			while (pivot < a->sortcnt[j]) j--; /* a[j] <= pivot となる位置を検索 */
			if (i >= j) break;
			temp = a->sortcnt[i]; temp2 = a->sortdir[i];
			a->sortcnt[i] = a->sortcnt[j]; a->sortdir[i] = a->sortdir[j];
			a->sortcnt[j] = temp; a->sortdir[j] = temp2; /* a[i],a[j] を交換 */
			i++; j--;
		}
		s_sort(a, left, i - 1);  /* 分割した左を再帰的にソート */
		s_sort(a, j + 1, right); /* 分割した右を再帰的にソート */
	}
}

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