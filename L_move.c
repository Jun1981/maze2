
void R_move(void){

	int same ;//�O�ƍ��W��������������

	m.now = getCurrentPosition();//���݈ʒu�擾
	m.cnt[m.now.x][m.now.y]++;//�ʍs�񐔃J�E���g

	


	//�O�Ɠ������W��������
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
		
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//�E�`�F�b�N
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//��`�F�b�N
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//���`�F�b�N
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//���`�F�b�N



		break;
	case 1://�E

		
		if(same==1 && m.cnt[m.now.x+1][m.now.y]!=1000){
			m.cnt[m.now.x+1][m.now.y]=1000;//�E����
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;
		
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//���`�F�b�N
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//�E�`�F�b�N
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//��`�F�b�N
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//���`�F�b�N
		
		


		break;
	case 2://��
		
      if(same==1 && m.cnt[m.now.x][m.now.y+1]!=1000){
			m.cnt[m.now.x][m.now.y+1]=1000;//������
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	
		
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//���`�F�b�N
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//���`�F�b�N
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//�E�`�F�b�N
		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//��`�F�b�N
		


		break;
	case 3://��
		
	    if(same==1 && m.cnt[m.now.x-1][m.now.y]!=1000){
			m.cnt[m.now.x-1][m.now.y]=1000;//������
			m.now_dir=m.mv=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	

		if(m.cnt[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=m.mv=0;break;}//��`�F�b�N
		if(m.cnt[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=m.mv=3;break;}//���`�F�b�N
		if(m.cnt[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=m.mv=2;break;}//���`�F�b�N
		if(m.cnt[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=m.mv=1;break; }//�E�`�F�b�N
		
		


		break;



	}

		
	//���݈ʒu�ۑ�
		m.old.x=m.now.x;
		m.old.y=m.now.y;

}
