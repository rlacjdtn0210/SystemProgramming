// <���� �������� ������>
// �������� ó�� ������ ��Ȯ�� �� �� ���� ���� ���� �� ����ȭ ó���� ����ߴ�.
// ��, ���ڿ� �Է� �� ó�� �� NULL���� �����Ⱚ�� �ʱ�ȭ�Ͽ� ����ε� ���� ����ϴµ���
// ���ڿ� �Լ� Ȱ�뿡 �־� �ð��� �ټ� ���� �Һ��ߴ�.

#define _CRT_SECURE_NO_WARNINGS 
#include "���.h"

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