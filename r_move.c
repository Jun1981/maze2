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
			old_dir=m.dir=m.mv = kabegiwa(); break;
		}


		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;

	




		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 1;  break; }
		
		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir=m.dir=m.mv = 0; break; }


		//////*右が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1000 && m.cnt[m.now.x + 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		////////左上が１で壁に囲まれてたら進む
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1000 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x ][m.now.y + 1] != 1000){
			if (m.cnt[m.now.x - 2][m.now.y - 1] == 1000 && m.cnt[m.now.x ][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		


		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 3;  break; }
		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir=m.dir=m.mv = 2;  break; }

		old_dir=m.dir=m.mv = dirsort();





		//前３方向の回数をチェックして一番少ない方を向く(進行方向優先）




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
			old_dir=m.dir=m.mv = kabegiwa(); break;
		}



		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir=m.dir=m.mv = 2;  break; }
		
		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 1;  break; }

		//////*下が１で壁に囲まれてたら
		if (m.cnt[m.now.x][m.now.y + 1] >= 1 && m.cnt[m.now.x][m.now.y + 1] != 1000 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1000 && m.cnt[m.now.x + 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 2; break;
			}
		}
		//////*右上が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x + 1][m.now.y - 1] != 1000 && same == 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x-1][m.now.y ] != 1000){
			if (m.cnt[m.now.x + 1][m.now.y ] == 1000 && m.cnt[m.now.x + 1][m.now.y -2] == 1000){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir=m.dir=m.mv = 0; break; }
		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 3;  break; }


		old_dir=m.dir=m.mv = dirsort();








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
			old_dir=m.dir=m.mv = kabegiwa(); break;
		}


		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 3;  break; }
		
		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir=m.dir=m.mv = 2;  break; }

		////*左が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1000 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1000 && m.cnt[m.now.x - 1][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		////右下が１で壁に囲まれてたら
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1000 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1000){
			if (m.cnt[m.now.x ][m.now.y + 1] == 1000 && m.cnt[m.now.x + 2][m.now.y + 1] == 1000){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 1;  break; }
		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir=m.dir=m.mv = 0; break; }

		old_dir=m.dir=m.mv = dirsort();









		break;
	case 3://左


		//前と座標が変わってなかったら一歩前を壁とする
		if (same == 1){ m.cnt[m.now.x - 1][m.now.y] = 1000; }

		//壁の近くでゴールチェック
		if (kabegiwa() != -1){
			old_dir=m.dir=m.mv = kabegiwa(); break;
		}

		//封鎖
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//上が０だったら進む
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir=m.dir=m.mv = 0; break; }
		

		//////上が１で壁に囲まれてたら進む
		if (m.cnt[m.now.x][m.now.y - 1] >= 1 && m.cnt[m.now.x][m.now.y - 1] != 1000 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1000 && m.cnt[m.now.x + 1][m.now.y - 1] == 1000){
				old_dir = m.dir = m.mv = 0; break;
			}
		}
		//////*左下が１で壁に囲まれてたら(ルーム脱出用）
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1000 && same == 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x +1][m.now.y ] != 1000){
			if (m.cnt[m.now.x - 1][m.now.y ] == 1000 && m.cnt[m.now.x - 1][m.now.y + 2] == 1000){
				old_dir = m.dir = m.mv = 2; break;
			}
		}


		//左が０だったら進む
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 3;  break; }

		

		//下が０だったら進む
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir=m.dir=m.mv = 2;  break; }

		//右が０だったら進む
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir=m.dir=m.mv = 1;  break; }

		old_dir=m.dir=m.mv = dirsort();




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

		//_t.sortcnt[3] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		//_t.sortdir[3] = 2;

		//s_sort(&_t, 0, 3);
		s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		//else 	if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;




		break;
	case 1://Right

		_t.sortcnt[0] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[0] = 1;
		_t.sortcnt[1] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[1] = 0;

		_t.sortcnt[2] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[2] = 2;

		//_t.sortcnt[3] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		//_t.sortdir[3] = 3;
		//
		//s_sort(&_t, 0, 3);
		s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		//else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;





		break;

	case 2://Down
		_t.sortcnt[0] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[0] = 2;
		_t.sortcnt[1] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[1] = 1;


		_t.sortcnt[2] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		_t.sortdir[2] = 3;

		//_t.sortcnt[3] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		//_t.sortdir[3] = 0;


		//s_sort(&_t, 0, 3);
		s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else 	if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		//else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;

		break;
	case 3://Left

		_t.sortcnt[0] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left       
		_t.sortdir[0] = 3;
		_t.sortcnt[1] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down        
		_t.sortdir[1] = 2;


		_t.sortcnt[2] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[2] = 0;

		//_t.sortcnt[3] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		//_t.sortdir[3] = 1;

		//s_sort(&_t, 0, 3);
		s_sort(&_t, 0, 2);




		if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else 	if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		//else 	if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;



		break;
	}
	return _t.sortdir[0];
}