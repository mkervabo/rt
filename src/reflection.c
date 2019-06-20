#include "rt.h"

t_vec3	reflection(t_vec3 direction, t_vec3 normal)
{
	t_vec3 ref;
	
	ref = vec3_dot(direction, normal)
	ref = vec3_add(vec3_mult(-2 * ref, normal), direction);
	return (ref);
}

t_vec3	refraction(double n, t_vec3 direction, t_vec3 normal)
{
	double	cosi;
	double	sini;
	t_vec3	ref;

	cosi = vec3_dot(direction, normal)
	sini = (1 / n) * (1 / n) * (1 - cosi * cosi) //considere d'origine qu'on et dans l'air donc indice = 1
	ref = vec3_multv(direction, (1 / n)) - vec3_multv(normal, (cosi * (1 / n) + sqrt(1 - sini)))
	return (ref);
}

