#include "rt.h"

t_color	apply_reflection_and_tansparency(t_ray *ray, t_object *object, size_t size, float t)
{
	t_hit_info	hit;
	t_ray		r;
	size_t		i;
	t_who		hit_max;

	r.origin = vec3_add(ray->origin, vec3_multv(ray->direction, t));
	r.direction = refraction();
	i = 0;
	while (i < size)
	{
		r.origin = vec3_add(ray->origin, vec3_multv(ray->direction, hit->t));
		r.direction = refraction(hit->n, ray->direction, );
		r.origin = vec3_sub(r.origin, objects[i]->pos);
		r.origin = vec3_rotate(r.origin, vec3_multv(objects[i]->rot, -1));
		r.direction = vec3_rotate(r.direction, vec3_multv(objects[i]->rot, -1));
		object_type(objects[i], &r, &hit);
		if (hit.t > 0 && hit.t < t_max.hit.t)
		{
			hit.n = vec3_rotate(hit.n, objects[i]->rot);
			t_max.hit = hit;
			t_max.i = i;
		}
		i++;
	}
}

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

