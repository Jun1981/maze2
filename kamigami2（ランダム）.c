#include "maze.h"
#include <time.h>

//�v���g�^�C�v
extern void maze_move(int);//���H�O���o���T���p�֐��@�i�����O�ō���@�@�P�ŉE��@�j
extern void start(void);//�X�^�[�g�n�_�̍s��
//extern void kabegiwa(int);//�Ǎۂ̌v�Z (�����F�P����@�F�Q�E��@�j
////////////////////////////


static	Funcs funcs = { "�_�X�̗V��", init, walkAround };
Funcs* getGroup05Info(void) { return &funcs; }


//���̃t�@�C���̃O���[�o���ϐ�

static int once =0;//��񂾂��p
//static int kabe_flag=0;//kabegiwa()�p

//�}�b�v�T�C�Y�p
static int	x_size=0;
static int	y_size=0;

//���E�����_���I��p
static int LR=0;//�O������P���E��



//////////////////////////////////////////////




//�}�b�v�\����
typedef struct MAP{
	int now_dir;//���̕���
	int prev_dir;//�O�s��������

	Pos now;//���݈ʒu�ۑ��p
	Pos old;//��O�̈ʒu���	
	int wall[100][100]; //�Ǐ�������i�ǂ̂Ƃ��P�O�O�O������j

}map;
//�\���̐錾
static map m;






//���C��

static int	walkAround(void){

	if(once==0)	init();	//�������i��񂾂��j
	



	if(once==2){
		maze_move(LR);//�����_��

	}

	if(once==1)start();//�X�^�[�g�n�_



	return m.now_dir;
}







//������
static void init(void){
	int i, j;//���[�v�p

	

	//�E��@
	//LR=1;
	//�����_��
	srand( (unsigned)time(NULL) );
	LR=rand()%2;//LR�ɂO���P�������

	//�}�b�v�T�C�Y
	x_size = getMazeWidth();
	y_size = getMazeHeight();
	//////////////////////////

	m.now = getCurrentPosition();//���݈ʒu�擾

	//�}�b�v�J�E���^�����Z�b�g
	for (i = 0; i < 100; i++)
		for (j = 0; j < 100; j++)
			m.wall[i][j] = 0;

	m.old.x=m.old.y=-1;//�O�̈ʒu��K����



	once=1;

}







//���H�O���o���T���p�֐��@�i�����O�ō���@�@�P�ŉE��@�j
static void maze_move(int lr){
	int same ;//�O�ƍ��W��������������
	static int tmp;
	m.now = getCurrentPosition();//���݈ʒu�擾
	m.wall[m.now.x][m.now.y]++;//�ʍs�񐔃J�E���g

	

	//�O�Ɠ������W��������
	if(m.now.x==m.old.x && m.now.y==m.old.y)same=1;		
	else same=0;	




	switch(m.now_dir){			
	case 0://�����
		if(same==1&& m.wall[m.now.x][m.now.y-1]!=1000 && m.now.y!=0){
			m.wall[m.now.x][m.now.y-1]=1000;
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;

		


		//����@
		if(lr==0){			

			
			//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			//	if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			//	//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			//	
			//	//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N

			if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000){//�E�[�̎�
					tmp=canMove(1);
				if(tmp==MapGoal){m.now_dir=1;break;}
				if(tmp==MapWall){m.wall[m.now.x+1][m.now.y]=1000;}
			}

			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			
		}
		//�E��@
		else if(lr==1){

			if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000){//���[�̎�
					tmp=canMove(3);
				if(tmp==MapGoal){m.now_dir=3;break;}
				if(tmp==MapWall){m.wall[m.now.x-1][m.now.y]=1000;}
			}
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N				
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N

			


			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			
		}
		break;

	case 1://�E
		if(same==1 && m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1){
			m.wall[m.now.x+1][m.now.y]=1000;//�E����
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;

		//����@
		if(lr==0){		
			
			if(m.now.y==y_size-2 && m.wall[m.now.x][m.now.y+1]!=1000){//���[�̎�
					tmp=canMove(2);
				if(tmp==MapGoal){m.now_dir=2;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y+1]=1000;}
			}

				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
				//
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N


		

			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			
		}
		//�E��@
		else if(lr==1){

			if(m.now.y==1 && m.wall[m.now.x][m.now.y-1]!=1000){//���[�̎�
				tmp=canMove(0);
				if(tmp==MapGoal){m.now_dir=0;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y-1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N				
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N

	

			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			
		}
		break;

	case 2://��
		if(same==1 && m.wall[m.now.x][m.now.y+1]!=1000 && m.now.y!=y_size-1){
			m.wall[m.now.x][m.now.y+1]=1000;//������
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	




		//����@
		if(lr==0){		

			if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000){//���[�̎�
				tmp=canMove(3);
				if(tmp==MapGoal){m.now_dir=3;break;}
				if(tmp==MapWall){m.wall[m.now.x-11][m.now.y]=1000;}
			}
			//if(m.now.x==1 && m.wall[m.now.x-1][m.now.y]!=1000)//���[�̎��E��@�ɐ؂�ւ���

			//	if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
				//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N

	


			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			
		}
		//�E��@
		else if(lr==1){

			if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000){//�E�[�̎�
				tmp=canMove(1);
				if(tmp==MapGoal){m.now_dir=1;break;}
				if(tmp==MapWall){m.wall[m.now.x-11][m.now.y]=1000;}
			}

			//if(m.now.x==x_size-2 && m.wall[m.now.x+1][m.now.y]!=1000)//�E�[�̎�����@�ɐ؂�ւ���


			//	if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N			
				//
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N

			

			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			
		}
		break;

	case 3://��
		if(same==1 && m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){
			m.wall[m.now.x-1][m.now.y]=1000;//������
			m.now_dir=m.prev_dir;
			break;
		}
		m.prev_dir=m.now_dir;	

		//����@
		if(lr==0 ){

		if(m.now.y==1 && m.wall[m.now.x][m.now.y-1]!=1000){//���[�̎�
				tmp=canMove(0);
				if(tmp==MapGoal){m.now_dir=0;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y-1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N				
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N


			

			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			}
		
		//�E��@
		else if(lr==1){

			if(m.now.y==y_size-2 && m.wall[m.now.x][m.now.y+1]!=1000){//���[�̎�
				tmp=canMove(2);
				if(tmp==MapGoal){m.now_dir=2;break;}
				if(tmp==MapWall){m.wall[m.now.x][m.now.y+1]=1000;}
			}
				//if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
				//if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
				//
				//if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N

	

			if(m.wall[m.now.x][m.now.y-1]!=1000 &&  m.now.y!=0){m.now_dir=0;break;}//��`�F�b�N
			if(m.wall[m.now.x-1][m.now.y]!=1000 &&  m.now.x!=0){m.now_dir=3;break;}//���`�F�b�N
			if(m.wall[m.now.x][m.now.y+1]!=1000 &&  m.now.y!=y_size-1){m.now_dir=2;break;}//���`�F�b�N
			if(m.wall[m.now.x+1][m.now.y]!=1000 && m.now.x!=x_size-1) { m.now_dir=1;break; }//�E�`�F�b�N
			
		}
		break;

	}


	//���݈ʒu�ۑ�
	m.old.x=m.now.x;
	m.old.y=m.now.y;
}

void start(void){

	//�ŏ��̈ʒu�ɂ���čŏ��̕��������߂�	

	if(m.now.y==0){//��[
		if(canMove(DirRight)==MapGoal){
			m.now_dir=1;
			goto END;
		}
		else{
			m.now_dir=3;//����
			goto END;
		}
	}




	if(m.now.x==0){//���[
		if(canMove(DirUp)==MapGoal){
			m.now_dir=0;
			goto END;
		}
		else{
			m.now_dir=2;//����
			goto END;
		}
	}
	if(m.now.x==x_size-1){//�E�[
		if(canMove(DirDown)==MapGoal){
			m.now_dir=2;
			goto END;
		}
		else{		
			m.now_dir=0;//���
			goto END;
		}
	}
	if(m.now.y==y_size-1){//���[
		if(canMove(DirLeft)==MapGoal){
			m.now_dir=3;
			goto END;
		}
		else{		
			m.now_dir=1;//�E��
			goto END;
		}
	}
					//////////////////////////////////////////////////////////


END: 
					once=2;

}

