#include "rt.h"

t_hit_info	in_union(t_union *unions, t_ray *ray)
{
	t_hit_info info;
	t_hit_info first;
	t_hit_info second;

	object_type(unions->first, ray, &first);
	object_type(unions->second, ray, &second);
	if (first.t == -1 && second.t == -1)
		info.t = -1;
	else if(first.t == -1)
		info = second;
	else if(second.t == -1)
		info = first;
	else if (first.t < second.t)
		info = first;
	else
		info = second;
	return(info);	
}

t_hit_info	in_intersection(t_intersec *intersection, t_ray *ray)
{
	t_hit_info info;
	t_hit_info first;
	t_hit_info second;

	object_type(intersection->first, ray, &first);
	object_type(intersection->second, ray, &second);
	if (first.t == -1 && second.t == -1)
		info.t = -1;	
	else if (first.t > second.t)
		info = first;
	else
		info = second;
	return(info);	
}

t_hit_info	in_minus(t_minus *intersection, t_ray *ray)
{
	t_hit_info info;
	t_hit_info first;
	t_hit_info second;

	object_type(intersection->first, ray, &first);
	object_type(intersection->second, ray, &second);
	if ((first.t == -1 && second.t == -1) || (first.t == second.t))
		info.t = -1;
	else if(first.t == -1)
		info = second;
	else if(second.t == -1)
		info = first;
	else if (first.t < second.t)
		info = first;
	else
		info = second;
	return (info);
}