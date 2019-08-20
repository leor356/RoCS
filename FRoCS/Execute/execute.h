//
// Laboratory of Robotics and Cognitive Science
// Created by:  Leonardo de Oliveira Ramos
// Github:      https://github.com/oramleo
//

#ifndef ARCH_EXECUTE_H_
#define ARCH_EXECUTE_H_

#include <vector>
#include <thread>

#include <Util/pipeline.h>
#include <Execute/action.h>
#include <Plan/behavior.h>
#include <Knowledge/knowledge.h>

class Execute
{
private:
	Knowledge &knowledge;
	Pipeline pipeline;
	bool running;
	int waiting_time;
	std::thread *execute_thread;

	std::vector<std::vector<Actuator *> > actuators;

public:
	explicit Execute(Knowledge &knowledge_)
		:knowledge(knowledge_), pipeline(), running(true), waiting_time(50), execute_thread(nullptr), actuators()
	{
	}

	~Execute()
	{
		running = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(waiting_time));
		if (execute_thread && execute_thread->joinable())
			execute_thread->join();
	}

	void startThread()
	{
		execute_thread = new std::thread(&Execute::run, this);
	}

	void run()
	{
		while (running)
		{
			std::shared_ptr<Action> action(nullptr);
			if (pipeline.next(&action) && action)
			{
				action->setActuators(actuators);
//				std::cout << "Act! " << *action << "\n";
				action->act();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(waiting_time));
		}
	}

	void setActuators(const std::vector<std::vector<Actuator *> > &actuators)
	{
		Execute::actuators = actuators;
	}

	Pipeline &getPipeline()
	{
		return pipeline;
	}
};

#endif //ARCH_EXECUTE_H_