
#pragma once
#include "shinnenn.h"

typedef struct {
	int sortdir[4];
	int sortcnt[4];
}tmp;

int med3(int x, int y, int z);
void s_sort(tmp *, int left, int right);