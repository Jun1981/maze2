
//2015/02/13  3:24

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
static	Funcs funcs = { "ê_ÅXÇÃóVÇ—", init, walkAround };
//=================================
// $B8x3+4X?t(B
//=================================
Funcs* getGroup05Info(void) { return &funcs; }


static int x_size, y_size;

static int self_chk= 0;//é©ï™ÇÃÉ}ÉbÉvÉ`ÉFÉbÉNóp




//$BFbIt4X?t(B
static mp m;
static int once = 0;//$B:G=i$@$1(B


static int	walkAround(void){
	
	
	if(once==1){
	r_move();//âEóDêÊ	
	}

	if (once == 0){		
		init();				
		return m.mv;
			
	}
	
		
		




	
	
	
	return m.mv;
}


static void init(void){

	int i, j;
	once=1;

	x_size = getMazeWidth();
		y_size = getMazeHeight();

	//É}ÉbÉvÉJÉEÉìÉ^ÇÉäÉZÉbÉg
	for (i = 0; i < 100; i++){
		for (j = 0; j < 100; j++){
			m.cnt[i][j] = 0;
		}
	}
	m.now = getCurrentPosition();

	//if (m.now.x == 0 && m.now.y == 12)self_chk=1;//é©å»É}ÉbÉvëÊàÍèåèämîF

	//m.cnt[m.now.x][m.now.y] ++ ;
	//m.stat[m.now.x][m.now.y] = wall;//$BJI(B
	m.old.x = m.now.x; m.old.y = m.now.y;
	
	//ÉXÉ^Å[Égínì_Ç™ç∂í[ÇÃèÍçá
	if (m.now.x == 0){	
		if (canMove(0) == MapGoal){
			m.mv = 0;
			
			
		}
		else if(canMove(2)==MapGoal){
			m.mv=2;
			
			
		}		
		m.mv = 1;



	}else
	//ÉXÉ^Å[Égínì_Ç™âEí[
	if(m.now.x==x_size-1){

		if (canMove(DirDown) == MapGoal){
			m.mv = DirDown;

		}
		else if(canMove(DirUp)==MapGoal){
			m.mv=DirUp;	

		}
		else
			m.mv = DirLeft;



	}

	//ÉXÉ^Å[Égínì_Å@è„
	if(m.now.y==0){

		if (canMove(DirRight) == MapGoal){
			m.mv = DirRight;

		}
		else if(canMove(DirLeft)==MapGoal){
			m.mv=DirLeft;	

		}
		else
			m.mv = DirDown;

	}else
	//ÉXÉ^Å[Égínì_Å@â∫
	if(m.now.y==y_size-1){

		if (canMove(DirLeft) == MapGoal){
			m.mv = DirLeft;
			
		}
		else if(canMove(DirRight)==MapGoal){
			m.mv=DirRight;	
			
		}
		else
		m.mv = DirUp;

	}

}

//äÆê¨å`ÅH

//2015îN2åé8ì˙


#include"maze.h"


#include "s_sort.h"


//#include "move.h"

#include "r_move.h"

#include "kabegiwa.h"

static int t_cnt[4] = { 0 };//àÍéûÉJÉEÉìÉg

static int old_dir;

static int times = 0;

static int stk_cnt[100][100] = { 0 };



//void r_move(void);
//int mv_chk(mp* x);//$B<~0O$NDL9T2s?t$r%A%'%C%/$70lHV>/$J$$J}8~$XJV$9!J>e#0!$1&#1!$2<#2!":8#3!K(B
static int dirsort(void);//$B<~0O$NDL9T2s?t%A%'%C%/$7$F0lHV>/$J$$J}8~$rJV$9(B
static int mv_chk(mp* x);


static void r_move(void){
	int same;

	//if (m.cnt[m.now.x][m.now.y] == 6){
	// m.cnt[m.now.x][m.now.y] = 1001; //$BJI(B
	//}
	m.now = getCurrentPosition();//$B8=:_0LCV$r<hF@(B
	same = mv_chk(&m);

	times++;//ç°âΩéËñ⁄Ç©

	stk_cnt[m.now.x][m.now.y] = times;


	m.cnt[m.now.x][m.now.y]++; //åªç›à íuÉJÉEÉìÉg


	switch (m.dir){
	case 0://è„

		//ëOÇ∆ç¿ïWÇ™ïœÇÌÇ¡ÇƒÇ»Ç©Ç¡ÇΩÇÁàÍï‡ëOÇï«Ç∆Ç∑ÇÈ
		if (same == 1){ m.cnt[m.now.x][m.now.y - 1] = 1001; }
		

		//ï«ÇÃãﬂÇ≠Ç≈ÉSÅ[ÉãÉ`ÉFÉbÉN
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}
		//ïïçΩ
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] =1000;


		//âEÇ™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
		
		////è„â∫Ç™ï«Ç≈ç∂âEÇ™ÇOà»è„
		//if(m.now.x!=0 && m.cnt[m.now.x][m.now.y+1]==1001 && m.cnt[m.now.x][m.now.y-1]==1001 && m.cnt[m.now.x-1][m.now.y]>0 ){
		//	old_dir = m.dir = m.mv = 3;
		//	break;;

		//}

		



		


		//////*âEÇ™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0){
			if (m.cnt[m.now.x + 1][m.now.y - 1]>0 && m.cnt[m.now.x + 1][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		////////ç∂è„Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁêiÇﬁ
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 2][m.now.y - 1] == 1001 && m.cnt[m.now.x][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		//////*âEè„Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x + 1][m.now.y - 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] >0){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		////ç∂ÇQÇ¬Ç™
		//if (m.cnt[m.now.x - 2][m.now.y ] >= 1 && m.cnt[m.now.x - 2][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
		//	if ( m.cnt[m.now.x-2][m.now.y + 1] == 1001){
		//		old_dir = m.dir = m.mv = 3; break;
		//	}
		//}
		//è„Ç™ï«Ç≈ç∂â∫Ç™ï«ÇÃèÍçáÇ≈ç∂Ç™ãAÇËÇÃí òH
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}

		


		//è„Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}
		//ç∂Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}
		//â∫Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}
		old_dir = m.dir = m.mv = dirsort();
			

		break;
	case 1://âE		
		//ëOÇ∆ç¿ïWÇ™ïœÇÌÇ¡ÇƒÇ»Ç©Ç¡ÇΩÇÁàÍï‡ëOÇï«Ç∆Ç∑ÇÈ
		if (same == 1){ m.cnt[m.now.x + 1][m.now.y] = 1001; }
		



		//ï«ÇÃãﬂÇ≠Ç≈ÉSÅ[ÉãÉ`ÉFÉbÉN
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}

		
		//ïïçΩ
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] =1000;


		//â∫Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}

		


		////ç∂âEÇ™ï«Ç≈è„â∫Ç™ÇOà»è„
		//if(m.cnt[m.now.x-1][m.now.y]==1001 && m.cnt[m.now.x+1][m.now.y]==1001 && m.cnt[m.now.x][m.now.y-1]>0 &&  m.cnt[m.now.x][m.now.y+1]>0 && m.cnt[m.now.x][m.now.y-1]!=1001 &&  m.cnt[m.now.x][m.now.y+1]!=1001){
		//	old_dir = m.dir = m.mv = 0;
		//	break;

		//}

		//â∫Ç™ï«Ç≈ç∂âEÇ™ÇOà è„

		if(m.cnt[m.now.x][m.now.y+1]==1001 &&  m.cnt[m.now.x-1][m.now.y]>0 &&  m.cnt[m.now.x+1][m.now.y]>0 && m.cnt[m.now.x-1][m.now.y]!=1001 &&  m.cnt[m.now.x+1][m.now.y]!=1001){
			old_dir = m.dir = m.mv = 1;
			break;

		}

		/////*âEè„Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x+1][m.now.y - 1] != 1001 && same == 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] >0){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		
		//////*â∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ
		if (m.cnt[m.now.x][m.now.y + 1] >= 1 && m.cnt[m.now.x][m.now.y + 1] != 1001 && same != 1 ){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001 && m.cnt[m.now.x + 1][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 2; break;
			}
		}
		/////*ç∂â∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] == 1001){
				old_dir = m.dir = m.mv = 0; break;
			}
		}
		////âEâ∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 ){
			if (m.cnt[m.now.x][m.now.y + 1] == 1001 && m.cnt[m.now.x + 2][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//â∫Ç™ï«Ç≈âEè„Ç™ï«ÇÃèÍçáÇ≈âEÇ™ãAÇËÇÃí òH
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}




		

			//âEÇ™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
			//è„Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}
		//ç∂Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}


		old_dir = m.dir = m.mv = dirsort();
		

		break;
	case 2://â∫




		/*if (self_chk == 2){
		if (m.now.x == 2 && m.now.y == 13){
		self_chk = 3;
		old_dir = m.dir = m.mv = DirRight;
		break;
		}


		}
		*/




		//ëOÇ∆ç¿ïWÇ™ïœÇÌÇ¡ÇƒÇ»Ç©Ç¡ÇΩÇÁàÍï‡ëOÇï«Ç∆Ç∑ÇÈ
		if (same == 1){ m.cnt[m.now.x][m.now.y + 1] = 1001; }

		//ï«ÇÃãﬂÇ≠Ç≈ÉSÅ[ÉãÉ`ÉFÉbÉN
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}


		//ïïçΩ
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//ç∂Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}

		
		
		////è„â∫Ç™ï«Ç≈ç∂âEÇ™ÇOà»è„
	
		//if(m.cnt[m.now.x][m.now.y+1]==1001 && m.cnt[m.now.x][m.now.y-1]==1001 && m.cnt[m.now.x-1][m.now.y]>0 &&  m.cnt[m.now.x+1][m.now.y]>0 &&m.cnt[m.now.x-1][m.now.y]!=1001 &&  m.cnt[m.now.x+1][m.now.y]!=1001){
		//	old_dir = m.dir = m.mv = 1;
		//	break;;

		//}
		
		


		

		////*ç∂Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1001 && m.cnt[m.now.x - 1][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		////âEâ∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1001 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x][m.now.y + 1] == 1001 && m.cnt[m.now.x + 2][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		//////*ç∂â∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y] == 1001 && m.cnt[m.now.x - 1][m.now.y + 2] >0){
				old_dir = m.dir = m.mv = 2; break;
			}
		}

		//â∫Ç™ï«Ç≈âEè„Ç™ï«ÇÃèÍçáÇ≈âEÇ™ãAÇËÇÃí òH
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//â∫Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}
		
			//âEÇ™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
			//è„Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}

		old_dir = m.dir = m.mv = dirsort();
		
		break;
	case 3://ç∂


		//ëOÇ∆ç¿ïWÇ™ïœÇÌÇ¡ÇƒÇ»Ç©Ç¡ÇΩÇÁàÍï‡ëOÇï«Ç∆Ç∑ÇÈ
		if (same == 1){ m.cnt[m.now.x - 1][m.now.y] = 1001; }

		//ï«ÇÃãﬂÇ≠Ç≈ÉSÅ[ÉãÉ`ÉFÉbÉN
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}
		//ïïçΩ
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;


			//è„Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}


		////è„â∫Ç™ï«ÇæÇ¡ÇΩÇÁç∂

		//if(m.cnt[m.now.x][m.now.y-1] ==1001 && m.cnt[m.now.x][m.now.y+1]==1001){
		//	 old_dir = m.dir = m.mv =3; break;
		//}


	



	
			
		////ç∂âEÇ™ï«Ç≈è„â∫Ç™ÇOà»è„
		//if(m.cnt[m.now.x-1][m.now.y]==1001 && m.cnt[m.now.x+1][m.now.y]==1001 && m.cnt[m.now.x][m.now.y-1]>0 &&  m.cnt[m.now.x][m.now.y+1]>0 &&  m.cnt[m.now.x][m.now.y-1]!=1001 &&  m.cnt[m.now.x][m.now.y+1]!=1001){
		//	old_dir = m.dir = m.mv = 2;
		//	break;

		//}

		


			//////è„Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁêiÇﬁ
		if (m.cnt[m.now.x][m.now.y - 1] >= 1 && m.cnt[m.now.x][m.now.y - 1] != 1001 && same != 1 ){
			if (m.cnt[m.now.x - 1][m.now.y - 1] >0 && m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 0; break;
			}
		}else
		//////*ç∂â∫Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁ(ÉãÅ[ÉÄíEèoópÅj
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same == 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y] == 1001 && m.cnt[m.now.x - 1][m.now.y + 2] == 1001){
				old_dir = m.dir = m.mv = 2; break;
			}
		}else

		////////ç∂è„Ç™ÇPÇ≈ï«Ç…àÕÇ‹ÇÍÇƒÇΩÇÁêiÇﬁ
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1001 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 2][m.now.y - 1] >0 && m.cnt[m.now.x][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}else


		//è„Ç™ï«Ç≈ç∂â∫Ç™ï«ÇÃèÍçáÇ≈ç∂Ç™ãAÇËÇÃí òH
		if (m.cnt[m.now.x - 1][m.now.y ] >= 1 && m.cnt[m.now.x - 1][m.now.y ] != 1001 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001 ){
				old_dir = m.dir = m.mv = 3; break;
			}
		}



		


		//ç∂Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}
		//â∫Ç™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}

			//âEÇ™ÇOÇæÇ¡ÇΩÇÁêiÇﬁ
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}

		old_dir = m.dir = m.mv = dirsort();
		
		break;
	}


	//old_dir=m.dir=m.mv = dirsort();
	m.old.x = m.now.x; m.old.y = m.now.y;
}
//$BA0$HF1$8$@$C$?$i#1$r$=$l0J30$O#0$rJV$9(B
static int mv_chk(mp* x){
	if (x->now.x == x->old.x &&x->now.y == x->old.y)
		return 1;
	else
		return 0;
}
static int dirsort(void){
	tmp _t;
	tmp *pt;
	pt = &_t;



	//âEÇ©ÇÁ
	switch (m.dir){
	case 0://è„


		//up
		if(m.now.y==0){
			_t.sortcnt[0] = t_cnt[0] = 1001;//Up  

		}else{
			_t.sortcnt[0] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];	
		}
		_t.sortdir[0] = 0;


		//left
		if(m.now.x==0){
			_t.sortcnt[1] = t_cnt[3] = 1001;
		}
		else{
			_t.sortcnt[1] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left		
		}
		_t.sortdir[1] = 3;

		//right
		if(m.now.x==x_size-1){
		_t.sortcnt[2] = t_cnt[1] = 1001;//Right
		}else {
			_t.sortcnt[2] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		}
		_t.sortdir[2] = 1;

		//down
		if(m.now.y==y_size-1){
		_t.sortcnt[3] = t_cnt[2] = 1001;//Down
		}else{
			_t.sortcnt[3] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		}		_t.sortdir[3] = 2;

		s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else 	if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;

		break;
	case 1://Right

			//right
		if(m.now.x==x_size-1){
		_t.sortcnt[0] = t_cnt[1] = 1001;//Right
		}else {
			_t.sortcnt[0] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		}
		_t.sortdir[0] = 1;

		//up
		if(m.now.y==0){
			_t.sortcnt[1] = t_cnt[0] = 1001;//Up  

		}else{
			_t.sortcnt[1] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];	
		}

		_t.sortdir[1] = 0;
		
			//down
		if(m.now.y==y_size-1){
			_t.sortcnt[2] = t_cnt[2] = 1001;//Down
		}else{
			_t.sortcnt[2] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		}_t.sortdir[2] = 2;


		//left
		if(m.now.x==0){
			_t.sortcnt[3] = t_cnt[3] = 1001;
		}
		else{
			_t.sortcnt[3] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left		
		}
		_t.sortdir[3] = 3;

	

	

		//_t.sortcnt[0] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		//_t.sortdir[0] = 1;


		//_t.sortcnt[1] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		//_t.sortdir[1] = 0;

		//_t.sortcnt[2] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		//_t.sortdir[2] = 2;

		//_t.sortcnt[3] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		//_t.sortdir[3] = 3;
		////
		 s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;
		else 	if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;





		break;

	case 2://Down
		//_t.sortcnt[0] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		//_t.sortdir[0] = 2;
		//_t.sortcnt[1] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		//_t.sortdir[1] = 1;


		//_t.sortcnt[2] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left
		//_t.sortdir[2] = 3;

		//_t.sortcnt[3] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		//_t.sortdir[3] = 0;



	//down
		if(m.now.y==y_size-1){
			_t.sortcnt[0] = t_cnt[2] = 1001;//Down
		}else{
			_t.sortcnt[0] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		}_t.sortdir[0] = 2;

	//right
		if(m.now.x==x_size-1){
		_t.sortcnt[1] = t_cnt[1] = 1001;//Right
		}else {
			_t.sortcnt[1] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		}
		_t.sortdir[1] = 1;
	//left
		if(m.now.x==0){
			_t.sortcnt[2] = t_cnt[3] = 1001;
		}
		else{
			_t.sortcnt[2] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left		
		}
		_t.sortdir[2] = 3;

	//up
		if(m.now.y==0){
			_t.sortcnt[3] = t_cnt[0] = 1001;//Up  

		}else{
			_t.sortcnt[3] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];	
		}_t.sortdir[3] = 0;
		
		

		s_sort(&_t, 0, 3);
		//s_sort(&_t, 0, 2);

		if (_t.sortcnt[0] == t_cnt[3])_t.sortdir[0] = 3;
		else if (_t.sortcnt[0] == t_cnt[2])_t.sortdir[0] = 2;
		else 	if (_t.sortcnt[0] == t_cnt[1])_t.sortdir[0] = 1;
		else 	if (_t.sortcnt[0] == t_cnt[0])_t.sortdir[0] = 0;

		break;
	case 3://Left

		//_t.sortcnt[0] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left       
		//_t.sortdir[0] = 3;
		//_t.sortcnt[1] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down        
		//_t.sortdir[1] = 2;


		//_t.sortcnt[2] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];//Up
		//_t.sortdir[2] = 0;

		//_t.sortcnt[3] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		//_t.sortdir[3] = 1;


		//left
		if(m.now.x==0){
			_t.sortcnt[0] = t_cnt[3] = 1001;
		}
		else{
			_t.sortcnt[0] = t_cnt[3] = m.cnt[m.now.x - 1][m.now.y];//Left		
		}
		_t.sortdir[0] = 3;
	//down
		if(m.now.y==y_size-1){
			_t.sortcnt[1] = t_cnt[2] = 1001;//Down
		}else{
			_t.sortcnt[1] = t_cnt[2] = m.cnt[m.now.x][m.now.y + 1];//Down
		}_t.sortdir[1] = 2;
	//up
		if(m.now.y==0){
			_t.sortcnt[2] = t_cnt[0] = 1001;//Up  

		}else{
			_t.sortcnt[2] = t_cnt[0] = m.cnt[m.now.x][m.now.y - 1];	
		}_t.sortdir[2] = 0;

	//right
		if(m.now.x==x_size-1){
		_t.sortcnt[3] = t_cnt[1] = 1001;//Right
		}else {
			_t.sortcnt[3] = t_cnt[1] = m.cnt[m.now.x + 1][m.now.y];//Right
		}
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



//ÅñèÛãµÇ…âûÇ∂Çƒå^ÇïœçXÇ∑ÇÈ


static int med3(int x, int y, int z)
/* x, y, z ÇÃíÜä‘ílÇï‘Ç∑ */
{
	if (x < y)
		if (y < z) return y; else if (z < x) return x; else return z; else
			if (z < y) return y; else if (x < z) return x; else return z;
}

//ç\ë¢ëÃÇÃÉÅÉìÉoÉ\Å[Ég
static void s_sort(tmp* a, int left, int right)
/* ÉNÉCÉbÉNÉ\Å[Ég
* a     : É\Å[ÉgÇ∑ÇÈîzóÒÇä‹ÇÒÇæÇÃå≥ÇÃç\ë¢ëÃ
* left  : É\Å[ÉgÇ∑ÇÈÉfÅ[É^ÇÃäJénà íu
* right : É\Å[ÉgÇ∑ÇÈÉfÅ[É^ÇÃèIóπà íu
*/


{



	if (left < right) {
		int i = left, j = right;
		int temp, temp2, pivot = med3(a->sortcnt[i], a->sortcnt[i + (j - i) / 2], a->sortcnt[j]); /* (i+j)/2Ç≈ÇÕÉIÅ[ÉoÅ[ÉtÉçÅ[ÇµÇƒÇµÇ‹Ç§ */
		while (1) { /* a[] Ç pivot à»è„Ç∆à»â∫ÇÃèWÇ‹ÇËÇ…ï™äÑÇ∑ÇÈ */
			while (a->sortcnt[i] < pivot) i++; /* a[i] >= pivot Ç∆Ç»ÇÈà íuÇåüçı */
			while (pivot < a->sortcnt[j]) j--; /* a[j] <= pivot Ç∆Ç»ÇÈà íuÇåüçı */
			if (i >= j) break;
			temp = a->sortcnt[i]; temp2 = a->sortdir[i];
			a->sortcnt[i] = a->sortcnt[j]; a->sortdir[i] = a->sortdir[j];
			a->sortcnt[j] = temp; a->sortdir[j] = temp2; /* a[i],a[j] Çåä∑ */
			i++; j--;
		}
		s_sort(a, left, i - 1);  /* ï™äÑÇµÇΩç∂ÇçƒãAìIÇ…É\Å[Ég */
		s_sort(a, j + 1, right); /* ï™äÑÇµÇΩâEÇçƒãAìIÇ…É\Å[Ég */
	}
}

#include "maze.h"
#include "shinnenn.h"
#include "kabegiwa.h"
//
//int kabegiwa(){
//
//	switch (m.dir){
//	case 0:
//		
//		if(m.now.y==1){//è„í[
//
//				if(m.cnt[m.now.x][m.now.y-1]==1001){
//				return -1;
//			}
//
//
//			if (canMove(DirUp) == MapWall){
//				m.cnt[m.now.x][m.now.y-1] = 1001;//ï«
//				return -1;
//				
//
//			}
//			else if(canMove(DirUp)==MapGoal){
//				return DirUp;
//			}
//
//
//		}
//
//		if (m.now.x == 1){//ç∂í[
//
//			if(m.cnt[m.now.x-1][m.now.y]==1001){
//				return -1;
//			}
//			if (canMove(DirLeft) == MapWall){
//
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//ï«
//				return -1;
//				
//
//			}
//			else if(canMove(DirLeft)==MapGoal){
//				return DirLeft;
//			}
//		}
//
//		
//		break;
//
//	case 1://âE
//		//ï«ç€ÇÃÉSÅ[ÉãämîF
//		if(m.now.x==x_size-2){//âEå¸Ç´
//
//			if(m.cnt[m.now.x+1][m.now.y]==1001){
//				return -1;
//			}
//
//
//			if (canMove(DirRight) == MapWall){
//				m.cnt[m.now.x+1][m.now.y] = 1001;//ï«
//				return -1;
//				
//
//			}
//			else if(canMove(DirRight)==MapGoal){
//				return DirRight;
//			}
//
//
//		}
//
//		if (m.now.x == 1){//è„í[
//
//			if(m.cnt[m.now.x][m.now.y-1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirUp) == MapWall){
//				m.cnt[m.now.x ][m.now.y-1] = 1001;//ï«
//				return -1;				
//
//			}
//			else if(canMove(DirUp)==MapGoal){
//				return DirUp;
//			}
//		}
//		//////////////////////////////////////////
//		break;
//	case 2://â∫
//			if(m.now.y==y_size-2){//â∫í[
//
//					if(m.cnt[m.now.x][m.now.y+1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirDown) == MapWall){
//				m.cnt[m.now.x][m.now.y+1] = 1001;//ï«
//				return -1;
//			}
//			else if(canMove(DirDown)==MapGoal){
//				return DirDown;
//			}
//		}
//
//		if (m.now.x == x_size-2){//âEí[
//
//				if(m.cnt[m.now.x+1][m.now.y]==1001){
//				return -1;
//			}
//
//			if (canMove(DirRight) == MapWall){
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//ï«
//				return -1;
//				
//
//			}
//			else if(canMove(DirRight)==MapGoal){
//				return DirRight;
//			}
//		}
//
//		//////////////////////////////////////////
//		break;
//	case 3:
//
//	if(m.now.x==1){//ç∂í[
//
//			if(m.cnt[m.now.x-1][m.now.y]==1001){
//				return -1;
//			}
//
//			if (canMove(DirLeft) == MapWall){
//				m.cnt[m.now.x-1][m.now.y] = 1001;//ï«
//				return -1;
//				
//
//			}
//			else if(canMove(DirLeft)==MapGoal){
//				return DirLeft;
//			}
//
//
//		}
//
//		if (m.now.y == y_size-2){//â∫í[
//			if(m.cnt[m.now.x][m.now.y+1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirDown) == MapWall){
//				m.cnt[m.now.x ][m.now.y+1] = 1001;//ï«
//				return -1;				
//
//			}
//			else if(canMove(DirDown)==MapGoal){
//				return DirDown;
//			}
//		}
//		//////////////////////////////////////////
//		
//
//		break;
//	}
//
//
//	return -1;
//}


//
//int kabegiwa(){
//
//	switch (m.dir){
//	case 0:
//		
//
//		if (m.now.x == 1){//ç∂í[
//			if (canMove(DirLeft) == MapGoal){
//				
//				return DirLeft;;
//
//			}
//			else{
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//ï«
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//		}
//
//		if (m.now.x == x_size - 2){//âEí[
//			if (canMove(DirRight) == MapGoal){
//				
//				return DirRight;
//			}
//			else{
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//ï«
//				return -1;
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//
//		}
//		break;
//
//	case 1:
//		//ï«ç€ÇÃÉSÅ[ÉãämîF
//		if (m.now.y == 1){//âEå¸Ç´ÇÃè„
//			if (canMove(DirUp) == MapGoal){
//				
//				return DirUp;
//			}
//			else
//			{
//				m.cnt[m.now.x][m.now.y - 1] = 1001;//ï«
//				//	m.cnt[m.now.x][m.now.y] += 3;
//			}
//
//		}
//		if (m.now.y == y_size - 2){//âEå¸Ç´ÇÃâ∫
//			if (canMove(DirDown) == MapGoal){
//				
//				return DirDown;
//			}
//			else{
//				m.cnt[m.now.x][m.now.y + 1] = 1001;//ï«
//				//m.cnt[m.now.x][m.now.y] += 3;
//				return -1;
//			}
//
//		}
//		//////////////////////////////////////////
//		break;
//	case 2:
//		//ï«ç€ÇÃÉSÅ[ÉãämîF
//		if (m.now.x == 1){//â∫å¸Ç´ç∂í[
//			if (canMove(DirLeft) == MapGoal){
//				
//				return DirLeft;
//			}
//			else
//			{
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//ï«
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//		}
//
//
//		if (m.now.x == x_size - 2){//â∫å¸Ç´âEí[
//			if (canMove(DirRight) == MapGoal){
//				
//				return DirRight;
//			}
//			else{
//				//m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//ï«
//				return -1;
//			}
//		}
//		//////////////////////////////////////////
//		break;
//	case 3:
//
//		//ï«ç€ÇÃÉSÅ[ÉãämîF
//		if (m.now.y == 1){//ç∂å¸Ç´è„í[
//			if (canMove(DirUp) == MapGoal){
//			
//				return DirUp;
//			}
//			else{
//				//	m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x][m.now.y - 1] = 1001;//ï«
//			}
//
//		}
//		if (m.now.y == y_size - 2){//ç∂å¸Ç´â∫í[
//			if (canMove(DirDown) == MapGoal){
//				
//				return DirDown;
//			}
//			else{
//				//m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x][m.now.y + 1] = 1001;//ï«
//				return -1;
//			}
//		}
//
//		break;
//	}
//
//
//	return -1;
//}


static int kabegiwa(){

	switch (m.dir){
	case 0:
		
		if(m.now.y==1){//è„í[

			if(m.cnt[m.now.x][m.now.y-1]!=1001){
				if (canMove(DirUp) == MapWall){
					m.cnt[m.now.x][m.now.y-1] = 1001;//ï«
				}
				else if(canMove(DirUp)==MapGoal){
					return DirUp;
				}
			}
		}
		


		if (m.now.x == 1){//ç∂í[

			if(m.cnt[m.now.x-1][m.now.y]!=1001){


				if (canMove(DirLeft) == MapWall){

					m.cnt[m.now.x - 1][m.now.y] = 1001;//ï«



				}
				else if(canMove(DirLeft)==MapGoal){
					return DirLeft;
				}
			}
		}

		
		break;

	case 1://âE
		//ï«ç€ÇÃÉSÅ[ÉãämîF
		//if(m.now.x==x_size-2){//âEå¸Ç´

		//	if(m.cnt[m.now.x+1][m.now.y]=!1001){

		//		if (canMove(DirRight) == MapWall){
		//			m.cnt[m.now.x+1][m.now.y] = 1001;//ï«



		//		}
		//		else if(canMove(DirRight)==MapGoal){
		//			return DirRight;
		//		}


		//	}
		//}

		if (m.now.x == 1){//è„í[

			if(m.cnt[m.now.x][m.now.y-1]!=1001){



				if (canMove(DirUp) == MapWall){
					m.cnt[m.now.x ][m.now.y-1] = 1001;//ï«


				}
				else if(canMove(DirUp)==MapGoal){
					return DirUp;
				}
			}
		}
		//////////////////////////////////////////
		break;
	case 2://â∫
		if(m.now.y==y_size-2){//â∫í[

			if(m.cnt[m.now.x][m.now.y+1]!=1001){



				if (canMove(DirDown) == MapWall){
					m.cnt[m.now.x][m.now.y+1] = 1001;//ï«

				}
				else if(canMove(DirDown)==MapGoal){
					return DirDown;
				}
			}
		}
		if (m.now.x == x_size-2){//âEí[

			if(m.cnt[m.now.x+1][m.now.y]!=1001){



				if (canMove(DirRight) == MapWall){
					m.cnt[m.now.x + 1][m.now.y] = 1001;//ï«



				}
				else if(canMove(DirRight)==MapGoal){
					return DirRight;
				}
			}
		}

		//////////////////////////////////////////
		break;
	case 3:

	if(m.now.x==1){//ç∂í[

			if(m.cnt[m.now.x-1][m.now.y]!=1001){
			
			

			if (canMove(DirLeft) == MapWall){
				m.cnt[m.now.x-1][m.now.y] = 1001;//ï«
			
				

			}
			else if(canMove(DirLeft)==MapGoal){
				return DirLeft;
			}


		}
	}
		if (m.now.y == y_size-2){//â∫í[
			if(m.cnt[m.now.x][m.now.y+1]!=1001){
		
			

			if (canMove(DirDown) == MapWall){
				m.cnt[m.now.x ][m.now.y+1] = 1001;//ï«		

			}
			else if(canMove(DirDown)==MapGoal){
				return DirDown;
			}
		}
		}
		//////////////////////////////////////////
		

		break;
	}


	return -1;
}