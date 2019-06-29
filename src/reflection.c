#include "rt.h"


t_vec3	reflection(t_vec3 direction, t_vec3 normal)
{
	t_vec3 ref;
	double i;
	
	i = vec3_dot(direction, normal);
	ref = vec3_add(vec3_multv(normal, -2 * i), direction);
	return (ref);
}

t_vec3	refraction(double n, t_vec3 direction, t_vec3 normal)
{
	double	cosi;
	double	sini;
	t_vec3	ref;

	cosi = vec3_dot(direction, normal);
	sini = (1 / n) * (1 / n) * (1 - cosi * cosi); //considere d'origine qu'on et dans l'air donc indice = 1
	ref = vec3_sub(vec3_multv(direction, (1 / n)), vec3_multv(normal, (cosi * (1 / n) + sqrt(1 - sini))));
	return (ref);
}

#define REFLECTION_BIAS 1e-4

t_who	apply_reflection_and_tansparency(t_ray *ray, t_object *objects[], size_t size, t_hit_info *hitt, size_t deep)
{
	t_hit_info	hit;
	t_ray		r;
	size_t		i;
	t_who		t_max;

	i = 0;
	t_max.hit.t = INFINITY;
	while (i < size)
	{
		r.origin = vec3_add(ray->origin, vec3_multv(ray->direction, hitt->t + REFLECTION_BIAS));
		//r.direction = ray->direction;
		r.direction = refraction(objects[i]->n, ray->direction, hitt->n);
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
	if (t_max.hit.t == INFINITY)
		t_max.hit.t = -1.0;
	else
	{
		if (objects[t_max.i]->n != INFINITY && deep < 300)
		{
			r.origin = vec3_add(ray->origin, vec3_multv(ray->direction, hitt->t + REFLECTION_BIAS));
			r.direction = refraction(objects[t_max.i]->n, ray->direction, hitt->n);
			t_max = apply_reflection_and_tansparency(&r, objects, size, &t_max.hit, deep + 1);
			if (t_max.hit.t >= 0)
				t_max.hit.t += hitt->t + REFLECTION_BIAS;
		}
		else
			t_max.hit.color = objects[t_max.i]->color;
	}
	return (t_max);
}