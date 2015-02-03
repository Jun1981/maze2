#include "s_sort.h"
//#include "move.h"


//＊状況に応じて型を変更する

 
int med3(int x, int y, int z)
/* x, y, z の中間値を返す */
{
    if (x < y)
        if (y < z) return y; else if (z < x) return x; else return z; else
        if (z < y) return y; else if (x < z) return x; else return z;
}
 
//構造体のメンバソート
void s_sort(tmp* a, int left, int right)
/* クイックソート
 * a     : ソートする配列を含んだの元の構造体
 * left  : ソートするデータの開始位置
 * right : ソートするデータの終了位置
 */
{
    if (left < right) {
        int i = left, j = right;
        int temp,temp2, pivot = med3(a->sortcnt[i], a->sortcnt[i + (j - i) / 2], a->sortcnt[j]); /* (i+j)/2ではオーバーフローしてしまう */
        while (1) { /* a[] を pivot 以上と以下の集まりに分割する */
            while (a->sortcnt[i] < pivot) i++; /* a[i] >= pivot となる位置を検索 */
            while (pivot < a->sortcnt[j]) j--; /* a[j] <= pivot となる位置を検索 */
            if (i >= j) break;
			temp = a->sortcnt[i]; temp2 = a->sortdir[i];
			a->sortcnt[i] = a->sortcnt[j]; a->sortdir[i] = a->sortdir[j];
			a->sortcnt[j] = temp; a->sortdir[j] = temp2; /* a[i],a[j] を交換 */
            i++; j--;
        }
        s_sort(a, left, i - 1);  /* 分割した左を再帰的にソート */
        s_sort(a, j + 1, right); /* 分割した右を再帰的にソート */
    }
}