#ifndef H_INFOS
#include "Infos.h"
#define H_INFOS
#endif

int Infos::getxhand()
{
	return xhand;
}
int Infos::getyhand()
{
	return yhand;
}
bool Infos::getCalibration()
{
	return calibration;
}
void Infos::setCalibration(bool v)
{
	calibration = v;
}