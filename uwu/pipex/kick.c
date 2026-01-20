#include <unistd.h>

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	if (access(v[1], X_OK))
		write(1, "boi\n", 4);
}
