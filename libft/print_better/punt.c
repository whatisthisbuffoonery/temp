#include <stdio.h>
// + ' ' - 0 #
// + > ' '
// - > 0
// 0 and ' ' can go together

// + force a + or - sign for numbers
// ' ' use a space instead of +
// - left justify. uses width. trailing spaces.
// 0 pad leading zeros (width normally pads spaces)
// # obviously sits next to the type char

// width: leading padding (minimum length format)
// precision: leading 0s for %d and %i. eats space out of width

// syntax: flags --> width --> precision --> type

int main(void)
{
	printf("%8ca\n", 0);
}
