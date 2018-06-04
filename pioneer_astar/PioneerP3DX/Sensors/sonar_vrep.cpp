//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#include "sonar_vrep.h"

#include <iostream>

extern "C"
{
#include <remoteApi/extApi.h>
#include <include/v_repConst.h>
}

#include "../Knowledge/pioneer_p_3_dx_model.h"

SonarVREP::SonarVREP(const std::string &name_, RobotModel robot_) : Range(name_), connection(
				const_cast<Connection &>(((PioneerP3DXModel &) robot_).getConnection())), robot(const_cast<RobotModel &>(robot_))
{
	if (simxGetObjectHandle(connection.getClientId(), (const simxChar *) name.c_str(), (simxInt *) &handle,
													(simxInt) simx_opmode_oneshot_wait) == simx_return_ok)
	{
		simxReadProximitySensor(connection.getClientId(), handle, NULL, NULL, NULL, NULL, simx_opmode_streaming);
		std::cout << "Connected to sensor " << name << " Handle: " << handle << std::endl;
	}
	else
	{
		std::cout << "Not connected to sensor " << name << std::endl;
	}
}

bool SonarVREP::getData(Position &position)
{
	char state;
	float point[3];
	if (simxReadProximitySensor(connection.getClientId(), handle, (simxUChar *) &state, point,
															nullptr, nullptr, simx_opmode_buffer) == simx_return_ok)
	{
		position.setPosition((double) point[0], (double) point[1], (double) point[2]);
		return true;
	}
	return false;
}