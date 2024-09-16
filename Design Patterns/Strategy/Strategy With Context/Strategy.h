//
// Created by Timothy Coelho on 9/14/24.
//

#ifndef SCRATCH_STRATEGY_H
#define SCRATCH_STRATEGY_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

#include "GeneratorChildren.h"
#include "EngineChildren.h"

template <typename E, typename G>
class Strategy
{
public:
	static void execute()
	{
		E engine;
		G gen;

		//Execute
		engine.run();
		gen.generate();
	}
};


#endif //SCRATCH_STRATEGY_H
