//
// Created by Timothy Coelho on 9/15/24.
//

#ifndef SCRATCH_CONTEXT_H
#define SCRATCH_CONTEXT_H

#include "Strategy.h"

class Context
{
public:
	template <typename E, typename G>
	static void execute_strategy()
	{
		Strategy<E, G> strategy;
		strategy.execute();
	}
};
#endif //SCRATCH_CONTEXT_H
