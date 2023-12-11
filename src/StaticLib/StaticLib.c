#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でキュー用のメモリを確保する
void initialize(QUEUE* q, size_t mem_size)
{
	if (q == NULL) return;

	q->memory_begin = (int*)malloc(mem_size);
	q->memory_end = q->memory_begin + mem_size / sizeof(int);
	q->head = q->memory_begin;
	q->tail = q->memory_begin;
}


// 確保したメモリを解放する
void finalize(QUEUE* q)
{
	if (q == NULL) return;

	free(q->memory_begin);

	q->memory_begin = NULL;
	q->memory_end = NULL;
	q->head = NULL;
	q->tail = NULL;
}


// valの値をキューに入れる。実行の成否を返す
bool enqueue(QUEUE* q, int val)
{
	if (q == NULL || countQueueableElements(q) == 0) return false;

	if (q->tail == q->memory_end){
		*(q->memory_begin) = val;
		q->tail = q->memory_begin + 1;
	}
	else {
		*(q->tail) = val;
		q->tail++;
	}
	return true;
}


// addrから始まるnum個の整数をキューに入れる。実行の成否を返す
bool enqueue_array(QUEUE* q, int* addr, int num)
{
	if (q == NULL || addr == NULL || countQueueableElements(q) < num || num <= 0) return false;

	for (int i = 0; i < num; i++)
	{
		enqueue(q, addr[i]);
	}
	return true;
}

// キューから一つの要素を取り出す(不具合時は0を返す)
int dequeue(QUEUE* q)
{
	if (q == NULL || countQueuedElements(q) == 0) return 0;

	int val = *(q->head);
	q->head = (q->head + 1 == q->memory_end) ? q->memory_begin : q->head + 1;
	return val;
}

// addrにキューからnumの要素を取り出す。取り出せた個数を返す
int dequeue_array(QUEUE* q, int* addr, int num)
{
	if (q == NULL || num <= 0 || countQueuedElements(q) == 0) return 0;

	int cnum = (num <= countQueuedElements(q)) ? num : countQueuedElements(q);
	for (int i = 0; i < cnum; i++) {
		addr[i] = dequeue(q);
	}
	return cnum;
}

// キューが空かどうかを調べる
bool isEmpty(const QUEUE* q)
{
	if (q == NULL) return false;

	return q->head == q->tail;
}

static int getMaxCount(const QUEUE* q)
{
	if (q == NULL || q->memory_begin == NULL) return 0;

	return (int)(q->memory_end - q->memory_begin);
}

// 挿入されたデータ数を得る
int countQueuedElements(const QUEUE* q)
{
	if (q == NULL || q->memory_begin == NULL) return 0;

	int max_counts = getMaxCount(q);
	return (q->tail - q->head + max_counts) % max_counts;
}

// 挿入可能なデータ数を得る
int countQueueableElements(const QUEUE* q)
{
	return getMaxCount(q) - countQueuedElements(q) - 1;
}
