//
// Created by Timothy Coelho on 6/27/24.
//

#ifndef LIBRARY_OF_ALEXANDRIA_CPP_UTIL_H
#define LIBRARY_OF_ALEXANDRIA_CPP_UTIL_H
inline void ASSERT(bool cond, const std::string& msg) noexcept
{
	if (!cond)
	{
		std::cerr << msg << '\n';
		exit(EXIT_FAILURE);
	}
}

#endif //LIBRARY_OF_ALEXANDRIA_CPP_UTIL_H
