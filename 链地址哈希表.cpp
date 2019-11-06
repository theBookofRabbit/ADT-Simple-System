#include<stdio.h>
#include<stdlib.h>

typedef enum {
	OK,
	ERROR
}Status;


/*链地址哈希表*/


/*链哈希表节点定义*/
typedef struct Node{
	char data;
	Node* next;
}Node,*Link;
/*链哈希表定义*/
typedef struct HashTable {
	Link* data;//储存哈希节点/链表的结点头
	int size;//哈希表的存储空间规模
	int count;//哈希表的实际储存元素
	int (*hash)(char data, int size);//哈希函数，输入要存的数据data和可以用的空间，计算出要分配的下标(所以函数类型是Int)
}HashTable,*HashLink;

int 直接定址法(char data, int size) {
	return (2 * data + 10) % size;//放大2倍，平移10位，这里为了避免超出范围，还是模以size
}

int 除留余数法(char data, int size) {
	return data % size;
}

int 折叠法(char data, int size) {
	int  j = 1, qu, sum = 0;
	for (int i = 0; i < 2; i++) {
		j *= 10;
	}
	while (data != 0) {
		qu = data % j;
		sum += qu;
		data /= j;
	}
	return sum % size;
}

int 平方取中法(char data, int size) {//这个适用于大数
	long tmp = data * data;
	while (tmp >= 1000) {
		tmp -= tmp / 1000 * 1000;
	}
	return tmp % size;
}

/*选择不同的哈希函数*/
void hash_choose(HashTable& HT) {//传入数组相当于传指针。数组名会退化为指针，因此不用想其他变量一样加 & 
	printf("请输入序号以确定不同的哈希函数类型。\n");
	printf("1.直接定址法；\n2.除留余数法；\n3.折叠法；\n4.平方取中法。\n");
	int choose = 0;
	scanf_s("%d", &choose);
	switch (choose) {
	case 1: {
		HT.hash = 直接定址法; break;
	}
	case 2: {
		HT.hash = 除留余数法; break;
	}
	case 3: {
		HT.hash = 折叠法; break;
	}
	case 4: {
		HT.hash = 平方取中法; break;
	}
	default: {
		printf("是不是爷给你惯着了，你不按规矩输入是不？重来吧。\n");
		return;
	}
	}
	printf("哈希函数已选定为: %d\n", choose);
}

/*初始化哈希表，不过要指定哈希函数，初始化时的哈希函数一旦确定，之后就不可更改--hash函数变成H.hash */
Status InitHash(HashTable& HT, int size) {//(*hash)相当于char a[]中的a,你也可以选择传char * a;
	HT.data = (Link*)malloc(size * sizeof(Node));
	if (HT.data == NULL) return ERROR;
	for (int i = 0; i < size; i++) {
		HT.data[i] = NULL;
	}
	HT.size = size;
	hash_choose(HT);
	HT.count = 0;
}

/*清空哈希表*/
Status DestroyHashTable(HashTable& HT) {
	HT.count = 0;
	if (HT.data == NULL) {
		printf("此链哈希表连数据表都没建立起来(没初始化)，你瞎清空什么呢？\n");
		return ERROR;
	}
	for (int i = 0; i < HT.size; i++) {
		HT.data[i] = NULL;
	}
	printf("此哈希表已清空。\n");
	return OK;
}

/*查找链哈希表：没找到就返回NULL*/
Link SearchHash(HashTable HT, char data) {
	if (HT.data == NULL) {
		printf("哈希表没有初始化。\n");
		return NULL;
	}
	int p = HT.hash(data, HT.size);
	Link q = (Link)malloc(sizeof(Node));
	for (q = HT.data[p]; q != NULL;q = q->next ) {
		if (q != NULL && q->data == data)//这里，q在输入第100位时会出现q为空的错误 。
			return q;
	}
	printf("该元素找不到，或者此哈希表已销毁, 如已做销毁请不要查找或者插入。\n");
	return NULL;
}

/*插入链哈希表，错误会输出错误信息*/
Status InsertHash(HashTable& HT,char data) {
	if (HT.data == NULL) {
		printf("此哈希表已销毁,请不要查找或者插入。\n");
		return ERROR;
	}
	int p = HT.hash(data, HT.size);//待插入位标
	if (SearchHash(HT, data) != NULL) {
		printf("该内容已存在于哈希表中，请勿重复插入。\n温馨提示：哈希表不允许重复。\n");
		return ERROR;
	}
	else {//查找不成功的情况
		int p;
		Link np;
		p = HT.hash(data, HT.size);
		np = (Link)malloc(sizeof(Node));
		if (nullptr == np) {
			printf("没有空间来插入，插入失败。\n");
			return ERROR;
		}
		np->data = data;
		np->next = HT.data[p];
		HT.data[p] = np;
		return OK;
	}
}

/*删除链哈希表,并把删除的结点存到tmp*/
Status DeleteHahshTable(HashTable& HT, char data,Link & tmp) {
	int p = HT.hash(data, HT.size);//待插入位标
	Link q = SearchHash(HT, data);
	if (q == NULL) {
		printf("该内容不存在于哈希表中，请勿做删除操作。\n");
		return ERROR;
	}
	else {//查找成功的情况
		q->data = '0';//耍点小聪明，将要删除的数据置为不可能“存在”的数据
		
		return OK;
	}
}


/*打印数据集是字母集的链哈希表全部元素*/
void show_HashTable_for_AZ(HashTable HT) {
	printf("++++++++++++++++链哈希表的元素有：++++++++++\n");
	Link p;
	for (int i = 0; i < HT.size; i++) {
		for (p = HT.data[i]; p != NULL; p = p->next) {
			if(p->data != '0')//因为我在删除函数那里做了凡是要删除的将数据改成‘0’.
				printf("%c		", p->data);
		}
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
}
