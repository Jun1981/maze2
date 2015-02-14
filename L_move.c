
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
