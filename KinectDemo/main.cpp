#include <stdlib.h>
#include <iostream>
#include <thread>
#ifndef H_SFML
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>
#define H_SFML
#endif

#ifndef H_KINECT
#include <stdlib.h>

#include <windows.h>
#include <winuser.h>
#include <NuiApi.h>
	#define H_KINECT
#endif

#ifndef H_UTILS
	#include "Utils.h"
	#define H_UTILS
#endif

#ifndef H_INFOS
	#include "Infos.h"
	#define H_INFOS
#endif

#ifndef H_CALIBRATION
	#include "Calibration.h"
	#define H_CALIBRATION
#endif
using namespace std;

void toto(int a)
{
	cout << "toto" << endl;
}

int main()
{
	POINT curs;
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape shape(5.f);
	window.setFramerateLimit(60);
	shape.setFillColor(sf::Color::Green);

	int hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	NUI_SKELETON_FRAME* sframe = new NUI_SKELETON_FRAME();


	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	bool calibrationEncours = false;
	double **positions = new double*[2];
	double posX, posY;
	sf::Event event;
	sf::Text status;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	status.setFont(font);
	status.setColor(sf::Color::Yellow);
	status.setCharacterSize(24);
	Infos * env = new Infos();


	while (1)
	{


		if (env->getCalibration() == false && calibrationEncours == false) {
			cout << "Début de la calibration" << endl;
			status.setString("Calibration en cours");
			thread t (Calibration::calibrationMouvement, sframe, positions, env);
			t.detach();
			
			calibrationEncours = true;
		}
		if(calibrationEncours) {

			if (env->getCalibration() == true) {
				calibrationEncours = false;
				status.setString("Calibration OK");

			}
		}
		if (!calibrationEncours)
		{
			NuiSkeletonGetNextFrame(0, sframe);

			for (int i = 0; i < 6; i++)
			{
				if (sframe->SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
				{
					shape.setPosition(Utils::kinectXtoperc(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x) * h,
						Utils::kinectYtoperc(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y) * w);


					posX = Utils::kinectXtopercScreen(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x, Utils::kinectXtoZero(positions[0][0]), Utils::kinectXtoZero(positions[1][0]))*w;
					posY = Utils::kinectYtopercScreen(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y, Utils::kinectYtoZero(positions[0][1]), Utils::kinectYtoZero(positions[1][1]))*h;

					SetCursorPos(posX, posY);
				}
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
		window.draw(status);

		window.draw(shape);
		window.display();
	}
	/*
	*/
	NuiShutdown();

	return 0;
}