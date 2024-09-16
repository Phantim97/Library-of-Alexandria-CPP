#include "Context.h"

int main()
{
	Strategy<EngineA, GeneratorB>::execute();
	Context::execute_strategy<EngineA, GeneratorB>();

	return 0;
}

