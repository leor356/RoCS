//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#ifndef ARCH_RANGE_H_
#define ARCH_RANGE_H_

#include <ostream>
#include "sensor.h"

template<typename Value>
class Range : public Sensor<Value>
{
protected:
	double max_range;
	double resolution;
	double fov_angle;
	double beam_angle;
	double scan_interval;

public:
	Range(std::string name_, double weight_, Position position_, double bandwidth_, double max_range_, double resolution_,
	      double fov_angle_, double beam_angle_, double scan_interval_):
		Sensor<Value>(name_, weight_, position_, bandwidth_)
	{
		max_range = max_range_;
		resolution = resolution_;
		fov_angle = fov_angle_;
		beam_angle = beam_angle_;
		scan_interval = scan_interval_;
	}

	Range(std::string name_):Sensor<Value>(name_), max_range{0}, resolution{0}, fov_angle{0}, beam_angle{0},
	                         scan_interval{0}
	{
	}

	friend std::ostream &operator<<(std::ostream &os, const Range<Value> &range)
	{
		os << static_cast<const Sensor<Value> &>(range) << " Max_range: " << range.max_range << " Resolution: "
		   << range.resolution
		   << " Fov_angle: " << range.fov_angle << " Beam_angle: " << range.beam_angle << " Scan_interval: "
		   << range.scan_interval << " ";
		return os;
	}

};

#endif //ARCH_RANGE_H_
