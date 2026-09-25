#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
	DIR	*thing;
	struct dirent	*thingy;

	thing = opendir("./");
	while (1)
	{
		thingy = readdir(thing);
		if (!thingy)
		{
			closedir(thing);
			return (0);
		}
		if (strcmp(thingy->d_name, ".") && strcmp(thingy->d_name, ".."))
			printf("%s\n", thingy->d_name);
	}
}
