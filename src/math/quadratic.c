#include "math/quadratic.h"
#include <math.h>

bool	solve_quadratic(struct s_quadratic fn, double *min, double *max)
{
	double	delta;
	double	p1;
	double	p2;

	delta = fn.b * fn.b - 4 * fn.a * fn.c;
	if (delta >= 0)
	{
		delta = sqrt(delta);
		p1 = (-fn.b - delta) / (2.0 * fn.a);
		p2 = (-fn.b + delta) / (2.0 * fn.a);
		*min = fmin(p1, p2);
		*max = fmax(p1, p2);
		return (true);
	}
	else
		return (false);
}
