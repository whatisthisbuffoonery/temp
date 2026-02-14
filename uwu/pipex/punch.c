#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
	printf("%d\n", SIGSEGV);
	printf("%d\n", SIGINT);
	printf("%d\n", SIGTERM);
	printf("%d\n", SIGKILL);
	printf("%d\n", SIGQUIT);
	printf("%d\n", SIGILL);
	printf("%d\n", SIGABRT);
	printf("%d\n", SIGFPE);
	printf("%d\n", SIGBUS);
	printf("%d\n", SIGPIPE);
	printf("%d\n", SIGALRM);

	printf("%s\n", strsignal(SIGSEGV));
	printf("%s\n", strsignal(SIGINT));
	printf("%s\n", strsignal(SIGTERM));
	printf("%s\n", strsignal(SIGKILL));
	printf("%s\n", strsignal(SIGQUIT));
	printf("%s\n", strsignal(SIGILL));
	printf("%s\n", strsignal(SIGABRT));
	printf("%s\n", strsignal(SIGFPE));
	printf("%s\n", strsignal(SIGBUS));
	printf("%s\n", strsignal(SIGPIPE));
	printf("%s\n", strsignal(SIGALRM));
}
