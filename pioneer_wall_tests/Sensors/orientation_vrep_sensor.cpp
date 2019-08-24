//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#include <include/v_repConst.h>
#include <remoteApi/extApi.h>
#include <iostream>
#include <thread>
#include "orientation_vrep_sensor.h"
#include "../Knowledge/pioneer_p3dx_model.h"

OrientationVREPSensor::OrientationVREPSensor(Connection &connection_)
	:Sensor("OrientationSensor"), connection(connection_), handle(connection_.getRobotHandle())
{
}

void OrientationVREPSensor::connect(int handle_)
{
	handle = handle_;
	float angle[3] = {0, 0, 0};

	simxGetObjectOrientation(connection.getClientId(), handle, -1, angle, simx_opmode_streaming);
	while (simxGetObjectOrientation(connection.getClientId(), handle, -1, angle, simx_opmode_buffer) != simx_return_ok)
	{
//		std::cout << "Waiting to connect to " << name << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	std::cout << "Connected to " << name << "\n";
}

bool OrientationVREPSensor::getData(Orientation &value)
{
	float angle[3];
	if (simx_return_ok == simxGetObjectOrientation(connection.getClientId(), handle, -1, angle, simx_opmode_buffer))
	{
//		std::cout << "GetDataOrientation: " << angle[0] << " " <<  angle[1]<< " " <<  angle[2] <<std::endl;
		value.setOrientation(angle[0], angle[1], angle[2]);
		return true;
	}
	value.setValid(false);
	return false;
}


