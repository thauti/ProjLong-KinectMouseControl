#ifndef H_CALIBRATION
#include "Calibration.h"
#define H_CALIBRATION
#endif

#include <stdlib.h>
#include <iostream>

#ifndef H_SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#define H_SFML
#endif
#ifndef H_KINECT
#include <windows.h>
#include <winuser.h>
#include <NuiApi.h>
#define H_KINECT
#endif


#ifndef H_INFOS
#include "Infos.h"
#define H_INFOS
#endif

using namespace std;

void Calibration::calibrationMouvement(NUI_SKELETON_FRAME* sframe, double **positions, Infos* env) {
	
	sf::SoundBuffer buffer;
	sf::Sound notif;
	NuiSkeletonGetNextFrame(0, sframe);

	buffer.loadFromFile("son.wav");
	notif.setBuffer(buffer);
	notif.play();
	notif.play();
	double tmpX, tmpY, tmpZ;
	int check = 0;
	bool cal1 = false, cal2 = false;
	cout << "Debut calibration" << endl;
	Sleep(2000);
	for (int i = 0; i < 2; i++) {
		NuiSkeletonGetNextFrame(0, sframe);

		positions[i] = new double[3];
		for (int k = 0; k < 6; k++)
		{
			if (sframe->SkeletonData[k].eTrackingState == NUI_SKELETON_TRACKED) {
				tmpX = sframe->SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x;
				tmpY = sframe->SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y;
				tmpZ = sframe->SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].z;
				cout << "Calibration " << i << " : " << tmpX << tmpY << endl;
				positions[i][0] = tmpX;
				positions[i][1] = tmpY;
				positions[i][2] = tmpZ;
				if (i == 0) {
					cal1 = true;
				}
				else if (i == 1) {
					cal2 = true;
				}
			}
			else {
				cout << "skeleton not found" << endl;
			}

		}
		notif.play();
		Sleep(2000);
	}
	if (!cal1 || !cal2) { // Si la calibration échoue on la refait
		calibrationMouvement(sframe, positions, env);
	}
	else {
		notif.play();
		notif.play();
		env->setCalibration(true);
	}
};

