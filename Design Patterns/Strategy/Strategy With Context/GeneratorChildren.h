//
// Created by Timothy Coelho on 9/15/24.
//

#ifndef SCRATCH_GENERATORCHILDREN_H
#define SCRATCH_GENERATORCHILDREN_H

#include "Generator.h"
#include <iostream>

class GeneratorA : public Generator
{
public:
	void generate() override
	{
		doSomething();
	}

	void doSomething()
	{
		std::cout << "something\n";
	}
};

class GeneratorB : public Generator
{
public:
	void generate() override
	{
		doSomethingElse();
	}

	void doSomethingElse()
	{
		std::cout << "something\n";
	}
};


#endif //SCRATCH_GENERATORCHILDREN_H
