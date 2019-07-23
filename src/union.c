#include "rt.h"


static double	remote(double t, t_vec3 *origin, t_ray *ray)
{
	t_vec3	p;
	double	remote;

	p = vec3_add(ray->origin, vec3_multv(ray->direction, t));
	remote = (origin->x - p.x) * (origin->x - p.x);
	remote += (origin->y - p.y) * (origin->y - p.y);
	remote += (origin->z - p.z) * (origin->z - p.z);
	remote = sqrt(remote);
	return (remote);
}

#include <stdio.h>

t_hit_info		in_union(t_union *unions, t_ray *ray)
{
	t_hit_info	info;
	t_hit_info	first;
	t_hit_info	second;
	double		l1;
	double		l2;

	object_type(unions->first, ray, &first);
	object_type(unions->second, ray, &second);
	l1 = remote(first.t, &unions->super.pos, ray);
	l2 = remote(second.t, &unions->super.pos, ray);
	if ((first.t == -1 && second.t == -1))
		info.t = -1;
	else if(first.t == -1)
		info = second;
	else if(second.t == -1)
		info = first;
	else if (l1 > l2)
		info = first;
	else
		info = second;
	//printf("t: %f", info.t);
	return(info);
}

t_hit_info		in_intersection(t_intersec *intersection, t_ray *ray)
{
	t_hit_info	info;
	t_hit_info	first;
	t_hit_info	second;
	double		l1;
	double		l2;

	object_type(intersection->first, ray, &first);
	object_type(intersection->second, ray, &second);
	l1 = remote(first.t, &intersection->super.pos, ray);
	l2 = remote(second.t, &intersection->super.pos, ray);
	if ((first.t == -1 && second.t == -1))
		info.t = -1;
	else if(first.t == -1)
		info = second;
	else if(second.t == -1)
		info = first;
	else if (l1 < l2)
		info = first;
	else
		info = second;
	return(info);
}

t_hit_info		in_minus(t_minus *minus, t_ray *ray)
{
	t_hit_info info;
	t_hit_info first;
	t_hit_info second;

	object_type(minus->first, ray, &first);
	object_type(minus->second, ray, &second);
	info.t = -1;
	/*else if(first.t == -1)
		info = second;
	else if(second.t == -1)
		info = first;
	else if (first.t < second.t)
		info = first;
	else
		info = second;*/
	return (info);
}