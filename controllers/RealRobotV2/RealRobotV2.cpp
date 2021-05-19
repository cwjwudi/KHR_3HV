#include <webots/Robot.hpp>


#include <iostream>
#include <string>
#include "WzSerialPort.h"
#include "StrToHex.h"
#include "RobotCtrl.h"
#include "symbol.h"



using namespace webots;


char* strHex = "09001202000000001D";	//测试用电机数据



int main(int argc, char **argv) {
	Robot *robot = new Robot();

	int timeStep = (int)robot->getBasicTimeStep();

	std::cout << timeStep;

	WzSerialPort w;
	
	if (w.open("COM3", 1250000, 2, 8, 1)) {
		std::cout << "send data finished..." << std::endl;
		w.isSerialOpen = 1;
	}
	float pout = 0;
	int i = 0;
	int count = 0;
	while (robot->step(timeStep) != -1) {	
		SendMotorCtrl2(&w, 0x00, pout);
		std::cout << pout << std::endl;
		pout = 100 * sin(count  * PI / 1000);
		count += 64;
};
	delete robot;
	return 0;
}
