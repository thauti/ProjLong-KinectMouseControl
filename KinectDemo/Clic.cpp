#ifndef H_KINECT
#include <stdlib.h>

#include <windows.h>
#include <winuser.h>
#include <NuiApi.h>
#define H_KINECT
#endif
#include <iostream>
#include "Clic.h"
using namespace std;
void *clicthread()
{
	Sleep(3000);

	
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	cout << "Clic" << endl;

	INPUT in;
	POINT p;
	GetCursorPos(&p);
	in.type = INPUT_MOUSE;
	in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	in.mi.time = 0;
	SendInput(1,&in, sizeof(in));
	in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &in, sizeof(in));
	Sleep(200);

	return 0;
};