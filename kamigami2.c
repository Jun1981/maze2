#include "maze.h"
#include "kamigami2.h"
#include "R_move.h"

static	Funcs funcs = { "神々の遊び", init, walkAround };
Funcs* getGroup05Info(void) { return &funcs; }


//このファイルのグローバル変数
static int once =0;//一回だけ用


//構造体宣言
static map m;

//マップサイズ用
static int	x_size=0;
static int	y_size=0;

static int	walkAround(void){
	if(once==1)	R_move();//右手法計算		
	if(once==0)	init();	//最初だけ

	once=1;//一回きり終了
	return m.mv;
}


static void init(void){
	int i, j;//ループ用
	
	//マップサイズ
	x_size = getMazeWidth();
	y_size = getMazeHeight();
	//////////////////////////

	m.now = getCurrentPosition();//現在位置取得

	//マップカウンタをリセット
	for (i = 0; i < 100; i++)
		for (j = 0; j < 100; j++)
			m.cnt[i][j] = 0;

	m.old.x=m.old.y=-1;//前の位置を適当に

	//最初の位置によって最初の方向を決める	
	
	if(m.now.y==0)//上端
		if(canMove(DirRight)==MapGoal){
			m.mv=1;
			goto END;

		}
		else
			m.now_dir=m.mv=3;//左へ
	


	if(m.now.x==0)//左端
		if(canMove(DirUp)==MapGoal){
			m.now_dir=m.mv=0;
			goto END;

		}
		else
			m.now_dir=m.mv=2;//下へ
	
	if(m.now.x==x_size-1)//右端

		if(canMove(DirDown)==MapGoal){
			m.now_dir=m.mv=2;
			goto END;

		}
		else		
			m.now_dir=m.mv=0;//上へ
	

	if(m.now.y==y_size-1)//下端
		if(canMove(DirLeft)==MapGoal){
			m.now_dir=m.mv=3;
			goto END;

		}
		else		
			m.now_dir=m.mv=1;//右へ
	
	//////////////////////////////////////////////////////////


END:;
}






void R_move(void){

	int same ;//前と座標が同じだったら

	m.now = getCurrentPosition();//現在位置取得
	m.cnt[m.now.x][m.now.y]++;//通行回数カウント

	


	//前と同じ座標だったら
	if(m.now.x==m.old.x && m.now.y==m.old.y)same=1;		
	else same=0;	


	switch(m.now_dir){			
	case 0:

		if(same==1&& m.cnt[m.now.x][m.now.y-1]!=1000){
			m.cnt[m.now.x][m.now.y-1]=1000;
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;
		
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//右チェック
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//上チェック
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//左チェック
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//下チェック



		break;
	case 1://右

		
		if(same==1 && m.cnt[m.now.x+1][m.now.y]!=1000){
			m.cnt[m.now.x+1][m.now.y]=1000;//右が壁
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;
		
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//下チェック
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//右チェック
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//上チェック
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//左チェック
		
		


		break;
	case 2://下
		
      if(same==1 && m.cnt[m.now.x][m.now.y+1]!=1000){
			m.cnt[m.now.x][m.now.y+1]=1000;//下が壁
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	
		
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//左チェック
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//下チェック
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//右チェック
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//上チェック
		


		break;
	case 3://左
		
	    if(same==1 && m.cnt[m.now.x-1][m.now.y]!=1000){
			m.cnt[m.now.x-1][m.now.y]=1000;//左が壁
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	

		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//上チェック
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//左チェック
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//下チェック
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//右チェック
		
		


		break;



	}

		
	//現在位置保存
		m.old.x=m.now.x;
		m.old.y=m.now.y;

}
