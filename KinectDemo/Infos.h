#pragma once
class Infos
{
public:
	int xhand;
	int yhand;
	bool calibration;
	Infos() {
		calibration = false;
		xhand = 0;
		yhand = 0;
	};
	int getxhand();
	int getyhand();
	bool getCalibration();
	void setCalibration(bool v);

};

