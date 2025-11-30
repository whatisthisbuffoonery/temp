#include <unistd.h>
#include <dlfcn.h>
#include <malloc.h>

static void		*(*real_malloc)(size_t);
static void		(*real_free)(void *);
static int		count;
static int		freeup;
static int		seg = 1;
//static			*t_malloc_node;

#ifndef SEG
# define SEG 0
#endif

static void	malloc_putnbr(char *c, long n)
{
	char a;
	int t = 1;
	int i = 0;

	while (c[i])
		i ++;
	write(1, c, i);
	if (n < 0)
	{
		n = 0 - n;
		write(1, "-", 1);
	}
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + 48;
		write(1, &a, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

void	*malloc(size_t size)
{
	void *result;

	if (!real_malloc)
		real_malloc = dlsym(RTLD_NEXT, "malloc");//I got to see ls segfault itself in shell

	if (real_malloc)
		count ++;

	if (SEG && count == seg)
	{
		count = 0;
		seg ++;
		return (NULL);//please oh please do not walk around with this in shell
	}

	result = real_malloc(size);

//	if (result)
//		add_node(size, );

	return (result);
}

void	free(void *ptr)
{
	if (!real_free)
		real_free = dlsym(RTLD_NEXT, "free");

	if (ptr)
		freeup ++;

	if (real_free)
		real_free(ptr);
}

static void	init_hook(void) __attribute__((constructor(101)));	//the 101 is redundant here, lower prios first
																//glibc has 0-100 reserved, dont touch those
																//also the extra prototype next to the definition
																//is a doozy
static void	init_hook(void)
{
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	real_free = dlsym(RTLD_NEXT, "free");
}

static void cleanup_hook(void) __attribute__((destructor));		//also takes prio number, higher number first
static void cleanup_hook(void)
{
	malloc_putnbr("count :", count);
	malloc_putnbr("leaks :", count - freeup);
}
