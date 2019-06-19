#include "rt.h"

t_vec3	reflection(t_vec3 direction, t_vec3 normal)
{
	t_vec3 ref;
	
	ref = vec3_mult(direction, normal)
	ref = vect3_add(vec3_mult(vec3_multv(ref, -2), normal), direction);
	return (ref);
}

