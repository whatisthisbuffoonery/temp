#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	*run(void *data)
{
	return (data);
}

int	main(void)
{
	int	input;
	int	thing = 123;
	int	*thong = &thing;
	int	i = 0;
	pthread_t	thread;

	while (i < 10)
	{
		input = i;
		pthread_create(&thread, NULL, run, (void *) &input);
		pthread_join(thread, (void **) &thong);
		printf("return value: %d\n", *thong);
		i ++;
	}
}
