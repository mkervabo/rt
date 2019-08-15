#include "math/utils.h"

void		scale(double *a, double *b, double max)
{
	double		total;

	total = *a + *b;
	if (total)
	{
		*a *= max / total;
		*b *= max / total;
	}
}


double	clamp(double value, double from, double to)
{
       if (value > to)
               return (to);
       else if (value < from)
               return (from);
       else
               return (value);
}

void		dswap(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}
