#include <iostream>
#include <cctype>

int	main(int c, char **v)
{
	int	i;
	int	k;

	(void) c;
	k = 1;
	while (v[k])
	{
		i = 0;
		while (v[k][i])
		{
			v[k][i] = std::toupper(v[k][i]);
			i ++;
		}
		k ++;
	}
	if (k == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		k = 1;
		while (v[k])
		{
			std::cout << v[k];
			if (v[k + 1])
				std::cout << " ";
			k ++;
		}
		std::cout << std::endl;
	}
}
