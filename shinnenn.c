

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
//=================================
// $B%W%l!<%d>pJs(B
//=================================
static	Funcs funcs = { "ê[ï£ÅiÇíÇô", init, walkAround };
//=================================
// $B8x3+4X?t(B
//=================================
Funcs* getGroup05Info(void) { return &funcs; }


int x_size, y_size;





//$BFbIt4X?t(B
mp m;
static int once = 0;//$B:G=i$@$1(B


static int	walkAround(void){

	/*x_size = getMazeWidth();
   y_size = getMazeHeight();*/


	
		//x_size = 50; y_size = 30;	
		//x_size = 20, y_size = 20;
		x_size = getMazeWidth();
		y_size = getMazeHeight();
	

	if (once == 0){
		init();
		once = 1;
		return m.mv;
	}
	r_move();	
	return m.mv;
}


static void init(void){

	int i, j;

	//É}ÉbÉvÉJÉEÉìÉ^ÇÉäÉZÉbÉg
	for (i = 0; i < 50; i++){
		for (j = 0; j < 30; j++){
			m.cnt[i][j] = 0;
		}



	}
	m.now = getCurrentPosition();
	m.cnt[m.now.x][m.now.y] = 1000;
	m.stat[m.now.x][m.now.y] = wall;//$BJI(B
	m.old.x = m.now.x, m.old.y = m.now.y;
	if (m.now.x == 0) m.mv = m.dir = DirRight;//$B%9%?!<%HCOE@$,:8C<$@$C$?$i(B
	else
		if (m.now.y == 0) m.dir = m.mv = DirDown;//$B>e%9%?!<%H(B
		else
			if (m.now.x == x_size - 1) m.dir = m.mv = DirLeft;//$B1&C<(B
			else
				if (m.now.y == y_size - 1)m.dir = m.mv = DirUp;//$B2<C<(B

}
