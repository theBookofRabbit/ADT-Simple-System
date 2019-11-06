#include<stdio.h>
#include<stdlib.h>

typedef enum {
	OK,
	ERROR
}Status;

typedef struct {
	char* elem;
	int front;
	int rear;
	int maxSize;
}SqQueue;

/*
循环队列
*/

/*构造空队列*/
Status InitQueue_Sq(SqQueue& Q, int size) {
	Q.elem = (char*)malloc(size * sizeof(char));
	if (Q.elem == NULL) return ERROR;
	Q.maxSize = size;
	Q.front = Q.rear = 0;
	return OK;
}
/*清空队列*/
Status DestroyQueue_Sq(SqQueue& Q) {
	for (int i = 0; i < Q.maxSize; i++) {
		Q.elem[i] = '\0';
	}
	Q.maxSize = 0;
	Q.front = Q.rear = 0;
	return OK;
}
/*置空*/
void QueueEmpty_Sq(SqQueue& Q) {
	int maxSize = Q.maxSize;
	DestroyQueue_Sq(Q);
	InitQueue_Sq(Q, maxSize);
}
/*判空*/
Status QueueEmpty_Sq(SqQueue Q) {
	if (Q.elem == NULL)
		return OK;
	else
		return ERROR;
}

/*显示循环队列全部元素*/
void ShowSqQueue_SQ(SqQueue SQ) {
	if (SQ.maxSize == 0 || SQ.elem == NULL) {
		printf("该循环队列已清空或者尚未初始化，故而不予显示。\n");
		return;
	}
	printf("++++++++++++++++循环队列的元素有：++++++++++\n");
	for(int i = 0;i < SQ.maxSize;i++){
		if ('A' <= SQ.elem[i] && 'Z' >= SQ.elem[i]) {//因为循环队列比较特殊，它不能靠一个元素为'\0'来判断终止条件。
			printf("%c		", SQ.elem[i]);
		}
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
}

/*返回队列的长度*/
int QueueLength_Sq(SqQueue Q) {
	int length = 0;
	for (int i = 0; i < Q.maxSize; i++) {
		if ('A' <= Q.elem[i] && 'Z' >= Q.elem[i])
			length++;
	}
	return length;
	/*if (Q.rear > Q.front)
		return Q.rear - Q.front;
	if (Q.rear < Q.front)
		return (Q.maxSize - Q.front) + Q.rear;
	if (Q.front == Q.rear)
		return 0;*/
}
/*返回队头元素给e*/
Status GetHead_Sq(SqQueue Q, char& e) {
	if (QueueLength_Sq(Q) <= 0)
		return ERROR;
	e = Q.elem[Q.front];
	return OK;
}
/*入队*/
Status EnQueue_Sq(SqQueue& Q, char e) {
	if (Q.front == (Q.rear + 1) % Q.maxSize) {
		printf("队列空间已满，无法入队。\n");//记得终止程序
		return ERROR;
	}
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxSize;
	return OK;
}
/*出队*/
Status DeleteSqQueue(SqQueue& Q, char& e) {
	if (QueueLength_Sq(Q) == 0)//队空警告
		return ERROR;
	int p = Q.front;
	while (Q.elem[p] == '\0') {//这是考虑到maxSize小的情况，但是我在主函数里初始化设置为400.所以它基本不会出现rear>maxSize的情况。
		p++;
		
	}
	if (Q.elem[p] != '\0') {
			e = Q.elem[p];
			Q.elem[p] = '\0';//书上的是靠移动指针来决定显示，我觉得直接置为'\0'不就好了，省的显示还得判断来判断去的；何况还保存了数据给e。
			Q.front = p;//一切处理号之后，Q.front来接手p的使命
			Q.front = (Q.front + 1) % Q.maxSize;
			return OK;
		}
}
/*查找*/
Status SquareSqQueue_Sq(SqQueue Q, char e) {
	if (QueueLength_Sq(Q) == 0)
		return ERROR;
	if (Q.rear > Q.front) {
		for (int i = Q.front; i < Q.rear; i++) {
			if (Q.elem[i] == e)
				return OK;
		}
		return ERROR;
	}
	if (Q.rear < Q.front) {
		for (int i = 0; i <= Q.front; i++)
			if (Q.elem[i] == e)
				return OK;
		for (int i = Q.rear; i < Q.maxSize; i++)
			if (Q.elem[i] == e)
				return OK;
		return ERROR;
	}
}

