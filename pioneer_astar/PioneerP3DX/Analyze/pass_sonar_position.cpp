//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#include <remoteApi/extApiPlatform.h>
#include "pass_sonar_position.h"

PassSonarPosition::PassSonarPosition(const RobotModel &robot) : Analyze(robot)
{
}

void PassSonarPosition::publishLoop()
{
	while (publishing)
	{
		publish(value);


//		using namespace std::chrono_literals;
//		std::this_thread::sleep_for(50ms);
		extApi_sleepMs(25);
	}

}

