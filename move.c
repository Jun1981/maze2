#include"maze.h"
#include "shinnenn.h"
#include "move.h"
#include "s_sort.h"
#include <stdlib.h>//qsort$BMQ(B
void move(void);
int mv_chk(mp* x);//$B<~0O$NDL9T2s?t$r%A%'%C%/$70lHV>/$J$$J}8~$XJV$9!J>e#0!$1&#1!$2<#2!":8#3!K(B
static int dirsort(void);//$B<~0O$NDL9T2s?t%A%'%C%/$7$F0lHV>/$J$$J}8~$rJV$9(B
void move(void){
	int same;
	m.cnt[m.now.x][m.now.y]++; //$B:BI8$NDL$C$?2s?t$r!\#1(B
	//if (m.cnt[m.now.x][m.now.y] == 6){
	// m.cnt[m.now.x][m.now.y] = 1000; //$BJI(B
	//}
	m.now = getCurrentPosition();//$B8=:_0LCV$r<hF@(B
	same = mv_chk(&m);


	
		switch (m.dir){
		case 0://ã

			if (m.now.y == 1){//ã’[
				if (canMove(DirUp) == MapGoal){
					m.mv = DirUp; return;
				}
				else{
					m.cnt[m.now.x][m.now.y - 1] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}
			}

			if (m.now.x == 1){//¶’[
				if (canMove(DirLeft) == MapGoal){					
					m.mv = DirLeft;
					return;

				}
				else{
					m.cnt[m.now.x - 1][m.now.y] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}
			}

			if (m.now.x == x_size-2){//‰E’[
				if (canMove(DirRight) == MapGoal){
					m.mv = DirRight;
					return;
				}
				else{
					m.cnt[m.now.x + 1][m.now.y] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}

			}




			if (same == 1){
				m.cnt[m.now.x][m.now.y - 1] = 1000;//$BJI(B
				m.stat[m.now.x][m.now.y - 1] = wall;
			}
			break;
		case 1://‰E

			if (m.now.x == x_size - 2){//‰E’[
				if (canMove(DirRight) == MapGoal){
					m.mv = DirRight; return;
				}else{
					m.cnt[m.now.x + 1][m.now.y] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}
			}



			//•ÇÛ‚ÌƒS[ƒ‹Šm”F
			if (m.now.y == 1){//‰EŒü‚«‚Ìã
				if (canMove(DirUp) == MapGoal){
					m.mv = DirUp;
					return;
				}
				else
				{
					m.cnt[m.now.x ][m.now.y-1] = 1000;//•Ç
				//	m.cnt[m.now.x][m.now.y] += 3;
				}

			}
			if (m.now.y == y_size - 2){//‰EŒü‚«‚Ì‰º
				if (canMove(DirDown) == MapGoal){
					m.mv = DirDown;
					return;
				}
				else{
					m.cnt[m.now.x][m.now.y + 1] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}

			}
			//////////////////////////////////////////









			if (same == 1){
				m.cnt[m.now.x + 1][m.now.y] = 1000;//$BJI(B
				m.stat[m.now.x + 1][m.now.y] = wall;
			}
			break;
		case 2://‰º

			if (m.now.y == y_size - 2){//‰ºŒü‚«@‰º’[
				if (canMove(DirDown) == MapGoal){
					m.mv = DirDown; return;
				}
				else{
					m.cnt[m.now.x][m.now.y + 1] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}
			}





			//•ÇÛ‚ÌƒS[ƒ‹Šm”F
			if (m.now.x == 1){//‰ºŒü‚«¶’[
				if (canMove(DirLeft) == MapGoal){
					m.mv = DirLeft;
					return;
				}
				else
				{
					m.cnt[m.now.x-1][m.now.y ] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}
			}


			if (m.now.x == x_size - 2){//‰ºŒü‚«‰E’[
				if (canMove(DirRight) == MapGoal){
					m.mv = DirRight;
					return;
				}
				else{
					//m.cnt[m.now.x][m.now.y] += 3;
					m.cnt[m.now.x + 1][m.now.y] = 1000;//•Ç
				}
			}
			//////////////////////////////////////////

			if (same == 1){
				m.cnt[m.now.x][m.now.y + 1] = 1000;//$BJI(B
				m.stat[m.now.x][m.now.y + 1] = wall;
			}
			break;
		case 3://¶


			if (m.now.x ==1 )//¶Œü‚«¶’[
				if (canMove(DirLeft) == MapGoal){
					m.mv = DirLeft; return;
				}
				else{
					m.cnt[m.now.x - 1][m.now.y] = 1000;//•Ç
					//m.cnt[m.now.x][m.now.y] += 3;
				}

			//•ÇÛ‚ÌƒS[ƒ‹Šm”F
			if (m.now.y == 1){//¶Œü‚«ã’[
				if (canMove(DirUp) == MapGoal){
					m.mv = DirUp;
					return;
				}
				else{
				//	m.cnt[m.now.x][m.now.y] += 3;
					m.cnt[m.now.x][m.now.y - 1] = 1000;//•Ç
				}

			}
			if (m.now.y == y_size - 2){//¶Œü‚«‰º’[
				if (canMove(DirDown) == MapGoal){
					m.mv = DirDown;
					return;
				}
				else{
					//m.cnt[m.now.x][m.now.y] += 3;
					m.cnt[m.now.x][m.now.y + 1] = 1000;//•Ç
				}
			}
			//////////////////////////////////////////
			if (same == 1){
				m.cnt[m.now.x - 1][m.now.y] = 1000;//$BJI(B
				m.stat[m.now.x - 1][m.now.y] = wall;
			}
			break;
		}
	
	//m.dir=m.mv=dirsort();
	m.dir = m.mv = dirsort();
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

	//ŽžŒv‰ñ‚è
	switch (m.dir){
	case 0://$B>e(B
		_t.sortcnt[0] = m.cnt[m.now.x - 1][m.now.y];//Left		
		_t.sortdir[0] = 3;

		_t.sortcnt[1] = m.cnt[m.now.x][m.now.y - 1];//Up  
		_t.sortdir[1] = 0;

		_t.sortcnt[2] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[2] = 1;


		//_t.sortcnt[3] = m.cnt[m.now.x][m.now.y + 1];//Down
		//_t.sortdir[3] = 2;
		//pntsort(&t);
		break;
	case 1://Right

		_t.sortcnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		_t.sortdir[0] = 0;
		_t.sortcnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		_t.sortdir[1] = 1;
		_t.sortcnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[2] = 2;
		
		//_t.sortcnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		//_t.sortdir[3] = 3;
		//pntsort(&t);
		break;
	case 2://Down
		_t.sortcnt[0] = m.cnt[m.now.x + 1][m.now.y];//$B0l8D1&$N%+%&%s%H(B
		_t.sortdir[0] = 1;

		_t.sortcnt[1] = m.cnt[m.now.x][m.now.y + 1];//Down
		_t.sortdir[1] = 2;
		_t.sortcnt[2] = m.cnt[m.now.x - 1][m.now.y];//Left
		_t.sortdir[2] = 3;
		
		//_t.sortcnt[3] = m.cnt[m.now.x][m.now.y - 1];//Up
		//_t.sortdir[3] = 0;
		break;
	case 3://Left
		_t.sortcnt[0] = m.cnt[m.now.x][m.now.y + 1];//$B0l8D2<(B
		_t.sortdir[0] = 2;

		_t.sortcnt[1] = m.cnt[m.now.x - 1][m.now.y];//$B0l8D:8(B
		_t.sortdir[1] = 3;
		_t.sortcnt[2] = m.cnt[m.now.x][m.now.y - 1];//$B0l8D>e(B
		_t.sortdir[2] = 0;
		
		//_t.sortcnt[3] = m.cnt[m.now.x + 1][m.now.y];//$B0l8D1&$N%+%&%s%H(B
		//_t.sortdir[3] = 1;
		break;
	}
	s_sort(&_t, 0, 2);
	return _t.sortdir[0];
}