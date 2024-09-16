//
// Created by Timothy Coelho on 9/15/24.
//

#ifndef SCRATCH_ENGINECHILDREN_H
#define SCRATCH_ENGINECHILDREN_H

#include "Engine.h"
#include <iostream>

class EngineA : public Engine
{
public:
	void run() override
	{
		test();
	}

	void test()
	{
		std::cout << "Engine is running\n";
	}
};

class EngineB : public Engine
{
public:
	void run() override
	{
		test();
	}

	void test()
	{
		std::cout << "Engine is starting\n";
	}
};

#endif //SCRATCH_ENGINECHILDREN_H
