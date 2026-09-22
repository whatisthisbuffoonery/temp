#include "sed.h"

void	sed(std::ifstream &in, std::ofstream &out, char *s1, char *s2)
{
	char	cmp;
	int		i;
	int		lim;

	lim = std::string(s1).length();
	i = 0;
	while (in.get(cmp))
	{
		if (lim > 0 && cmp == s1[i])
			i ++;
		else
		{
			out.write(s1, i);
			out << cmp;
			i = 0;
		}
		if (i >= lim)
		{
			out << s2;
			i = 0;
		}
	}
}

int	main(int c, char **v)
{
	if (c != 4)
		return (1);
	std::ifstream	infile(v[1]);
	if (!infile.is_open())
		return (1);
	std::string	outfilename(std::string(v[1]) + ".replace");
	std::ofstream	outfile(outfilename.c_str());
	if (!outfile.is_open())
	{
		infile.close();
		return (1);
	}
	sed(infile, outfile, v[2], v[3]);
	infile.close();
	outfile.close();
}
