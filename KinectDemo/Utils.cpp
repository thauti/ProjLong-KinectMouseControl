#ifndef H_UTILS
#include "Utils.h"
#define H_UTILS
#endif


Utils::Utils()
{
}
double Utils::kinectXtoperc(double i)
{
	return (2.2 + i) / 4.4;
}
double  Utils::kinectYtoperc(double i)
{
	return 1 - (1.6 + i) / 3.2;
}

double Utils::kinectXtoZero(double i)
{
	return i + 2.2;
}
double Utils::kinectYtoZero(double i)
{
	return i + 1.6;
}
double Utils::kinectXtopercScreen(double i, double x1, double x2)
{
	double minx, maxx;
	if (x1 > x2) {
		minx = x2;
		maxx = x1;
	}
	else
	{
		minx = x1;
		maxx = x2;
	}
	return (Utils::kinectXtoZero(i) - minx) / (maxx - minx);
}
double Utils::kinectYtopercScreen(double i, double y1, double y2)
{
	double miny, maxy;

	if (y1 > y2) {
		miny = y2;
		maxy = y1;
	}
	else
	{
		miny = y1;
		maxy = y2;
	}
	return 1 - (Utils::kinectYtoZero(i) - miny) / (maxy - miny);
}