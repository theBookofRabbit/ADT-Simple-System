#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include<random>

/*
随机产生A~Z中的字母的length长度的数组
*/
void dataset_for_AZ(char data[],int length) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i++) {
		int e = rand() % (26 - 0) + 'A';
		data[i] = e;
	}
}

///*随机产生随机数*/
//void dataset_for_Number(char data[], int length) {
//	std::default_random_engine e;//产生大随机数，这是STL库函数
//	e.seed(10);
//	for (int i = 0; i < length; i++) {
//		int temp = e();
//		if(e() < 0)
//			data[i] = -1 * temp;
//		else {
//			data[i] = temp;
//		}
//	}
//}


/*展示数据集*/
void show_dataset(char data[], int length) {
	for (int i = 0; i < length; i++) {
		printf("%c	", data[i]);
	}
}
