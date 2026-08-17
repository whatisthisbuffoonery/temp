//#include <iostream>
#include <unistd.h>

// using cout inits 70kb of heap
int	main(void)
{
	write(1, "bruh\n", 5);
//	std::cout << "bruh" << std::endl;
}
