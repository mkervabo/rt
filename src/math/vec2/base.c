#include <math.h>
#include "math/vec2.h"
#include "debug/assert.h"

t_vec2	vec2(double x, double y)
{
	assertf(x != NAN && y != NAN, "NAN in vec2(%f, %f)", x, y);

	return ((struct s_vec2) {
		.x = x,
		.y = y
	});
}

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x + b.x,
		a.y + b.y
	));
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x - b.x,
		a.y - b.y
	));
}

t_vec2	vec2_mult(t_vec2 a, t_vec2 b)
{
	return (vec2(
		a.x * b.x,
		a.y * b.y
	));
}

