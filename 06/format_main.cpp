#include "format.h"



int main()
{
	assert(format("{0} + {0} = {1}", "one", 2) == "one + one = 2");

	assert(format("{3} + {2} + {1} + {0} = {4}", 3, 2, 1, 0, 6) == "0 + 1 + 2 + 3 = 6");

	try 
	{
		auto err = format("{}", 1);
	}
	catch(runtime_error)
	{
		assert(true);
	}
}