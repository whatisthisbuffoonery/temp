#include "h_philo.h"

void	timeval_find_max(struct timeval *max, struct timeval *test)//new libft func
{
	test->tv_sec = -1;
	test->tv_usec = -1;
	if (test->tv_sec > 0)
		max->tv_sec = -1;
	else
	{
		max->tv_sec = 1;
		max->tv_sec <<= (sizeof(max->tv_sec) * CHAR_BIT) - 1;
		max->tv_sec = ~max->tv_sec;
	}
	if (test->tv_usec > 0)
		max->tv_usec = -1;
	else
	{
		max->tv_usec = 1;
		max->tv_usec <<= (sizeof(max->tv_usec) * CHAR_BIT) - 1;
		max->tv_usec = ~max->tv_usec;
	}
}

int	timeval_diff(struct timeval src1, struct timeval src2)
{
	static _Thread_local struct timeval	curr;
	static _Thread_local struct timeval	test;
	static _Thread_local struct timeval max;
	static _Thread_local int			carry;

	curr.tv_usec = src1.tv_usec - src2.tv_usec;
	carry = (src1.tv_usec < src2.tv_usec);
	curr.tv_sec = (src1.tv_sec - src2.tv_sec) - carry;
	if (!test.tv_sec)
		timeval_find_max(&max, &test);
	if (carry)
		curr.tv_usec += (1000 * 1000) + 1;
	if (src1.tv_sec < src2.tv_sec)
		curr.tv_sec += (max.tv_sec) + (1 - carry);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

int	timeval_diff_atomic(struct timeval src1, _Atomic struct timeval src2)
{
	static _Thread_local struct timeval	input;

	input = src2;
	return (timeval_diff(src1, input));
}
