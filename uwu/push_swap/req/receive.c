#include <unistd.h>

int main(int c, char **v)
{
	if (c < 2)
	{
		write(1, "nothing\n", 8);
		return (1);
	}
	write(1, "arg: |", 6);
	write(1, v[1], 1);
	write(1, "|\n", 2);
	char buf[100];
	int i = read(0, buf, 100);
	write(1, "we got : |", 10);
	write(1, buf, i);
	write(1, "|\n", 2);
}
