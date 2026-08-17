#include <iostream>

int	main(void)
{
	int	i = 0;
	int	&ref = i;

	ref = 5;
	std::cout << "i is: " << i << std::endl;

	int	k = 8;
	ref = k;
	std::cout << "you updated 'i' you fool: " << i << std::endl;

	std::cout << "meant to stand in as the var it is pointing to: " << ref << std::endl;
	// doesnt compile: std::cout << "ref test 2: " << *ref << std::endl;
	// its just there to dodge copy on write for param passing, returns
}
