#include<stdio.h>
#include<stdlib.h>

typedef enum {
	OK,
	ERROR
}Status;

typedef struct HashTable_OA{
	char* data;
	int size;
	int count;
	int* tag;//标记数组：0--该下标位置没有元素；1--该下标位置有有效元素；-1--该下标位置本来有元素，但是经过了删除操作，所以可以继续依照它球的下一个地址（冲突处理不停止，没找到0就不能停止查找）
	int (*hash)(char key, int size);//哈希函数
	void (*collision) (int& hashValue, int hashSize);//处理冲突函数--冲突函数是接收当前冲突的位标，然后根据这个位标直接计算出下一个位标
}HashTable_OA,*HashLink_OA;


/*各种处理冲突函数*/
void 线性探测法(int& p, int size) {
	p = (p + 2) % size;
}

void 二次探测法(int& p, int size) {
	p = (p + p * p) % size;
}

/*选择处理冲突函数*/
void collsion_choose_for_OpenAdress(HashTable_OA& HTOA) {
	printf("请输入序号以确定不同的处理冲突策略。\n");
	printf("1.线性探测法；\n2.二次探测法（平方探测法）。\n");
	int choose = 0;
	scanf_s("%d", &choose);
	switch (choose) {
	case 1: {
		HTOA.collision = 线性探测法;
		break;
	}
	case 2: {
		HTOA.collision = 二次探测法;
		break;
	}
	default: {
		printf("输入指令有误。\n");
	}
	}
}

/*哈希函数*/
int 直接定址法_OA(char data, int size) {
	return (2 * data + 10) % size;//放大2倍，平移10位，这里为了避免超出范围，还是模以size
}

int 除留余数法_OA(char data, int size) {
	return data % size;
}

int 折叠法_OA(char data, int size) {
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

int 平方取中法_OA(char data, int size) {//这个适用于大数
	long tmp = data * data;
	while (tmp >= 1000) {
		tmp -= tmp / 1000 * 1000;
	}
	return tmp % size;
}


/*选择不同的哈希函数*/
void hash_choose_for_OpenAdress(HashTable_OA & HTOA) {//传入数组相当于传指针。数组名会退化为指针，因此不用想其他变量一样加 & 
	printf("请输入序号以确定不同的哈希函数类型。\n");
	printf("1.直接定址法；\n2.除留余数法；\n3.折叠法；\n4.平方取中法。\n");
	int choose = 0;
	scanf_s("%d", &choose);
	switch (choose) {
	case 1: {
		HTOA.hash = 直接定址法_OA; break;
	}
	case 2: {
		HTOA.hash = 除留余数法_OA; break;
	}
	case 3: {
		HTOA.hash = 折叠法_OA; break;
	}
	case 4: {
		HTOA.hash = 平方取中法_OA; break;
	}
	default: {
		printf("是不是爷给你惯着了，你不按规矩输入是不？重来吧。\n");
		return;
	}
	}
	printf("哈希函数已选定为: %d\n", choose);
}


/*初始化开放定址哈希表*/
Status InitHash_for_OpenAdress(HashTable_OA& HTOA, int size) {
	HTOA.data = (char*)malloc(size * sizeof(char));
	HTOA.tag = (int*)malloc(size * sizeof(int));
	if (HTOA.data == NULL || HTOA.tag == NULL) {
		printf("程序无法分配空间。\n");
		return ERROR;
	}
	for (int i = 0; i < size; i++) {
		HTOA.tag[i] = 0;
		HTOA.data[i] = '\0';
	}
	HTOA.size = size;
	HTOA.count = 0;
	hash_choose_for_OpenAdress(HTOA);
	collsion_choose_for_OpenAdress(HTOA);
	return OK;
}

/*查找--因为查找次数和冲突次数不属于数据数组的属性，故而不能作为数据的一部分*/
Status Search_HashTable_for_OpenAdress(HashTable_OA HTOA, char data, int& p,int& c) {

	p = HTOA.hash(data, HTOA.size);
	while((1 == HTOA.tag[p] && HTOA.data[p] != data) || -1 == HTOA.tag[p]) {//该位置不说终止位置且数据不是要找的，或者当前结点仅仅是被删除的，不能在这里停下，就继续查找。
		HTOA.collision(p, HTOA.size);//把改后的冲突地址赋给p
		c++;//记录data的冲突次数--data不同，c不同。
	}
	if (1 == HTOA.tag[p] && HTOA.data[p] == data) {
		return OK;
	}
	if (HTOA.tag[p] == 0) {
		return ERROR;
	}
	return ERROR;
}


/*插入--哈希表不能允许重复元素的存在与插入*/
Status InsertHash_for_OpenAdress(HashTable_OA& HTOA, char data) {

	int p, c = 0;
	if (Search_HashTable_for_OpenAdress(HTOA, data, p, c) == OK) {
		printf("该元素已存在于此哈希表中，而哈希表不允许有重复元素，请勿做插入操作。\n");
		return ERROR;
	}
	else {
		HTOA.data[p] = data;
		HTOA.tag[p] = 1;
		++HTOA.count;
		return OK;
	}
}

/*删除*/
Status DeleteHashTable_for_OpenAdress(HashTable_OA& HTOA, char data,char& e) {
	if (HTOA.data == NULL) {
		printf("尚未初始化。\n");
		return ERROR;
	}
	int flag = 1;
	for (int i = 0; i < HTOA.size; i++) {
		if (HTOA.data[i] < 'Z' && HTOA.data[i] > 'A') {
			flag = 0;
		}
	}
	if (flag) {
		printf("空表，请勿删除操作。\n");
		return ERROR;
	}

	int p = HTOA.hash(data, HTOA.size);
	while ((1 == HTOA.tag[p] && HTOA.data[p] != data) || -1 == HTOA.tag[p]) {
		HTOA.collision(p, HTOA.size);//把改后的冲突地址赋给p
	}
	if (1 == HTOA.tag[p] && HTOA.data[p] == data) {
		//HTOA.tag[p] == -1;//???为什么不起作用？？？
		//printf("HTOA的data[p] == %c,tag[p] == %d\n", HTOA.data[p], HTOA.tag[p]);
		HTOA.data[p] = '\0';
		HTOA.count--;
		e = data;
		return OK;
	}
	if(0 == HTOA.tag[p]) {
		printf("该元素不存在于此哈希表中，你删除啥呢？\n");
		return ERROR;
	}
}

/*清空*/
void ClearHash_for_OpenAdress(HashTable_OA& HTOA) {
	for(int i = 0;i < HTOA.size;i++){
		HTOA.data[i] = '\0';
	}
}


/*显示*/
void show_HashTable_OA(HashTable_OA HTOA) {
	printf("++++++++++++++++开放定址哈希表的元素有：++++++++++\n");
	for (int i = 0; i < HTOA.size; i++) {
		if (HTOA.tag[i] == 1 && HTOA.data[i] != '\0') {
			printf("%c		", HTOA.data[i]);
		}
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++\n");
}
