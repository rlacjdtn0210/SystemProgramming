#pragma once
#ifndef CLASS_H
#define CLASS_H

#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "string"

using namespace std;

CRITICAL_SECTION one;
string filename = "";
FILE *fp = NULL;

DWORD WINAPI ThreadProc_fopen(LPVOID lpParam);
DWORD WINAPI ThreadProc_fsearch(LPVOID IpParam);

class Thread {
private:
	DWORD dwThreadID;
	HANDLE hThread;

public:
	Thread() {
		dwThreadID = 0;
		hThread = NULL;
	}

	~Thread() {
		dwThreadID = NULL;
		CloseHandle(hThread);
	}

	HANDLE* get() {
		return &hThread;
	}

	void fileopen() {
		hThread = CreateThread(
			NULL,
			0,
			ThreadProc_fopen,
			&one,
			0,
			&dwThreadID
		);
		if (hThread == NULL) {
			cout << "Thread creating is failed" << endl;
			return;
		}
	}

	void fsearch() {
		hThread = CreateThread(
			NULL,
			0,
			ThreadProc_fsearch,
			&one,
			0,
			&dwThreadID
		);
		if (hThread == NULL) {
			cout << "Thread creating is failed" << endl;
			return;
		}
	}
};

DWORD WINAPI ThreadProc_fopen(LPVOID lpParam) {
	PCRITICAL_SECTION One = (PCRITICAL_SECTION)lpParam;

	EnterCriticalSection(One); {
		SYSTEMTIME time;
		GetLocalTime(&time);
		cout << "Write the name of the open file : "; getline(cin, filename);

		try {
			fp = fopen(filename.c_str(), "r");
			if (fp == NULL) throw fp;
			else {
				cout << "LocalPath:> " << filename << endl;
			}
		}

		catch (FILE *fp) {
			if (fp == NULL) {
				cout << "File opening is failed." << endl;
				return 0;
			}
		}

		cout << "Open file time : ";
		cout << time.wYear << '/' << time.wMonth << '/' << time.wDay << ' ';
		cout << time.wHour << ':' << time.wMinute << ':' << time.wSecond << '+';
		cout << time.wMilliseconds << endl;
	}
	LeaveCriticalSection(One);

	return 0;
}

DWORD WINAPI ThreadProc_fsearch(LPVOID IpParam) {
	PCRITICAL_SECTION One = (PCRITICAL_SECTION)IpParam;
	while (true) {
		if (filename != " ") {
			EnterCriticalSection(One); {
				char buffer[300] = { 0 };
				int line_num = 0;
				clock_t start, end;
				string data = "";

				cout << "Search data : "; cin >> data;
				start = clock();
				while (fgets(buffer, 300, fp)) {
					line_num++;
					char temp[100] = { 0 };
					char *ptr = strstr(buffer, data.c_str());
					if (ptr != NULL) {
						if (ptr - 1 != " ") {
							strncpy(temp, ptr - 1, 3);
							cout << filename << " : " << line_num << ' ' << '(' << temp << ')' << endl;
						}
						else if (ptr - 1 == " ") {
							strncpy(temp, ptr, 2);
							cout << filename << " : " << line_num << ' ' << '(' << temp << ')' << endl;
						}
					}
					else continue;
				}
				fclose(fp);
				end = clock();
				cout << "Run time : " << (double)end - start << "msec" << endl;
			}
			LeaveCriticalSection(One);
			break;
		}
	}

	return 0;
}

#endif CLASS_H#pragma once
#pragma once
