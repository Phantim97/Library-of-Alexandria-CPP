//
// Created by Timothy Coelho on 9/15/24.
//

#ifndef SCRATCH_GENERATOR_H
#define SCRATCH_GENERATOR_H

class Generator
{
public:
	virtual void generate() = 0;
	virtual ~Generator() = default;
};

#endif //SCRATCH_GENERATOR_H
