#include<stdio.h>
#include<stdlib.h>

typedef enum {
	OK,
	ERROR
}Status;

typedef struct {
	char* elem;
	int size;
	int top;
	int increment;
}SqStack;

/*
顺序栈
*/
/*初始化顺序栈*/
Status InitStack_Sq(SqStack& S, int size, int inc) {
	S.elem = (char*)malloc(size * sizeof(char));
	if (S.elem == NULL) return ERROR;
	S.size = size;
	S.increment = inc;
	S.top = 0;
	return OK;
}
/*销毁顺序栈*/
Status DestroySqStack_Sq(SqStack& S) {
	S.elem = NULL;
	if (S.elem != NULL) return ERROR;
	S.size = S.top = 0;
	S.increment = 0;
	return OK;
}
/*判空顺序栈*/
Status StackEmpty_Sq(SqStack S) {
	if (S.elem == NULL)
		return OK;
	else
		return ERROR;
}
/*清空顺序栈*/
void ClearSqStack_Sq(SqStack& S) {
	int size = S.size;
	int increment = S.increment;
	DestroySqStack_Sq(S);
	InitStack_Sq(S, size, increment);
}
/*将元素e压入顺序栈S*/
Status Push_Sq(SqStack& S, char e) {
	//这一大段全是讲扩容的
	char* newbase;
	if (S.top >= S.size) {
		newbase = (char*)realloc(S.elem, (S.increment + S.size) * sizeof(char));
		if (newbase == NULL) return ERROR;
		S.elem = newbase;
		S.size += S.increment;
	}
	//========到这里为止============
	S.elem[S.top++] = e;
	return OK;
}
/*将顺序栈S的栈顶元素出栈，并返回给元素e*/
Status Pop_Sq(SqStack& S, char& e) {
	if (S.top == 0) return ERROR;
	e = S.elem[--S.top];
	return OK;
}
/*取栈顶元素并用e返回（不出栈）*/
Status GetTop_Sq(SqStack S, char& e) {
	if (S.top == 0) return ERROR;
	e = S.elem[--S.top];
	S.top++;
	return OK;
}
/*查询顺序表*/
int SquareSqStack_Sq(SqStack S, char e) {
	for (int i = 0; i < S.top; i++) {
		if (S.elem[i] == e)
			return i;
	}
	return -1;
}

/*显示顺序栈全部元素*/
void show_SqStack(SqStack SS) {
	printf("++++++++++++++++顺序栈的元素有：++++++++++\n");
	for (int i = 0; i < SS.top; i++) {
		printf("%c		", SS.elem[i]);
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
}
