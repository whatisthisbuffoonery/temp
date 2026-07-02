#include <unistd.h>

typedef struct s_stack
{
	int arr[5];
	int top;
	int bottom;
	int size;
}		stack;

void init(stack *dst)
{
	dst->size = 5;
	dst->top = 4;
	dst->bottom = 0;
}

int main(void)
{
	char buf[32];
	int lim;
	stack a = {.arr = {1, 2, 3, 4, 5}};
	stack b = {.arr = {6, 7, 8, 9, 10}};
	init(&a);
	init(&b);

	write(1, "use push swap instructions, or type \'show\'\n", 43);
	while (1)
	{
		lim = read(0, buf, 32);
		if (lim < 0)
			return (0);
		else if (lim > 5)
		{
			write(2, "instruction too long\n", 22);
			continue ;
		}
		buf[lim] = '\0';
		run_buffer(&a, &b, buf);
	}
}
