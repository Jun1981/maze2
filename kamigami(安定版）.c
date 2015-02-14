
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
static	Funcs funcs = { "�_�X�̗V��", init, walkAround };
//=================================
// $B8x3+4X?t(B
//=================================
Funcs* getGroup05Info(void) { return &funcs; }


static int x_size, y_size;

static int self_chk= 0;//�����̃}�b�v�`�F�b�N�p




//$BFbIt4X?t(B
static mp m;
static int once = 0;//$B:G=i$@$1(B


static int	walkAround(void){
	
	
	if(once==1){
	r_move();//�E�D��	
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

	//�}�b�v�J�E���^�����Z�b�g
	for (i = 0; i < 100; i++){
		for (j = 0; j < 100; j++){
			m.cnt[i][j] = 0;
		}
	}
	m.now = getCurrentPosition();

	//if (m.now.x == 0 && m.now.y == 12)self_chk=1;//���ȃ}�b�v�������m�F

	//m.cnt[m.now.x][m.now.y] ++ ;
	//m.stat[m.now.x][m.now.y] = wall;//$BJI(B
	m.old.x = m.now.x; m.old.y = m.now.y;
	
	//�X�^�[�g�n�_�����[�̏ꍇ
	if (m.now.x == 0){	
		if (canMove(0) == MapGoal){
			m.mv = 0;
			
			
		}
		else if(canMove(2)==MapGoal){
			m.mv=2;
			
			
		}		
		m.mv = 1;



	}else
	//�X�^�[�g�n�_���E�[
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

	//�X�^�[�g�n�_�@��
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
	//�X�^�[�g�n�_�@��
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

//�����`�H

//2015�N2��8��


#include"maze.h"


#include "s_sort.h"


//#include "move.h"

#include "r_move.h"

#include "kabegiwa.h"

static int t_cnt[4] = { 0 };//�ꎞ�J�E���g

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

	times++;//������ڂ�

	stk_cnt[m.now.x][m.now.y] = times;


	m.cnt[m.now.x][m.now.y]++; //���݈ʒu�J�E���g


	switch (m.dir){
	case 0://��

		//�O�ƍ��W���ς���ĂȂ����������O��ǂƂ���
		if (same == 1){ m.cnt[m.now.x][m.now.y - 1] = 1001; }
		

		//�ǂ̋߂��ŃS�[���`�F�b�N
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}
		//����
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] =1000;


		//�E���O��������i��
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
		
		////�㉺���ǂō��E���O�ȏ�
		//if(m.now.x!=0 && m.cnt[m.now.x][m.now.y+1]==1001 && m.cnt[m.now.x][m.now.y-1]==1001 && m.cnt[m.now.x-1][m.now.y]>0 ){
		//	old_dir = m.dir = m.mv = 3;
		//	break;;

		//}

		



		


		//////*�E���P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0){
			if (m.cnt[m.now.x + 1][m.now.y - 1]>0 && m.cnt[m.now.x + 1][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		////////���オ�P�ŕǂɈ͂܂�Ă���i��
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 2][m.now.y - 1] == 1001 && m.cnt[m.now.x][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		//////*�E�オ�P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x + 1][m.now.y - 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] >0){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		////���Q��
		//if (m.cnt[m.now.x - 2][m.now.y ] >= 1 && m.cnt[m.now.x - 2][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
		//	if ( m.cnt[m.now.x-2][m.now.y + 1] == 1001){
		//		old_dir = m.dir = m.mv = 3; break;
		//	}
		//}
		//�オ�ǂō������ǂ̏ꍇ�ō����A��̒ʘH
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}

		


		//�オ�O��������i��
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}
		//�����O��������i��
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}
		//�����O��������i��
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}
		old_dir = m.dir = m.mv = dirsort();
			

		break;
	case 1://�E		
		//�O�ƍ��W���ς���ĂȂ����������O��ǂƂ���
		if (same == 1){ m.cnt[m.now.x + 1][m.now.y] = 1001; }
		



		//�ǂ̋߂��ŃS�[���`�F�b�N
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}

		
		//����
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] =1000;


		//�����O��������i��
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}

		


		////���E���ǂŏ㉺���O�ȏ�
		//if(m.cnt[m.now.x-1][m.now.y]==1001 && m.cnt[m.now.x+1][m.now.y]==1001 && m.cnt[m.now.x][m.now.y-1]>0 &&  m.cnt[m.now.x][m.now.y+1]>0 && m.cnt[m.now.x][m.now.y-1]!=1001 &&  m.cnt[m.now.x][m.now.y+1]!=1001){
		//	old_dir = m.dir = m.mv = 0;
		//	break;

		//}

		//�����ǂō��E���O�ʏ�

		if(m.cnt[m.now.x][m.now.y+1]==1001 &&  m.cnt[m.now.x-1][m.now.y]>0 &&  m.cnt[m.now.x+1][m.now.y]>0 && m.cnt[m.now.x-1][m.now.y]!=1001 &&  m.cnt[m.now.x+1][m.now.y]!=1001){
			old_dir = m.dir = m.mv = 1;
			break;

		}

		/////*�E�オ�P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x + 1][m.now.y - 1] >= 1 && m.cnt[m.now.x+1][m.now.y - 1] != 1001 && same == 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] >0){
				old_dir = m.dir = m.mv = 0; break;
			}
		}

		
		//////*�����P�ŕǂɈ͂܂�Ă���
		if (m.cnt[m.now.x][m.now.y + 1] >= 1 && m.cnt[m.now.x][m.now.y + 1] != 1001 && same != 1 ){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001 && m.cnt[m.now.x + 1][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 2; break;
			}
		}
		/////*�������P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0 && m.cnt[m.now.x - 1][m.now.y] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y] == 1001 && m.cnt[m.now.x + 1][m.now.y - 2] == 1001){
				old_dir = m.dir = m.mv = 0; break;
			}
		}
		////�E�����P�ŕǂɈ͂܂�Ă���
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 ){
			if (m.cnt[m.now.x][m.now.y + 1] == 1001 && m.cnt[m.now.x + 2][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//�����ǂŉE�オ�ǂ̏ꍇ�ŉE���A��̒ʘH
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}




		

			//�E���O��������i��
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
			//�オ�O��������i��
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}
		//�����O��������i��
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}


		old_dir = m.dir = m.mv = dirsort();
		

		break;
	case 2://��




		/*if (self_chk == 2){
		if (m.now.x == 2 && m.now.y == 13){
		self_chk = 3;
		old_dir = m.dir = m.mv = DirRight;
		break;
		}


		}
		*/




		//�O�ƍ��W���ς���ĂȂ����������O��ǂƂ���
		if (same == 1){ m.cnt[m.now.x][m.now.y + 1] = 1001; }

		//�ǂ̋߂��ŃS�[���`�F�b�N
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}


		//����
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;



		//�����O��������i��
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}

		
		
		////�㉺���ǂō��E���O�ȏ�
	
		//if(m.cnt[m.now.x][m.now.y+1]==1001 && m.cnt[m.now.x][m.now.y-1]==1001 && m.cnt[m.now.x-1][m.now.y]>0 &&  m.cnt[m.now.x+1][m.now.y]>0 &&m.cnt[m.now.x-1][m.now.y]!=1001 &&  m.cnt[m.now.x+1][m.now.y]!=1001){
		//	old_dir = m.dir = m.mv = 1;
		//	break;;

		//}
		
		


		

		////*�����P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x - 1][m.now.y] >= 1 && m.cnt[m.now.x - 1][m.now.y] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y + 1] > 0){
			if (m.cnt[m.now.x - 1][m.now.y - 1] == 1001 && m.cnt[m.now.x - 1][m.now.y + 1] >0){
				old_dir = m.dir = m.mv = 3; break;
			}
		}
		////�E�����P�ŕǂɈ͂܂�Ă���
		if (m.cnt[m.now.x + 1][m.now.y + 1] >= 1 && m.cnt[m.now.x + 1][m.now.y + 1] != 1001 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x][m.now.y + 1] == 1001 && m.cnt[m.now.x + 2][m.now.y + 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}
		//////*�������P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same != 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y] == 1001 && m.cnt[m.now.x - 1][m.now.y + 2] >0){
				old_dir = m.dir = m.mv = 2; break;
			}
		}

		//�����ǂŉE�オ�ǂ̏ꍇ�ŉE���A��̒ʘH
		if (m.cnt[m.now.x + 1][m.now.y] >= 1 && m.cnt[m.now.x + 1][m.now.y] != 1001 && same == 1 && m.cnt[m.now.x - 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y - 1] != 1001){
			if (m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 1; break;
			}
		}

		//�����O��������i��
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}
		
			//�E���O��������i��
		if(m.now.x!=x_size-1){
		if (m.cnt[m.now.x + 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 1;  break; }
		}
			//�オ�O��������i��
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}

		old_dir = m.dir = m.mv = dirsort();
		
		break;
	case 3://��


		//�O�ƍ��W���ς���ĂȂ����������O��ǂƂ���
		if (same == 1){ m.cnt[m.now.x - 1][m.now.y] = 1001; }

		//�ǂ̋߂��ŃS�[���`�F�b�N
		if (kabegiwa() != -1){
			old_dir = m.dir = m.mv = kabegiwa(); break;
		}
		//����
		if (m.cnt[m.now.x - 1][m.now.y] + m.cnt[m.now.x + 1][m.now.y] + m.cnt[m.now.x][m.now.y - 1] + m.cnt[m.now.x][m.now.y + 1] >= 3000)
			m.cnt[m.now.x][m.now.y] = 1000;


			//�オ�O��������i��
		if(m.now.y!=0){
		if (m.cnt[m.now.x][m.now.y - 1] == 0){ old_dir = m.dir = m.mv = 0; break; }
		}


		////�㉺���ǂ������獶

		//if(m.cnt[m.now.x][m.now.y-1] ==1001 && m.cnt[m.now.x][m.now.y+1]==1001){
		//	 old_dir = m.dir = m.mv =3; break;
		//}


	



	
			
		////���E���ǂŏ㉺���O�ȏ�
		//if(m.cnt[m.now.x-1][m.now.y]==1001 && m.cnt[m.now.x+1][m.now.y]==1001 && m.cnt[m.now.x][m.now.y-1]>0 &&  m.cnt[m.now.x][m.now.y+1]>0 &&  m.cnt[m.now.x][m.now.y-1]!=1001 &&  m.cnt[m.now.x][m.now.y+1]!=1001){
		//	old_dir = m.dir = m.mv = 2;
		//	break;

		//}

		


			//////�オ�P�ŕǂɈ͂܂�Ă���i��
		if (m.cnt[m.now.x][m.now.y - 1] >= 1 && m.cnt[m.now.x][m.now.y - 1] != 1001 && same != 1 ){
			if (m.cnt[m.now.x - 1][m.now.y - 1] >0 && m.cnt[m.now.x + 1][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 0; break;
			}
		}else
		//////*�������P�ŕǂɈ͂܂�Ă���(���[���E�o�p�j
		if (m.cnt[m.now.x - 1][m.now.y + 1] >= 1 && m.cnt[m.now.x - 1][m.now.y + 1] != 1001 && same == 1 && m.cnt[m.now.x][m.now.y - 1] > 0 && m.cnt[m.now.x + 1][m.now.y] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y] == 1001 && m.cnt[m.now.x - 1][m.now.y + 2] == 1001){
				old_dir = m.dir = m.mv = 2; break;
			}
		}else

		////////���オ�P�ŕǂɈ͂܂�Ă���i��
		if (m.cnt[m.now.x - 1][m.now.y - 1] >= 1 && m.cnt[m.now.x - 1][m.now.y - 1] != 1001 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 2][m.now.y - 1] >0 && m.cnt[m.now.x][m.now.y - 1] == 1001){
				old_dir = m.dir = m.mv = 3; break;
			}
		}else


		//�オ�ǂō������ǂ̏ꍇ�ō����A��̒ʘH
		if (m.cnt[m.now.x - 1][m.now.y ] >= 1 && m.cnt[m.now.x - 1][m.now.y ] != 1001 && same != 1 && m.cnt[m.now.x + 1][m.now.y] > 0 && m.cnt[m.now.x][m.now.y + 1] != 1001){
			if (m.cnt[m.now.x - 1][m.now.y + 1] == 1001 ){
				old_dir = m.dir = m.mv = 3; break;
			}
		}



		


		//�����O��������i��
		if(m.now.x!=0){
		if (m.cnt[m.now.x - 1][m.now.y] == 0){ old_dir = m.dir = m.mv = 3;  break; }
		}
		//�����O��������i��
		if(m.now.y!=y_size-1){
		if (m.cnt[m.now.x][m.now.y + 1] == 0){ old_dir = m.dir = m.mv = 2;  break; }
		}

			//�E���O��������i��
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



	//�E����
	switch (m.dir){
	case 0://��


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



//���󋵂ɉ����Č^��ύX����


static int med3(int x, int y, int z)
/* x, y, z �̒��Ԓl��Ԃ� */
{
	if (x < y)
		if (y < z) return y; else if (z < x) return x; else return z; else
			if (z < y) return y; else if (x < z) return x; else return z;
}

//�\���̂̃����o�\�[�g
static void s_sort(tmp* a, int left, int right)
/* �N�C�b�N�\�[�g
* a     : �\�[�g����z����܂񂾂̌��̍\����
* left  : �\�[�g����f�[�^�̊J�n�ʒu
* right : �\�[�g����f�[�^�̏I���ʒu
*/


{



	if (left < right) {
		int i = left, j = right;
		int temp, temp2, pivot = med3(a->sortcnt[i], a->sortcnt[i + (j - i) / 2], a->sortcnt[j]); /* (i+j)/2�ł̓I�[�o�[�t���[���Ă��܂� */
		while (1) { /* a[] �� pivot �ȏ�ƈȉ��̏W�܂�ɕ������� */
			while (a->sortcnt[i] < pivot) i++; /* a[i] >= pivot �ƂȂ�ʒu������ */
			while (pivot < a->sortcnt[j]) j--; /* a[j] <= pivot �ƂȂ�ʒu������ */
			if (i >= j) break;
			temp = a->sortcnt[i]; temp2 = a->sortdir[i];
			a->sortcnt[i] = a->sortcnt[j]; a->sortdir[i] = a->sortdir[j];
			a->sortcnt[j] = temp; a->sortdir[j] = temp2; /* a[i],a[j] ������ */
			i++; j--;
		}
		s_sort(a, left, i - 1);  /* �������������ċA�I�Ƀ\�[�g */
		s_sort(a, j + 1, right); /* ���������E���ċA�I�Ƀ\�[�g */
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
//		if(m.now.y==1){//��[
//
//				if(m.cnt[m.now.x][m.now.y-1]==1001){
//				return -1;
//			}
//
//
//			if (canMove(DirUp) == MapWall){
//				m.cnt[m.now.x][m.now.y-1] = 1001;//��
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
//		if (m.now.x == 1){//���[
//
//			if(m.cnt[m.now.x-1][m.now.y]==1001){
//				return -1;
//			}
//			if (canMove(DirLeft) == MapWall){
//
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//��
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
//	case 1://�E
//		//�Ǎۂ̃S�[���m�F
//		if(m.now.x==x_size-2){//�E����
//
//			if(m.cnt[m.now.x+1][m.now.y]==1001){
//				return -1;
//			}
//
//
//			if (canMove(DirRight) == MapWall){
//				m.cnt[m.now.x+1][m.now.y] = 1001;//��
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
//		if (m.now.x == 1){//��[
//
//			if(m.cnt[m.now.x][m.now.y-1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirUp) == MapWall){
//				m.cnt[m.now.x ][m.now.y-1] = 1001;//��
//				return -1;				
//
//			}
//			else if(canMove(DirUp)==MapGoal){
//				return DirUp;
//			}
//		}
//		//////////////////////////////////////////
//		break;
//	case 2://��
//			if(m.now.y==y_size-2){//���[
//
//					if(m.cnt[m.now.x][m.now.y+1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirDown) == MapWall){
//				m.cnt[m.now.x][m.now.y+1] = 1001;//��
//				return -1;
//			}
//			else if(canMove(DirDown)==MapGoal){
//				return DirDown;
//			}
//		}
//
//		if (m.now.x == x_size-2){//�E�[
//
//				if(m.cnt[m.now.x+1][m.now.y]==1001){
//				return -1;
//			}
//
//			if (canMove(DirRight) == MapWall){
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//��
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
//	if(m.now.x==1){//���[
//
//			if(m.cnt[m.now.x-1][m.now.y]==1001){
//				return -1;
//			}
//
//			if (canMove(DirLeft) == MapWall){
//				m.cnt[m.now.x-1][m.now.y] = 1001;//��
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
//		if (m.now.y == y_size-2){//���[
//			if(m.cnt[m.now.x][m.now.y+1]==1001){
//				return -1;
//			}
//
//			if (canMove(DirDown) == MapWall){
//				m.cnt[m.now.x ][m.now.y+1] = 1001;//��
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
//		if (m.now.x == 1){//���[
//			if (canMove(DirLeft) == MapGoal){
//				
//				return DirLeft;;
//
//			}
//			else{
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//��
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//		}
//
//		if (m.now.x == x_size - 2){//�E�[
//			if (canMove(DirRight) == MapGoal){
//				
//				return DirRight;
//			}
//			else{
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//��
//				return -1;
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//
//		}
//		break;
//
//	case 1:
//		//�Ǎۂ̃S�[���m�F
//		if (m.now.y == 1){//�E�����̏�
//			if (canMove(DirUp) == MapGoal){
//				
//				return DirUp;
//			}
//			else
//			{
//				m.cnt[m.now.x][m.now.y - 1] = 1001;//��
//				//	m.cnt[m.now.x][m.now.y] += 3;
//			}
//
//		}
//		if (m.now.y == y_size - 2){//�E�����̉�
//			if (canMove(DirDown) == MapGoal){
//				
//				return DirDown;
//			}
//			else{
//				m.cnt[m.now.x][m.now.y + 1] = 1001;//��
//				//m.cnt[m.now.x][m.now.y] += 3;
//				return -1;
//			}
//
//		}
//		//////////////////////////////////////////
//		break;
//	case 2:
//		//�Ǎۂ̃S�[���m�F
//		if (m.now.x == 1){//���������[
//			if (canMove(DirLeft) == MapGoal){
//				
//				return DirLeft;
//			}
//			else
//			{
//				m.cnt[m.now.x - 1][m.now.y] = 1001;//��
//				//m.cnt[m.now.x][m.now.y] += 3;
//			}
//		}
//
//
//		if (m.now.x == x_size - 2){//�������E�[
//			if (canMove(DirRight) == MapGoal){
//				
//				return DirRight;
//			}
//			else{
//				//m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x + 1][m.now.y] = 1001;//��
//				return -1;
//			}
//		}
//		//////////////////////////////////////////
//		break;
//	case 3:
//
//		//�Ǎۂ̃S�[���m�F
//		if (m.now.y == 1){//��������[
//			if (canMove(DirUp) == MapGoal){
//			
//				return DirUp;
//			}
//			else{
//				//	m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x][m.now.y - 1] = 1001;//��
//			}
//
//		}
//		if (m.now.y == y_size - 2){//���������[
//			if (canMove(DirDown) == MapGoal){
//				
//				return DirDown;
//			}
//			else{
//				//m.cnt[m.now.x][m.now.y] += 3;
//				m.cnt[m.now.x][m.now.y + 1] = 1001;//��
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
		
		if(m.now.y==1){//��[

			if(m.cnt[m.now.x][m.now.y-1]!=1001){
				if (canMove(DirUp) == MapWall){
					m.cnt[m.now.x][m.now.y-1] = 1001;//��
				}
				else if(canMove(DirUp)==MapGoal){
					return DirUp;
				}
			}
		}
		


		if (m.now.x == 1){//���[

			if(m.cnt[m.now.x-1][m.now.y]!=1001){


				if (canMove(DirLeft) == MapWall){

					m.cnt[m.now.x - 1][m.now.y] = 1001;//��



				}
				else if(canMove(DirLeft)==MapGoal){
					return DirLeft;
				}
			}
		}

		
		break;

	case 1://�E
		//�Ǎۂ̃S�[���m�F
		//if(m.now.x==x_size-2){//�E����

		//	if(m.cnt[m.now.x+1][m.now.y]=!1001){

		//		if (canMove(DirRight) == MapWall){
		//			m.cnt[m.now.x+1][m.now.y] = 1001;//��



		//		}
		//		else if(canMove(DirRight)==MapGoal){
		//			return DirRight;
		//		}


		//	}
		//}

		if (m.now.x == 1){//��[

			if(m.cnt[m.now.x][m.now.y-1]!=1001){



				if (canMove(DirUp) == MapWall){
					m.cnt[m.now.x ][m.now.y-1] = 1001;//��


				}
				else if(canMove(DirUp)==MapGoal){
					return DirUp;
				}
			}
		}
		//////////////////////////////////////////
		break;
	case 2://��
		if(m.now.y==y_size-2){//���[

			if(m.cnt[m.now.x][m.now.y+1]!=1001){



				if (canMove(DirDown) == MapWall){
					m.cnt[m.now.x][m.now.y+1] = 1001;//��

				}
				else if(canMove(DirDown)==MapGoal){
					return DirDown;
				}
			}
		}
		if (m.now.x == x_size-2){//�E�[

			if(m.cnt[m.now.x+1][m.now.y]!=1001){



				if (canMove(DirRight) == MapWall){
					m.cnt[m.now.x + 1][m.now.y] = 1001;//��



				}
				else if(canMove(DirRight)==MapGoal){
					return DirRight;
				}
			}
		}

		//////////////////////////////////////////
		break;
	case 3:

	if(m.now.x==1){//���[

			if(m.cnt[m.now.x-1][m.now.y]!=1001){
			
			

			if (canMove(DirLeft) == MapWall){
				m.cnt[m.now.x-1][m.now.y] = 1001;//��
			
				

			}
			else if(canMove(DirLeft)==MapGoal){
				return DirLeft;
			}


		}
	}
		if (m.now.y == y_size-2){//���[
			if(m.cnt[m.now.x][m.now.y+1]!=1001){
		
			

			if (canMove(DirDown) == MapWall){
				m.cnt[m.now.x ][m.now.y+1] = 1001;//��		

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