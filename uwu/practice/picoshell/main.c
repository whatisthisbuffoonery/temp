#include <stdio.h>
#include <unistd.h>

int	picoshell(char **cmds[]);

int	main(void)
{
    char *cmd1[] = {"echo", "squalala", NULL};
    char *cmd2[] = {"/bin/cat", NULL};
    char *cmd3[] = {"/usr/bin/sed", "s/a/b/g", NULL};
    char **cmds[] = {cmd1, cmd2, cmd3, NULL};

    int result = picoshell(cmds);
    printf("picoshell returned %d\n", result);
//	printf("test exec:\n");
//	execvp(*cmd1, cmd1);

    return 0;
}
