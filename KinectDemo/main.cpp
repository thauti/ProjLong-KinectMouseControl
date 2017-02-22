#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <NuiApi.h>
#include "Utils.h"

using namespace std;



void calibrationMouvement(NUI_SKELETON_FRAME sframe, double **positions) {
	
	sf::SoundBuffer buffer;
	sf::Sound notif;
	
	buffer.loadFromFile("son.wav");
	notif.setBuffer(buffer);
	notif.play();
	notif.play();
	double tmpX, tmpY, tmpZ;
	int check =0;
	bool cal1 = false, cal2 = false;
	cout << "Debut calibration" << endl;
	Sleep(2000);
	for (int i = 0; i < 2; i++) {
		NuiSkeletonGetNextFrame(0, &sframe);

		positions[i] = new double[3];
		for (int k = 0; k < 6; k++)
		{
			if (sframe.SkeletonData[k].eTrackingState == NUI_SKELETON_TRACKED) {
				tmpX = sframe.SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x;
				tmpY = sframe.SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y;
				tmpZ = sframe.SkeletonData[k].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].z;
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
		calibrationMouvement(sframe, positions);
	}
	else {
		notif.play();
		notif.play();
	}
}

int main()
{
	POINT curs;
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape shape(5.f);
	window.setFramerateLimit(60);
	shape.setFillColor(sf::Color::Green);

	int hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	NUI_SKELETON_FRAME sframe;


	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	bool calibration = false;
	double **positions = new double*[2];
	double posX, posY;
	sf::Event event;
	while (1)
	{

		NuiSkeletonGetNextFrame(0, &sframe);
		if (!calibration) {
			calibrationMouvement(sframe, positions);
			calibration = true;
		}
		for (int i = 0; i < 6; i++)
		{
			if (sframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			{
				shape.setPosition(Utils::kinectXtoperc(sframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x) * h,
					Utils::kinectYtoperc(sframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y) * w);


				posX = Utils::kinectXtopercScreen(sframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x, Utils::kinectXtoZero(positions[0][0]), Utils::kinectXtoZero(positions[1][0]))*w;
				posY = Utils::kinectYtopercScreen(sframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y, Utils::kinectYtoZero(positions[0][1]), Utils::kinectYtoZero(positions[1][1]))*h;

				SetCursorPos(posX, posY);
			}
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				exit(1);
			}
		}


		window.clear();
		window.draw(shape);
		window.display();
	}
	/*
	*/
	NuiShutdown();

	return 0;
}