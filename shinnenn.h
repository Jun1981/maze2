
#pragma once

#include	<stdio.h>
#include	<conio.h>
#include	<windows.h>
#include	<stdlib.h>



#include "maze.h"

//#define map20x20
#define map50x30
//マップサイズ　20x20

#ifdef map20x20

#define x_size 20 
#define y_size 20
#endif

//マップサイズ５０ｘ３０
#ifdef map50x30
#define x_size 50  
#define y_size 30
#endif 


enum mstat{ aile = 0, wall = 1 };


//自機関係
typedef struct MAP{

	int dir;//自機/向いている方向
	int mv;//次の移動
	Pos now;//現在位置
	Pos old;//ひとつ前の位置

	int cnt[x_size][y_size];//通行回数カウント
	//int sortcnt[4];//
	//int sortdir[4];//
	//
	enum mstat stat[x_size][y_size];//ある座標が壁か通路か

}map;
extern map m;