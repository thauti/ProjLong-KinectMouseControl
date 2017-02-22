#pragma once
#ifndef H_KINECT
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <NuiApi.h>
#define H_KINECT
#endif
#ifndef H_INFOS
#include "Infos.h"
#define H_INFOS
#endif
class Calibration
{
public:
	static void calibrationMouvement(NUI_SKELETON_FRAME* sframe, double **positions, Infos* env);
};

