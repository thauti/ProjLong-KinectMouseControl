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
#include "Clic.h"

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

	thread *click_t = NULL;

	NUI_TRANSFORM_SMOOTH_PARAMETERS defaultParams =
	{ 1.0f, 0.1f, 1.0f, 1.0f, 1.0f };

	sf::Time* t1 = new sf::Time();
	sf::Clock* c = new sf::Clock();
	int lock_opti = 0;
	int lock_opti2 = 0;
	int clicprolonge = 0;
	while (1)
	{


		if (env->getCalibration() == false && calibrationEncours == false) {
			cout << "D�but de la calibration" << endl;
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
			NuiTransformSmooth(sframe, &defaultParams);
			for (int i = 0; i < 6; i++)
			{
				if (sframe->SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
				{
					shape.setPosition(Utils::kinectXtoperc(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x) * h,
						Utils::kinectYtoperc(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y) * w);


					posX = Utils::kinectXtopercScreen(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x, Utils::kinectXtoZero(positions[0][0]), Utils::kinectXtoZero(positions[1][0]))*w;
					posY = Utils::kinectYtopercScreen(sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y, Utils::kinectYtoZero(positions[0][1]), Utils::kinectYtoZero(positions[1][1]))*h;
					if (positions[0][2] - sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].z >0.3)
					{
						if (clicprolonge != 1) {
							if (lock_opti == 0)
							{
								lock_opti = 1;

								c->restart();
							}
							else
							{

								*t1 = c->getElapsedTime();
							///	cout << t1->asSeconds() << endl;
								if (t1->asSeconds() >= 2.f)
								{
									clicgauche();
									c->restart();
									lock_opti = 0;
									clicprolonge = 1;
								}
							}
						}
						else
						{
							*t1 = c->getElapsedTime();
						//	cout << t1->asSeconds() << endl;
							if (t1->asSeconds() >= 3.f)
							{
								clicgauche_grab();
								c->restart();
								lock_opti = 0;
								clicprolonge = 1;
							}
						}
						
					}
					else if (positions[0][2] - sframe->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].z >0.3)
					{
						if (lock_opti2 == 0)
						{
							lock_opti2 = 1;
							c->restart();
						}
						else
						{
							cout << "Clic ?" << endl;
							*t1 = c->getElapsedTime();
							cout << t1->asSeconds() << endl;
							if (t1->asSeconds() >= 2.f)
							{
								clicdroite();
								c->restart();
								lock_opti2 = 0;
							}
						}
					}
					else
					{
						if (clicprolonge == 1)
						{
							clicgauche_relache();
							clicprolonge = 0;
							lock_opti = 0;
						}
						if (lock_opti != 0)
						{
							lock_opti = 0;
						}
						if (lock_opti2 != 0)
						{
							lock_opti2 = 0;
						}
					}

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