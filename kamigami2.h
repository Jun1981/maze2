
#pragma once
#include	<stdio.h>
#include	<conio.h>
#include	<windows.h>
#include	<stdlib.h>

//グローバル変数




typedef struct MAP{
	int now_dir;
	int prev_dir;
	int mv;
	Pos now;
	Pos old;	
	int cnt[100][100];

}map;