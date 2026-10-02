/*
	const binds to thing on the left:
		int
		*
	unless its on the left edge
		const int
	so 'a' will never compile
	also int goes on the left edge usually, compiler not that smort
*/
int	main(void)
{
	const int const a;
	*const int const b;
	**int	c;
}
