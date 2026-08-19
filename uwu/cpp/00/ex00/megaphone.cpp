#include <iostream>
#include <cctype>

int	main(int c, char **v)
{
	int	i;
	int	k;

	if (c < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	k = 1;
	while (v[k])
	{
		i = 0;
		while (v[k][i])
		{
			v[k][i] = std::toupper(v[k][i]);
			i ++;
		}
		std::cout << v[k++];
	}
	std::cout << std::endl;
}
