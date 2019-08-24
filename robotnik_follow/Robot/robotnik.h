//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#ifndef PIONEER_PIONEER_P3DX_H
#define PIONEER_PIONEER_P3DX_H


#include <Robot/robot.h>
#include "../Analyze/pass_robotnik_position.h"
#include "../Knowledge/robotnik_knowledge.h"
#include "../Actuators/wheel_vrep.h"

#include "../Sensors/P3DXPositionSensor.h"
#include "../Sensors/orientation_vrep_sensor.h"
#include "../Sensors/position_vrep_sensor.h"

#include "../Monitor/P3DXPositionMonitor.h"
#include "../Monitor/range_vrep_monitor.h"
#include "../Monitor/position_vrep_monitor.h"
#include "../Monitor/orientation_vrep_monitor.h"
#include "../Analyze/pass_vrep_range.h"
#include "../Analyze/pass_vrep_position.h"
#include "../Analyze/pass_vrep_orientation.h"
#include "../Plan/go_to_p3dx_planner.h"
#include "../Visualizer/file_visualizer.h"


class Robotnik : public Robot
{
private:
	RobotnikKnowledge knowledge;

	Connection &connection;

	//	SENSORS
	std::vector<RangeVREPSensor> range_sensors;
	OrientationVREPSensor orientation_sensor;
	PositionVREPSensor position_sensor;
	PositionVREPSensor p3dx_position_sensor;

	//	ACTUATORS
	std::vector<WheelVREP> wheels;
	std::vector<Actuator *> wheel_ptrs;


	//	MONITORS
	RangeVREPMonitor range_monitor;
	PositionVREPMonitor position_monitor;
	OrientationVREPMonitor orientation_monitor;
	PositionVREPMonitor p3dx_position_monitor;

	//	ANALYZES
	PassVREPRange range_analyze;
	PassVREPPosition position_analyze;
	PassVREPOrientation orientation_analyze;
	PassRobotnikPosition p3dx_position_analyze;

	//  PLANNER
	GoToP3DXPlanner planner;

	FileVisualizer file_visualizer;

	std::chrono::seconds lifetime;


private:

	void verifyConnection();

	void setSensors();

	void setActuators();

	void setMonitors();

	void setAnalyzes();

	void setPlan();

	void setExecute();

	void setVisualizers();

	void setReactiveModels();

	void setKnowledge();

	void connectToProximitySensors();

	void connectToOrientationSensor();

	void connectToPositionSensor();

	void connectToP3DXPositionSensor();

	void connectToWheels();


public:
	Robotnik();

	void run();

};


#endif //PIONEER_PIONEER_P_3_DX_H
