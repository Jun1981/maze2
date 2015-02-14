#include "maze.h"
#include <time.h>

//プロトタイプ
extern void maze_move(int);//迷路外周出口探索用関数　（引数０で左手法　１で右手法）
extern void start(void);//スタート地点の行動
//extern void kabegiwa(int);//壁際の計算 (引数：１左手法：２右手法）
////////////////////////////


static	Funcs funcs = { "神々の遊び", init, walkAround };
Funcs* getGroup05Info(void) { return &funcs; }


//このファイルのグローバル変数

static int once =0;//一回だけ用
//static int kabe_flag=0;//kabegiwa()用

//マップサイズ用
static int	x_size=0;
static int	y_size=0;

//左右ランダム選択用
static int LR=0;//０が左手１が右手



//////////////////////////////////////////////




//マップ構造体
typedef struct MAP{
	int now_dir;//今の方向
	int prev_dir;//前行った方向

	Pos now;//現在位置保存用
	Pos old;//一個前の位置情報	
	int wall[100][100]; //壁情報を入れる（壁のとき１０００を入れる）

}map;
//構造体宣言
static map m;






//メイン

static int	walkAround(void){

	if(once==0)	init();	//初期化（一回だけ）
	



	if(once==2){
		maze_move(LR);//ランダム

	}

	if(once==1)start();//スタート地点



	return m.now_dir;
}







//初期化
static void init(void){
	int i, j;//ループ用

	

	//右手法
	//LR=1;
	//ランダム
	srand( (unsigned)time(NULL) );
	LR=rand()%2;//LRに０か１をいれる

	//マップサイズ
	x_size = getMazeWidth();
	y_size = getMazeHeight();
	//////////////////////////

	m.now = getCurrentPosition();//現在位置取得

	//マップカウンタをリセット
	for (i = 0; i < 100; i++)
		for (j = 0; j < 100; j++)
			m.wall[i][j] = 0;

	m.old.x=m.old.y=-1;//前の位置を適当に



	once=1;

}







//迷路外周出口探索用関数　（引数０で左手法　１で右手法）
static void maze_move(int lr){
	int same ;//前と座標が同じだったら
	static int tmp;
	m.now = getCurrentPosition();//現在位置取得
	m.wall[m.now.x][m.now.y]++;//通行回数カウント

	

	//前と同じ座標だったら
	if(m.now.x==m.old.x && m.now.y==m.old.y)same=1;		
	else same=0;	




	switch(m.now_dir){			
	case 0://上向き
		if(same==1&& m.wall[m.now.x][m.now.y-1]!=1000 && m.now.y!=0){
			m.wall[m.now.x][m.now.y-1]=1000;
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;

		


		//左手法
		if(lr==0){			

			
			//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			//	if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			//	//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			//	
			//	//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック

			if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000){//右端の時
					tmp=canMove(1);
				if(tmp==MapGoal){m.now_dir=1;break;}
				if(tmp==MapWall){m.wall[m.now.x+1][m.now.y]=1000;}
			}

			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			
		}
		//右手法
		else if(lr==1){

			if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000){//左端の時
					tmp=canMove(3);
				if(tmp==MapGoal){m.now_dir=3;break;}
				if(tmp==MapWall){m.wall[m.now.x-1][m.now.y]=1000;}
			}
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック				
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック

			


			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			
		}
		break;

	case 1://右
		if(same==1 && m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1){
			m.wall[m.now.x+1][m.now.y]=1000;//右が壁
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;

		//左手法
		if(lr==0){		
			
			if(m.now.y==y_size-2 && m.wall[m.now.x][m.now.y+1]!=1000){//下端の時
					tmp=canMove(2);
				if(tmp==MapGoal){m.now_dir=2;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y+1]=1000;}
			}

				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
				//
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック


		

			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			
		}
		//右手法
		else if(lr==1){

			if(m.now.y==1 && m.wall[m.now.x][m.now.y-1]!=1000){//下端の時
				tmp=canMove(0);
				if(tmp==MapGoal){m.now_dir=0;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y-1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック				
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック

	

			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			
		}
		break;

	case 2://下
		if(same==1 && m.wall[m.now.x][m.now.y+1]!=1000 && m.now.y!=y_size-1){
			m.wall[m.now.x][m.now.y+1]=1000;//下が壁
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	




		//左手法
		if(lr==0){		

			if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000){//左端の時
				tmp=canMove(3);
				if(tmp==MapGoal){m.now_dir=3;break;}
				if(tmp==MapWall){m.wall[m.now.x-11][m.now.y]=1000;}
			}
			//if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000)//左端の時右手法に切り替える

			//	if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
				//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック

	


			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			
		}
		//右手法
		else if(lr==1){

			if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000){//右端の時
				tmp=canMove(1);
				if(tmp==MapGoal){m.now_dir=1;break;}
				if(tmp==MapWall){m.wall[m.now.x-11][m.now.y]=1000;}
			}

			//if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000)//右端の時左手法に切り替える


			//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック			
				//
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック

			

			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			
		}
		break;

	case 3://左
		if(same==1 && m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){
			m.wall[m.now.x-1][m.now.y]=1000;//左が壁
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	

		//左手法
		if(lr==0 ){

		if(m.now.y==1 && m.wall[m.now.x][m.now.y-1]!=1000){//下端の時
				tmp=canMove(0);
				if(tmp==MapGoal){m.now_dir=0;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y-1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック				
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック


			

			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			}
		
		//右手法
		else if(lr==1){

			if(m.now.y==y_size-2 && m.wall[m.now.x][m.now.y+1]!=1000){//下端の時
				tmp=canMove(2);
				if(tmp==MapGoal){m.now_dir=2;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y+1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
				//
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック

	

			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//上チェック
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//左チェック
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//下チェック
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//右チェック
			
		}
		break;

	}


	//現在位置保存
	m.old.x=m.now.x;
	m.old.y=m.now.y;
}

void start(void){

	//最初の位置によって最初の方向を決める	

	if(m.now.y==0){//上端
		if(canMove(DirRight)==MapGoal){
			m.now_dir=1;
			goto END;
		}
		else{
			m.now_dir=3;//左へ
			goto END;
		}
	}




	if(m.now.x==0){//左端
		if(canMove(DirUp)==MapGoal){
			m.now_dir=0;
			goto END;
		}
		else{
			m.now_dir=2;//下へ
			goto END;
		}
	}
	if(m.now.x==x_size-1){//右端
		if(canMove(DirDown)==MapGoal){
			m.now_dir=2;
			goto END;
		}
		else{		
			m.now_dir=0;//上へ
			goto END;
		}
	}
	if(m.now.y==y_size-1){//下端
		if(canMove(DirLeft)==MapGoal){
			m.now_dir=3;
			goto END;
		}
		else{		
			m.now_dir=1;//右へ
			goto END;
		}
	}
					//////////////////////////////////////////////////////////


END: 
					once=2;

}

