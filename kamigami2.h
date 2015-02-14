
#pragma once
#include	<stdio.h>
#include	<conio.h>
#include	<windows.h>
#include	<stdlib.h>

//ƒOƒ[ƒoƒ‹•Ï”




typedef struct MAP{
	int now_dir;
	int prev_dir;
	int mv;
	Pos now;
	Pos old;	
	int cnt[100][100];

}map;