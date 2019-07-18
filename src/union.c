#include "rt.h"

void		in_union(t_struct unions, t_ray *ray, size_t size)
{
	size_t	i;
	size_t	y;
	t_ray	r;
	t_ray	r2
	t_who	t;
	t_hit_info	hit;

	i = 0;
	while (i < size && t_max[i] !+ -1)
	{
		y = 0;
		r = *ray;
		r.origin = vec3_sub(r.origin, unions[i]->pos);
		r.origin = vec3_rotate(r.origin, vec3_multv(unions[i]->rot, -1));
		r.direction = vec3_rotate(r.direction, vec3_multv(unions[i]->rot, -1))
		while(y < size)
		{
			r2 = *r;
			r2.origin = vec3_sub(r2.origin, unions[i].objects[y]->pos);
			r2.origin = vec3_rotate(r.origin, vec3_multv(unions[i].objects[y]->rot, -1));
			r2.direction = vec3_rotate(r.direction, vec3_multv(unions.[i].objects[y]->rot, -1));
			object_type(unions.[i].objects[y], &r, &hit);
			if (hit.t > 0 && hit.t < t_max.hit.t)
			{
				hit.n = vec3_rotate(hit.n, unions[i].objects[y]->rot);
				t_max.hit = hit;
				t_max.i = i;
			}
			y++;	
		}
		if (t.hit.t == INFINITY)
			t.hit.t = -1.0;
		else
		{
			if (objects[t_max.i]->n != INFINITY)
				t = apply_reflection_and_tansparency(ray, objects, size, &t_max.hit, 0);
			else
				t.hit.color = objects[t_max.i]->color;
		}
		
		i++;
	}
	if (t_max.i == -1)
	return (t_max);
}