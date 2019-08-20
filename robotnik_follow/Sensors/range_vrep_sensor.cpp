//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#include "range_vrep_sensor.h"
#include "../Knowledge/robotnik_model.h"

#include <iostream>

extern "C"
{
#include <include/v_repConst.h>
}


RangeVREPSensor::RangeVREPSensor(const std::string &name_, Connection &connection_)
	:Range(name_), handle(-1), connection(connection_)
{
	while (handle == -1)
	{
		if (simxGetObjectHandle(connection.getClientId(), (const simxChar *) name.c_str(), (simxInt *) &handle,
		                        (simxInt) simx_opmode_oneshot_wait) == simx_return_ok)
		{
			simxReadProximitySensor(connection.getClientId(), handle, nullptr, nullptr, nullptr, nullptr,
			                        simx_opmode_streaming);
			std::cout << "Connected to sensor " << name << " Handle: " << handle << std::endl;
		}
		else
		{
			std::cout << "Not connected to sensor " << name << std::endl;
		}
	}


}


bool RangeVREPSensor::getData(Position &position)
{
	float point[3];
	char state;
	if ((simxReadProximitySensor(connection.getClientId(), handle, (simxUChar *) &state, point, nullptr, nullptr,
	                             simx_opmode_buffer) == simx_return_ok) && (state > 0))
	{
		position.setPosition((double) point[0], (double) point[1], (double) point[2], (bool) state);
		return true;
	}
//	std::cout << point[0] << point[1]<< point[2]<< std::endl;
	return false;
}

//bool RangeVREPSensor::getData(Position &position, char &state)
//{
//	float point[3];
//	if (simxReadProximitySensor(connection.getClientId(), handle, (simxUChar *) &state, point,
//															nullptr, nullptr, simx_opmode_buffer) == simx_return_ok)
//	{
//		position.setPosition((double) point[0], (double) point[1], (double) point[2]);
////		std::cout << position << std::endl;
//		return true;
//	}
////	std::cout << point[0] << point[1]<< point[2]<< std::endl;
//	return false;
//}

int RangeVREPSensor::getHandle() const
{
	return handle;
}
