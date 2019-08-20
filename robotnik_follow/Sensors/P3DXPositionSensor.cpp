//
// Created by leleco on 06/07/19.
//

#include "P3DXPositionSensor.h"


//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#include <thread>
#include <iostream>
#include <include/v_repConst.h>
#include "position_vrep_sensor.h"
#include "../Knowledge/robotnik_model.h"
#include "../Knowledge/robotnik_knowledge.h"

P3DXPositionSensor::P3DXPositionSensor(Connection &connection_)
        :Sensor("PositionSensor"), connection(connection_), handle(connection_.getRobotHandle())
{
}

void P3DXPositionSensor::connect(int handle_)
{
    handle = handle_;
    float position[3] = {0, 0, 0};

    simxGetObjectPosition(connection.getClientId(), handle, -1, position, simx_opmode_streaming);
    while (simxGetObjectPosition(connection.getClientId(), handle, -1, position, simx_opmode_buffer) != simx_return_ok)
    {
//		std::cout << "Waiting to connect to " << name << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    float pos[3] = {0};
    simxGetObjectPosition(connection.getClientId(), handle, -1, pos, simx_opmode_buffer);

    std::cout << "Connected to " << name << std::endl;

}

bool P3DXPositionSensor::getData(Position &value)
{
    float pos[3];
    if (simx_return_ok == simxGetObjectPosition(connection.getClientId(), handle, -1, pos, simx_opmode_buffer))
    {
//		std::cout << "GetDataPosition: " << pos[0] << " " <<  pos[1]<< " " <<  pos[2] <<std::endl;
        value.setPosition(pos[0], pos[1], pos[2]);
        return true;
    }
//	std::cout << "nao deu \n";
    return false;
}
