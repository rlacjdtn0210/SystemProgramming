// <구현 과정에서 느낀점>
// 쓰레드의 처리 순서를 정확히 알 수 없어 로직 구현 시 동기화 처리가 곤란했다.
// 또, 문자열 입력 및 처리 시 NULL값과 쓰레기값을 초기화하여 제대로된 값을 출력하는데에
// 문자열 함수 활용에 있어 시간을 다소 많이 소비했다.

#define _CRT_SECURE_NO_WARNINGS 
#include "헤더.h"

using namespace std;

#pragma warning(disable:4996)

int main(void) {
	InitializeCriticalSection(&one);
	int flag = 0;
	while (flag != 1) {
		Thread thread[2];

		thread[0].fileopen();
		thread[1].fsearch();

		for (int i = 0; i < 2; i++) {
			WaitForMultipleObjects(1, thread[i].get(), TRUE, INFINITE);
			thread[i].~Thread();
		}
		cout << "0 : Continue , 1 : Exit => "; cin >> flag;
		cout << "----------------------------------------------------" << endl;
		cin.ignore();
	}

	DeleteCriticalSection(&one);
	system("pause");
	return 0;
}