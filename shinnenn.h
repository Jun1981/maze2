#pragma once

#include	<stdio.h>
#include	<conio.h>
#include	<windows.h>
#include	<stdlib.h>


#include "maze.h"



//#define map20x20
#define map50x30


//
////$B%^%C%W%5%$%:!!(B20x20
//#ifdef map20x20
//#define xsize 20 
//#define ysize 20
//#endif
//
////$B%^%C%W%5%$%:#5#0#x#3#0(B
//#ifdef map50x30
//#define xsize 50  
//#define ysize 30
//#endif 



enum mstat{ aile = 0, wall = 1 };
//
//extern const int xsize;
//extern const int ysize;


//$B<+5!4X78(B
typedef struct MAP{

	int dir;//$B<+5!(B/$B8~$$$F$$$kJ}8~(B
	int mv;//$B<!$N0\F0(B
	Pos now;//$B8=:_0LCV(B
	Pos old;//$B$R$H$DA0$N0LCV(B

	int cnt[50][30];//$BDL9T2s?t%+%&%s%H(B
	//int sortcnt[4];//
	//int sortdir[4];//
	//
	enum mstat stat[50][30];//$B$"$k:BI8$,JI$+DLO)$+(B

}mp;

extern mp m;

extern int x_size, y_size;
extern int self_chk;//Ž©•ª‚Ìƒ}ƒbƒvŠm”F—p
