#pragma once
class Utils
{
public:
	Utils();
	static double kinectXtoperc(double i);
	static double kinectYtoperc(double i);
	static double kinectXtoZero(double i);
	static double kinectYtoZero(double i);
	static double kinectXtopercScreen(double i, double x1, double x2);
	static double  kinectYtopercScreen(double i, double y1, double y2);
};

