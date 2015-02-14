#include "maze.h"
#include "kamigami2.h"
#include "R_move.h"

static	Funcs funcs = { "�_�X�̗V��", init, walkAround };
Funcs* getGroup05Info(void) { return &funcs; }


//���̃t�@�C���̃O���[�o���ϐ�
static int once =0;//��񂾂��p


//�\���̐錾
static map m;

//�}�b�v�T�C�Y�p
static int	x_size=0;
static int	y_size=0;

static int	walkAround(void){
	if(once==1)	R_move();//�E��@�v�Z		
	if(once==0)	init();	//�ŏ�����

	once=1;//��񂫂�I��
	return m.mv;
}


static void init(void){
	int i, j;//���[�v�p
	
	//�}�b�v�T�C�Y
	x_size = getMazeWidth();
	y_size = getMazeHeight();
	//////////////////////////

	m.now = getCurrentPosition();//���݈ʒu�擾

	//�}�b�v�J�E���^�����Z�b�g
	for (i = 0; i < 100; i++)
		for (j = 0; j < 100; j++)
			m.cnt[i][j] = 0;

	m.old.x=m.old.y=-1;//�O�̈ʒu��K����

	//�ŏ��̈ʒu�ɂ���čŏ��̕��������߂�	
	
	if(m.now.y==0)//��[
		if(canMove(DirRight)==MapGoal){
			m.mv=1;
			goto END;

		}
		else
			m.now_dir=m.mv=3;//����
	


	if(m.now.x==0)//���[
		if(canMove(DirUp)==MapGoal){
			m.now_dir=m.mv=0;
			goto END;

		}
		else
			m.now_dir=m.mv=2;//����
	
	if(m.now.x==x_size-1)//�E�[

		if(canMove(DirDown)==MapGoal){
			m.now_dir=m.mv=2;
			goto END;

		}
		else		
			m.now_dir=m.mv=0;//���
	

	if(m.now.y==y_size-1)//���[
		if(canMove(DirLeft)==MapGoal){
			m.now_dir=m.mv=3;
			goto END;

		}
		else		
			m.now_dir=m.mv=1;//�E��
	
	//////////////////////////////////////////////////////////


END:;
}






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
