#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でキュー用のメモリを確保する
void initialize(QUEUE* q, size_t mem_size)
{
	if (q == NULL) return;

	q->data = (int*)malloc(mem_size);
	q->head = 0;
	q->tail = mem_size / sizeof(int)-1;
	q->max = mem_size / sizeof(int);
}


// 確保したメモリを解放する
void finalize(QUEUE* q)
{
	if (q == NULL) return;

	free(q->data);

	q->data = NULL;
	q->head = NULL;
	q->tail = NULL;
	q->max = NULL;
}


// valの値をキューに入れる。実行の成否を返す
bool enqueue(QUEUE* q, int val)
{
	// ToDo: valのデータをキューに追加します
	// 上手くいかない場合にはfalseを返します
	// メモリを使い切ったら先頭アドレスに戻って追加して下さい
	if (q == NULL || (q->tail + 2) % q->max == q->head) return false;
	else
	{
		q->data[(q->tail + 1)%q->max] = val;
		q->tail= (q->tail + 1) % q->max;
		return true;
	}

}


// addrから始まるnum個の整数をキューに入れる。実行の成否を返す
bool enqueue_array(QUEUE* q, int* addr, int num)
{
	// ToDo: addrからnum個のデータをキューに追加します
	// 上手くいかない場合にはfalseを返します
	// メモリを使い切ったら先頭アドレスに戻って追加して下さい
	if (q == NULL || num <= 0)return false;
	int fal = 0;
	for (int i = 1; i <= num; i++)
	{
		if ((q->tail + 1 + i) % q->max == q->head)
		{
			fal = 1;
		}
	}
	if (fal) return false;
	else
	{
		for (int i = 0; i < num; i++)
		{
			q->data[(q->tail + 1) % q->max] = addr[i];
			q->tail = (q->tail + 1) % q->max;
		}
		return true;
	}

}

// キューから一つの要素を取り出す(不具合時は0を返す)
int dequeue(QUEUE* q)
{
	// ToDo: 先頭のデータを返します
	if (q == NULL || (q->tail + 1) % q->max == q->head)return 0;
	else
	{
		int ret = 0;
		ret = q->data[q->head];
		q->head = (q->head+1)%q->max;
		return ret;
	}
}

// addrにキューからnumの要素を取り出す。取り出せた個数を返す
int dequeue_array(QUEUE* q, int* addr, int num)
{
	// ToDo: 先頭からnum個のデータをaddrに格納します
	if (q == NULL || addr == NULL|| (q->tail + 1) % q->max == q->head) return 0;
	else if (num <= 0) return false;
	else
	{
		int ret = 0;
		for (int i = 0; i < num; i++)
		{
			if ((q->tail + 1) % q->max == q->head)
			{
				break;
			}
			addr[i]= q->data[q->head];
			q->head = (q->head + 1) % q->max;
			ret++;
		}
		return ret;
	}
}

// キューが空かどうかを調べる
bool isEmpty(const QUEUE* q)
{
	if (q == NULL) return false;
	else if ((q->tail + 1) % q->max == q->head)
		return true;
	else
		return false;
}

//static int getMaxCount(const QUEUE* q)
//{
//	if (q == NULL || q->memory_begin == NULL) return 0;
//
//	return (int)(q->memory_end - q->memory_begin);
//}

// 挿入されたデータ数を得る
int countQueuedElements(const QUEUE* q)
{
	if (q == NULL|| (q->tail + 1) % q->max == q->head) return 0;
	else
	{
		int h= q->head;
		int t= q->tail;
		if (h > t)
		{
			t + q->max;
		}
		return t - h + 1;
	}
}

// 挿入可能なデータ数を得る
int countQueueableElements(const QUEUE* q)
{
	int queued;
	if (q == NULL || (q->tail + 1) % q->max == q->head)queued = 0;
	else
	{
		int h= q->head;
		int t= q->tail;
		if (h > t)
		{
			t + q->max;
		}
		queued= t - h + 1;
	}

	return q->max - queued-1;
}
