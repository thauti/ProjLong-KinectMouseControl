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
void clicgauche()
{	
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	

	INPUT in;
	POINT p;
	in.type = INPUT_MOUSE;
	in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	in.mi.time = 0;
	SendInput(1,&in, sizeof(in));
	in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &in, sizeof(in));

};
void clicgauche_grab()
{

	INPUT in;
	POINT p;
	in.type = INPUT_MOUSE;
	in.mi.time = 0;
	in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &in, sizeof(in));
}
void clicgauche_relache()
{
	INPUT in;
	POINT p;
	in.type = INPUT_MOUSE;
	in.mi.time = 0;
	in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &in, sizeof(in));
	cout << "On relache" << endl;
}
void clicdroite()
{
	cout << "Clic" << endl;
	cout << "Clic" << endl;
	

	INPUT in;
	POINT p;
	GetCursorPos(&p);
	in.type = INPUT_MOUSE;
	in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	in.mi.time = 0;
	SendInput(1, &in, sizeof(in));
	in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &in, sizeof(in));

};