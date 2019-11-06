#include<stdio.h>
#include<stdlib.h>
//#include "ADT.cpp"//<>只能用于头文件（.h文件）
typedef enum {
	OK,
	ERROR
}Status;

typedef struct LNode {
	char data;
	LNode* next;
}LNode, * LinkList;


/*
链表
*/
/*初始化空链表*/
Status InitList_L(LinkList& L) {
	L = (LinkList)malloc(sizeof(LNode));
	if (L == NULL) return ERROR;
	L->next = NULL;
	return OK;
}
/*查表*/
LinkList SearchList_L(LinkList& L,char e) {
	if (L == NULL)return NULL;
	LinkList p;
	p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	if (p != NULL)return p;
	return NULL;
}
/*构造节点*/
LinkList MakeList_L(char e) {
	LinkList p = (LinkList)malloc(sizeof(LNode));
	if (p == NULL)return NULL;
	p->data = e;
	p->next = NULL;
	return p;
}
/*插入链表某个节点的直接后继节点--可以是头节点的后继结点*/
Status InsertAfterList_L(LinkList &p, LinkList &q) {
	if (p == NULL || q == NULL)return ERROR;
	q->next = p->next;
	p->next = q;
	return OK;
}

/*插入表尾*/
Status InsertList_L(LinkList& p, LinkList& q) {
	if (p == NULL || q == NULL) return ERROR;
	LinkList temp = p;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = q;
	temp->next->next = NULL;
	return OK;
}

/*删除链表对应元素的结点*/
Status DeleteList_L(LinkList & LL,char e) {
	LinkList p = SearchList_L(LL, e);
	if (p == NULL) {
		printf("链表中没有这个元素，你删除啥呢？\n");
		return ERROR;
	}
	else {
		p->data = '0';//耍个小聪明，‘0’是不会出现在正常的输入里的。所以它相当于被删除了，输出时做点手脚就好。
		return OK;
	}
}
 
/*删除链表的直接后继节点,并把删除的元素值赋给e*/
Status DeleteAfterList_L(LinkList & p, char& e) {
	if (p == NULL || p->next == NULL)return ERROR;
	e = p->next->data;
	p->next = p->next->next;
	return OK;
}

/*销毁链表（不彻底）*/
void DestroyList_L(LinkList& LL) {
	LL->data = NULL;
	LL->next = NULL;
}

/*显示链表全部元素*/
void show_LinkList(LinkList LL) {
	if (LL == NULL) {
		printf("链表为初始化或者已销毁，无法显示，也请勿做插入和删除操作。\n");
	}
	printf("+++++++++++++++++++++++链表+++++++++++++++++++++\n");
	LinkList p = LL->next;//头节点没有数据要展示
	do {
		if (p != NULL && p->data != NULL) {
			if(p->data != '0')//因为我对删除操作动了点手脚
				printf("%c		", p->data);
			p = p->next;
		}
	} while (p != NULL);
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++\n");
}

