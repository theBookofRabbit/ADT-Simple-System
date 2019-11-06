#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//#include "ADT.cpp"//<>只能用于头文件（.h文件）
typedef enum Status{
	OK,
	ERROR
}Status;

/*数据集函数*/
extern void dataset_for_AZ(char data[], int length);
extern void show_dataset(char data[], int length);

/*说明：顺序栈：*/
typedef struct SqStack{
	char* elem;
	int size;
	int top;
	int increment;
}SqStack;

extern Status InitStack_Sq(SqStack& S, int size, int inc);
extern Status DestroySqStack_Sq(SqStack& S);
extern Status StackEmpty_Sq(SqStack S);
extern void ClearSqStack_Sq(SqStack& S);
extern Status Push_Sq(SqStack& S, char e);
extern Status Pop_Sq(SqStack& S, char& e);
extern Status GetTop_Sq(SqStack S, char& e);
extern int SquareSqStack_Sq(SqStack S, char e);
extern void show_SqStack(SqStack SS);

/*说明：循环队列*/
typedef struct SqQueue {
	char* elem;
	int front;
	int rear;
	int maxSize;
}SqQueue;
extern Status InitQueue_Sq(SqQueue& Q, int size);
extern Status DestroyQueue_Sq(SqQueue& Q);
extern void QueueEmpty_Sq(SqQueue& Q);
extern Status QueueEmpty_Sq(SqQueue Q);
extern int QueueLength_Sq(SqQueue Q);
extern Status GetHead_Sq(SqQueue Q, char& e);
extern Status EnQueue_Sq(SqQueue& Q, char e);
extern Status DeleteSqQueue(SqQueue& Q, char& e);
extern Status SquareSqQueue_Sq(SqQueue Q, char e);
extern void ShowSqQueue_SQ(SqQueue SQ);

/*说明：线性表*/
typedef struct SqList {
	char* elem;
	int length;
	int size;
	int increment;
}SqList;
extern Status InitList_Sq(SqList& L, int size, int inc);
extern Status DestroySqList_Sq(SqList& L);
extern Status ClearSqList_Sq(SqList& L);
extern Status PutElem_Sq(SqList& L, char e);
extern Status DeleteSqList_Sq(SqList& L, char& e);
extern Status SearchSqList_Sq(SqList& L, char e);

/*说明：链表*/
typedef struct LNode {
	char data;
	LNode* next;
}LNode, * LinkList;
extern Status InitList_L(LinkList& L);
extern LinkList SearchList_L(LinkList& L, char e);
extern LinkList MakeList_L(char e);
extern Status InsertList_L(LinkList& p, LinkList & q);
extern Status DeleteList_L(LinkList& LL, char e);
extern void show_LinkList(LinkList LL);
extern void DestroyList_L(LinkList& LL);

/*说明：双向链表*/
typedef struct DuLNode {
	char data;
	DuLNode* next;
	DuLNode* prior;
}DuLNode,*DuLinkList;
extern Status InitList_Du(DuLinkList& DL);
extern Status DestroyDuLinkList_Du(DuLinkList& DL);
extern DuLinkList SearchDuLinkList_Du(DuLinkList DL, char e);
extern DuLinkList MakeDuLinkList_Du(char e);
extern DuLinkList PriorElem_DuL(DuLinkList p, char e);
extern DuLinkList AfterElem_DuL(DuLinkList p, char e);
extern Status DeleteAfterDuLinkList_Du(DuLinkList p, char& e);

/*链哈希表*/
/*链哈希表节点定义*/
typedef struct Node {
	char data;
	Node* next;
}Node, * Link;
/*链哈希表定义*/
typedef struct HashTable {
	Link* data;//储存哈希节点/链表的结点头
	int size;//哈希表的存储空间规模
	int count;//哈希表的实际储存元素
	int (*hash)(char data, int size);//哈希函数，输入要存的数据data和可以用的空间，计算出要分配的下标(所以函数类型是Int)
}HashTable, * HashLink;
extern Status InitHash(HashTable& HT, int size);
extern Status DestroyHashTable(HashTable& HT);
extern Link SearchHash(HashTable HT, char data);
extern Status InsertHash(HashTable& HT, char data);
extern Status DeleteHahshTable(HashTable& HT, char data, Link& tmp);
extern int 平方取中法_OA(char data, int size);
extern int 除留余数法_OA(char data, int size);
extern int 折叠法_OA(char data, int size);
extern int 平方取中法_OA(char data, int size);
extern void hash_choose(HashTable & HT);
extern void show_HashTable_for_AZ(HashTable HT);

/*开放定址哈希表*/
typedef struct HashTable_OA {
	char* data;
	int size;
	int count;
	int* tag;
	int (*hash)(char key, int size);//哈希函数
	void (*collision) (int& hashValue, int hashSize);//处理冲突函数
}HashTable_OA, * HashLink_OA;
extern void 线性探测法(int& p, int size);
extern void 二次探测法(int& p, int size);
extern void collsion_choose_for_OpenAdress(HashTable_OA& HTOA);
extern int 平方取中法(char data, int size);
extern int 除留余数法(char data, int size);
extern int 折叠法(char data, int size);
extern int 平方取中法(char data, int size);
extern void hash_choose_for_OpenAdress(HashTable_OA& HTOA);
extern Status InitHash_for_OpenAdress(HashTable_OA& HTOA, int size);
extern Status Search_HashTable_for_OpenAdress(HashTable_OA HTOA, char data, int& p, int& c);
extern Status InsertHash_for_OpenAdress(HashTable_OA& HTOA, char data);
extern Status DeleteHashTable_for_OpenAdress(HashTable_OA& HTOA, char data, char& e);
extern void ClearHash_for_OpenAdress(HashTable_OA& HTOA);
extern void show_HashTable_OA(HashTable_OA HTOA);





int main() {

	char dataset1[400] = { 0 };
	int length = 400;
	int choose_for_data = 0;

	dataset_for_AZ(dataset1, length);

	printf("=============================数据结构ADT。==========================\n");
	printf("以下是数据结构的展示：\n");
	printf("1.顺序栈；\n2.链表；\n3.循环队列；\n4.双向链表；\n5.线性表；\n6.链哈希表。\n7.开放定址哈希表。\n");
	printf("请输入以上ADT的对应序号以使用它。\n");

	int choose = 0;
	scanf_s("%d", &choose);
	switch (choose) {
	case 1: {
		//顺序栈
		SqStack SS;
		printf("==================顺序栈=======================\n");
		InitStack_Sq(SS, length, 5);
		int choose2 = 0;
		while (choose2 != 5) {
			printf("请输入你要执行的操作。\n");
			printf("1.入栈；\n2.出栈；\n3.查找；\n4.清空;\n5.退出。\n");
			scanf_s("%d", &choose2);

			switch (choose2) {
			case 1: {//入栈
				printf("你要自己输入字母呢，还是采用系统随机给出的字母？\n1.自己输入；\t2.系统给的。\n");
				char data = '[';//反正不能是A~Z中的一个
				int choose = 0;

				scanf_s("%d", &choose);
				getchar();
				if (choose == 1) {
					printf("请输入你要插入的大写字母.\n");
					scanf_s("%c", &data);
				}
				else if (choose == 2) {
					srand((unsigned)time(NULL));
					int t = rand() % length;
					printf("系统给的字母是：%c.\n", dataset1[t]);
					data = dataset1[t];
				}
				else {
					printf("没有正确输入选项。\n");
					return 0;
				}
				if (Push_Sq(SS, data) == OK) {
					printf("已压栈。\n");
				}
				else {
					printf("程序已经扩容（每次会扩容5个元素空间），但仍然空间不足，无法压栈。\n");
					return 0;
				}
				show_SqStack(SS);
				break;
			}
			case 2: {//出栈
				char c = '[';
				if (Pop_Sq(SS,c) == OK)
					printf("已出栈,栈元素为 %c\n",c);
				else
					printf("栈中已没有元素，请勿做出栈操作。\n");
				show_SqStack(SS);
				break;
			}
			case 3: {//查找
				char c;
				printf("输入你要查找的的大写字母。\n");
				getchar();
				scanf_s("%c", &c);
				
				int p = SquareSqStack_Sq(SS, c);
				if (p != -1) {
					printf("已找到，为第%d个元素。\n", p+1);
				}
				else {
					printf("没有找到，该数据不在栈中。\n");
				}
				break;
			}
			case 4: {//清空
				if (StackEmpty_Sq(SS) == OK) {
					printf("该顺序栈是空栈（做过销毁），没有数据，请不要做清空操作。\n");
				}
				else {
					ClearSqStack_Sq(SS);
					printf("已清空，不保证已经清空，请以下面的显示为准。\n");
					show_SqStack(SS);
				}
				break;
			}
			case 5: {//退出
				break;
			}
			default: {
				printf("输入指令有误，请重来。\n");
			}
			}
		}
		break;
	}
	case 2: {
		//链表
		LinkList LL;
		printf("==================链表=======================\n");
		InitList_L(LL);
		int choose3 = 0;
		while (choose3 != 5) {
			printf("请输入你要执行的操作。\n");
			printf("1.插入；\n2.删除；\n3.查找；\n4.清空;\n5.退出。\n");
			scanf_s("%d", &choose3);

			switch (choose3) {
			case 1: {//插入
				printf("你要自己输入字母呢，还是采用系统随机给出的字母？\n1.自己输入；\t2.系统给的。\n");
				char data = '[';//反正不能是A~Z中的一个
				int choose = 0;

				scanf_s("%d", &choose);
				getchar();
				if (choose == 1) {
					printf("请输入你要插入的大写字母.\n");
					scanf_s("%c", &data);
				}
				else if (choose == 2) {
					srand((unsigned)time(NULL));
					int t = rand() % length;
					printf("系统给的字母是：%c.\n", dataset1[t]);
					data = dataset1[t];
				}
				else {
					printf("没有正确输入选项。\n");
					return 0;
				}

				LinkList p = MakeList_L(data);
				if (p == NULL) {
					printf("抱歉，程序可用空间不足，构造结点失败。\n");
					return 0;
				}
				else {
					if (InsertList_L(LL, p) == OK) {
						printf("已插入。\n");
					}
					else {
						printf("链表尚未建立或者已被销毁，请勿做插入操作。\n");
					}
				}
				show_LinkList(LL);
				break;
			}
			case 2: {//删除
				printf("请输入你要删除的元素。\n");
				char data;
				getchar();
				scanf_s("%c", &data);
				
				if (DeleteList_L(LL, data) == OK) {
					printf("已删除。\n");
				}
				//删除失败（查找失败）的清空已经在删除函数中打印了解释。
				show_LinkList(LL);
				break;
			}
			case 3:{//查找
				char c;
				printf("输入你要查找的的大写字母。\n");
				getchar();
				scanf_s("%c", &c);

				LinkList p = SearchList_L(LL, c);
				if (p != NULL) {
					printf("已找到，为：%c  \n", p->data);
				}
				else {
					printf("链表中没有这个大写字母。\n");
				}
				break;
			}
			case 4: {//清空
				DestroyList_L(LL);
				printf("不保证绝对清空，以下面的显示为准。\n");
				show_LinkList(LL);
				break;
			}
			case 5: {//退出
				break;
			}
			default: {
				printf("你输入的是什么鬼东西,还是压根就没输入呢！\n");
			}
			}
		}
		break;
	}
	case 3: {
		//循坏队列
		SqQueue SQ;
		printf("==================循环队列=======================\n");
		InitQueue_Sq(SQ, length);
		int choose4 = 0;
		while (choose4 != 5) {
			printf("请输入你要执行的操作。\n");
			printf("1.插入；\n2.删除；\n3.查找；\n4.清空;\n5.退出。\n");
			scanf_s("%d", &choose4);

			switch (choose4) {
			case 1: {//插入
				printf("你要自己输入字母呢，还是采用系统随机给出的字母？\n1.自己输入；\t2.系统给的。\n");
				char data = '[';//反正不能是A~Z中的一个
				int choose = 0;

				scanf_s("%d", &choose);
				getchar();
				if (choose == 1) {
					printf("请输入你要插入的大写字母.\n");
					scanf_s("%c", &data);
				}
				else if (choose == 2) {
					srand((unsigned)time(NULL));
					int t = rand() % length;
					printf("系统给的字母是：%c.\n", dataset1[t]);
					data = dataset1[t];
				}
				else {
					printf("没有正确输入选项。\n");
					return 0;
				}

				if (EnQueue_Sq(SQ, data) == OK) {
					printf("已入队。\n");
					ShowSqQueue_SQ(SQ);
				}
				else {
					printf("发生了小概率事件，入队失败了。\n"); 
					return 0;
				}
				break;
			}
			case 2: {//出队
				char e;
				if (DeleteSqQueue(SQ, e) == OK) {
					printf("出队成功，队尾元素是：%c \n", e);
				}
				else {
					printf("队空，请勿做出队操作。\n");
				}
				ShowSqQueue_SQ(SQ);
				break;
			}
			case 3: {//查找
				char c;
				printf("输入你要查找的的大写字母。\n");
				getchar();
				scanf_s("%c", &c);

				if (SquareSqQueue_Sq(SQ, c) == OK) {
					printf("已找到，该元素存在于此循环队列里。\n");
				}
				else {
					printf("找不到或者队空。\n");
				}
				break;
			}
			case 4: {//清空
				DestroyQueue_Sq(SQ);
				printf("已清空，不保证绝对清空，还请以下面的展示为准。\n");
				ShowSqQueue_SQ(SQ);
				break;
			}
			case 5: {//退出
				break;
			}
			default: {
				printf("你输入的是什么鬼东西,还是压根就没输入呢！\n");
			}
			}
		}
		break;
	}
	case 4: {
		//双向链表
		break;
	}
	case 5: {
		//线性表
		break;
	}
	case 6: {
		//哈希表
		HashTable HT;
		printf("==================哈希表=======================\n");
		printf("在一切开始之前，我需要你指定一个哈希函数：");
		InitHash(HT, length);//HT.hash函数已经选定
		int choose1 = 0;
		while (choose1 != 5) {
			printf("请输入你要执行的操作：\n");
			printf("1.插入；\n2.删除；\n3.查找；\n4.清空;\n5.退出。\n温馨提示：清空哈希表仍会保留你之前选定的哈希函数，如要彻底删除哈希表的数据，可以选择退出后重新再来。\n");

			scanf_s("%d", &choose1);

			switch (choose1) {
			case 1: {//输入
				printf("你要自己输入字母呢，还是采用系统随机给出的字母？\n1.自己输入；\t2.系统给的。\n");
				char data = '[';//反正不能是A~Z中的一个
				int choose = 0;

				scanf_s("%d", &choose);
				getchar();
				if (choose == 1) {
					printf("请输入你要插入的大写字母.\n");
					scanf_s("%c", &data);
				}
				else if(choose == 2){
					srand((unsigned)time(NULL));
					int t = rand() % length;
					printf("系统给的字母是：%c.\n",dataset1[t]);
					data = dataset1[t];
				}
				else {
					printf("没有正确输入选项。\n");
					return 0;
				}

				if (InsertHash(HT, data) == OK)
					printf("已插入。\n");
				//InsertHash函数已经对查找不成功做出了说明
				show_HashTable_for_AZ(HT);
				break;
			}case 2: {//删除
				char c = '[';
				Link tmp = NULL;
				printf("输入你要删除的哈希表中已存在的大写字母。\n");
				getchar();
				scanf_s("%c", &c);
				if (DeleteHahshTable(HT, c, tmp) == OK)
					printf("已删除。\n");
				else
					printf("删除失败。\n");
				show_HashTable_for_AZ(HT);
				break;
			}
			case 3: {//查找
				char c;
				printf("输入你要查找的的大写字母。\n");
				getchar();
				scanf_s("%c", &c);
				Link p = SearchHash(HT, c);
				if (p != NULL) {
					printf("已找到，为 %c.",p->data);
				}//SearchHash函数已经做了对查找失败的解释
				break;
			}
			case 4: {//清空
				DestroyHashTable(HT);
				break;
			}
			case 5: {//退出
				break;//因为while条件的原因，一旦choose1== 5 就会退出循环了。
			}
			default: {
				printf("你输入的是什么鬼东西,还是压根就没输入呢！\n");
			}
			}
		}
		break;
	}
	case 7: {//开放定址哈希表
		HashTable_OA HTOA;
		printf("==================开放定址哈希表=======================\n");
		printf("在一切开始之前，我需要你指定一个哈希函数：");
		InitHash_for_OpenAdress(HTOA, length);
		int choose4 = 0;
		while (choose4 != 5) {
			printf("请输入你要执行的操作：\n");
			printf("1.插入；\n2.删除；\n3.查找；\n4.清空;\n5.退出。\n温馨提示：清空哈希表仍会保留你之前选定的哈希函数和处理冲突函数，如要彻底删除哈希表的数据和配置，可以选择退出后重新再来。\n");

			scanf_s("%d", &choose4);
			switch (choose4) {
			case 1: {//插入
				printf("你要自己输入字母呢，还是采用系统随机给出的字母？\n1.自己输入；\t2.系统给的。\n");
				char data = '[';//反正不能是A~Z中的一个
				int choose = 0;

				scanf_s("%d", &choose);
				getchar();
				if (choose == 1) {
					printf("请输入你要插入的大写字母.\n");
					scanf_s("%c", &data);
				}
				else if (choose == 2) {
					srand((unsigned)time(NULL));
					int t = rand() % length;
					printf("系统给的字母是：%c.\n", dataset1[t]);
					data = dataset1[t];
				}
				else {
					printf("没有正确输入选项。\n");
					return 0;
				}

				if (InsertHash_for_OpenAdress(HTOA, data) == OK) {
					printf("已插入。\n");
					show_HashTable_OA(HTOA);
				}
				break;
			}
			case 2: {//删除
				char c = '[';
				char e;
				printf("输入你要删除的哈希表中已存在的大写字母。\n");
				getchar();
				scanf_s("%c", &c);
				if (DeleteHashTable_for_OpenAdress(HTOA, c, e) == OK) {
					printf("已删除 %c \n",e);
					show_HashTable_OA(HTOA);
				}//删除失败的提示已经在该删除函数中说明了。
				break;
			}
			case 3: {//查找
				char c;//查找数据
				int p;//位标
				int count = 0;//冲突次数
				printf("输入你要查找的的大写字母。\n");
				getchar();
				scanf_s("%c", &c);

				if (Search_HashTable_for_OpenAdress(HTOA, c, p, count) == OK) {
					printf("找到了，你要找的 %c 存在这个开放定址哈希表中。\n冲突次数：%d \n",HTOA.data[p],count);
					show_HashTable_OA(HTOA);
				}
				else {
					printf("找不到。\n");
				}
				break;
			}
			case 4: {//清空
				ClearHash_for_OpenAdress(HTOA);
				printf("已清空。\n");
				show_HashTable_OA(HTOA);
				break;
			}
			case 5: {//退出
				break;
			}
			default: {
				printf("你输入的是什么鬼东西,还是压根就没输入呢！\n");
			}
			}
		}
		break;
	}


	}
	return 0;

}
