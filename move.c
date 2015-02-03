
#include"maze.h"
#include "shinnenn.h"

#include "move.h"

#include "s_sort.h"

#include <stdlib.h>//qsort用

void move(void);
int mv_chk(map* x);//周囲の通行回数をチェックし一番少ない方向へ返す（上０，右１，下２、左３）

static int dirsort(void);//周囲の通行回数チェックして一番少ない方向を返す








void move(void){
	int same;
	
	m.cnt[m.now.x][m.now.y]++;	//座標の通った回数を＋１
	//if (m.cnt[m.now.x][m.now.y] == 6){
	//	m.cnt[m.now.x][m.now.y] = 1000; //壁

	//}
	m.now = getCurrentPosition();//現在位置を取得
	same = mv_chk(&m);


	

	if (same ==1){

		

		switch(m.dir){

		case 0:
			m.cnt[m.now.x][m.now.y - 1] = 1000;//壁
			m.stat[m.now.x][m.now.y - 1] = wall;
			break;
		case 1:
			m.cnt[m.now.x+1][m.now.y ] = 1000;//壁
			m.stat[m.now.x+1][m.now.y ] = wall;
			break;
		case 2://下

			m.cnt[m.now.x][m.now.y + 1] = 1000;//壁
			m.stat[m.now.x][m.now.y + 1] = wall;
			break;
		case 3:
			m.cnt[m.now.x-1][m.now.y ] = 1000;//壁
			m.stat[m.now.x-1][m.now.y ] = wall;
			break;




		}
		
	
	
	};

	//m.dir=m.mv=dirsort();

	m.dir = m.mv = dirsort();
	m.old.x = m.now.x; m.old.y = m.now.y;



}



//前と同じだったら１をそれ以外は０を返す
int mv_chk(map* x){

	if (x->now.x == x->old.x &&x->now.y == x->old.y)
		return 1;	
	else 
		return 0;

}


static int dirsort(void){


	

	tmp _t;
	tmp *pt;

	pt = &_t;
	
	switch (m.dir){

	case 0://上
		_t.sortcnt[0] = m.cnt[m.now.x][m.now.y - 1];//一個上
		_t.sortdir[0] = 0;

		_t.sortcnt[1] = m.cnt[m.now.x + 1][m.now.y];//一個右のカウント
		_t.sortdir[1] = 1;

		
		_t.sortcnt[2] = m.cnt[m.now.x - 1][m.now.y];//一個左
		_t.sortdir[2] = 3;

		
		_t.sortcnt[3] = m.cnt[m.now.x][m.now.y + 1];//一個下
		_t.sortdir[3] = 2;

		//pntsort(&t);

		


		break;
	case 1://右
		
		_t.sortcnt[0] = m.cnt[m.now.x + 1][m.now.y];//一個右のカウント
		_t.sortdir[0] = 1;

	
		_t.sortcnt[1] = m.cnt[m.now.x][m.now.y + 1];//一個下
		_t.sortdir[1] = 2;

		
		_t.sortcnt[2] = m.cnt[m.now.x][m.now.y - 1];//一個上
		
		_t.sortdir[2] = 0;

	
		_t.sortcnt[3] = m.cnt[m.now.x - 1][m.now.y];//一個左
		_t.sortdir[3] = 3;

		//pntsort(&t);

		
		break;
	case 2://下

		_t.sortcnt[0] = m.cnt[m.now.x][m.now.y + 1];//一個下
		_t.sortdir[0] = 2;
		
		

		_t.sortcnt[1] = m.cnt[m.now.x - 1][m.now.y];//一個左
		_t.sortdir[1] = 3;

		_t.sortcnt[2] = m.cnt[m.now.x + 1][m.now.y];//一個右のカウント
		_t.sortdir[2] = 1;

		
		_t.sortcnt[3] = m.cnt[m.now.x][m.now.y - 1];//一個上
		_t.sortdir[3] = 0;

		

	
		break;
	case 3://左
		_t.sortcnt[0] = m.cnt[m.now.x - 1][m.now.y];//一個左
		_t.sortdir[0] = 3;

		_t.sortcnt[1] = m.cnt[m.now.x][m.now.y - 1];//一個上
		_t.sortdir[1] = 0;

		_t.sortcnt[2] = m.cnt[m.now.x][m.now.y + 1];//一個下
		_t.sortdir[2] = 2;

		_t.sortcnt[3] = m.cnt[m.now.x + 1][m.now.y];//一個右のカウント
		_t.sortdir[3] = 1;

		
		break;

	}

	s_sort(&_t, 0, 3);
	return _t.sortdir[0];

	

}
