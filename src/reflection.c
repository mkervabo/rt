#include "rt.h"


double	clamp_cosi(double value)
{
	if (value < -1)
		return (-1);
	if (value > 1)
		return (1);
	return (value);
}

t_vec3	reflection(t_vec3 direction, t_vec3 normal)
{
	t_vec3 ref;
	double i;
	
	i = vec3_dot(direction, normal);
	//ref = vec3_add(vec3_multv(normal, -2 * i), direction);
	ref = vec3_sub(direction, vec3_mult(vec3_multv(normal, -2 * i), normal));
	return (ref);
}

t_vec3	refraction(double n, t_vec3 direction, t_vec3 normal)
{
	/*
	double	cosi;
	double	sini;
	t_vec3	ref;

	cosi = vec3_dot(direction, normal);
	sini = (1 / n) * (1 / n) * (1 - cosi * cosi);
	ref = vec3_sub(vec3_multv(direction, (1 / n)), vec3_multv(normal, (cosi * (1 / n) + sqrt(1 - sini))));
	return (ref);
	*/
	double cosi;
	double etai;
	t_vec3 ref;
	double eta;
	double k;

	cosi = clamp_cosi(vec3_dot(direction, normal));
	etai = 1;
	ref = normal;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		etai = n;
		n = 1;
		ref = vec3_multv(normal, -1);
	}
	eta = etai / n;
	k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? (t_vec3){0, 0, 0} : vec3_add(vec3_multv(direction, eta), vec3_multv(ref, eta * cosi - sqrt(k))));

}

void 	fresnel(double n, t_vec3 direction, t_vec3 normal, double *kr)
{
	double cosi;
	double etai;
	double etat;
	double sint;

	double cost;
	double Rs;
	double Rp;

	cosi = clamp_cosi(vec3_dot(direction, normal));
	etai = 1;
	etat = n;
	if (cosi > 0)
	{
		etai = n;
		etat = 1;
	}
	sint = 1 - cosi * cosi;
	sint = etai / etat * sqrt(sint < 0 ? 0 : sint);
	if (sint >= 1)
		*kr = 1;
	else
	{
		cost = 1 - sint * sint;
		cost = sqrt(cost < 0 ? 0 : cost);
		Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (Rs * Rs + Rp * Rp) / 2; 
	}
}

void	hit_ray(t_ray *r, t_who *t_max, t_object *object_i, size_t i)
{
	t_hit_info	hit;

	r->origin = vec3_sub(r->origin, object_i->pos);
	r->origin = vec3_rotate(r->origin, vec3_multv(object_i->rot, -1));
	r->direction = vec3_rotate(r->direction, vec3_multv(object_i->rot, -1));
	object_type(object_i, r, &hit);
	if (hit.t > 0 && hit.t < t_max->hit.t)
	{
		hit.n = vec3_rotate(hit.n, object_i->rot);
		t_max->hit = hit;
		t_max->i = i;
	}
}

#define REFLECTION_BIAS 1e-4

void	hit_new_ray(t_ray *r, t_object *objects[], size_t size, t_who *t_max, t_hit_info *hitt, size_t deep)
{
	if (t_max->hit.t == INFINITY)
		t_max->hit.t = -1.0;
	else
	{
		if (objects[t_max->i]->n != INFINITY && deep < 5)
		{
			*t_max = apply_reflection_and_tansparency(r, objects, size, &t_max->hit, deep + 1);
			if (t_max->hit.t >= 0)
				t_max->hit.t += hitt->t + REFLECTION_BIAS;
		}
		else
			t_max->hit.color = objects[t_max->i]->color;
	}
	//printf("Nray  r:%f, g:%f, b:%f\n", t_max->hit.color.r, t_max->hit.color.g, t_max->hit.color.b);
}

t_color color_add2(t_color a, t_color b)
{
	return ((t_color) {
		.r = (a.r + b.r) / 2,
		.g = (a.g + b.g) / 2,
		.b = (a.b + b.b) / 2
	});
}

t_who	apply_reflection_and_tansparency(t_ray *ray, t_object *objects[], size_t size, t_hit_info *hitt, size_t deep)
{
	t_ray		r;
	size_t		i;
	t_who		t_max_refl;
	t_who		t_max_refr;
	double		kr;

	i = 0;
	t_max_refl.hit.t = INFINITY;
	t_max_refr.hit.t = INFINITY;
	while (i < size)
	{
		fresnel(objects[i]->n, ray->direction, hitt->n, &kr);;
		r.origin = vec3_add(ray->origin, vec3_multv(ray->direction, hitt->t + REFLECTION_BIAS)); //different si dans l'object ou non (a faire)
		//r.direction = ray->direction;
		r.direction = reflection(ray->direction, hitt->n);
		hit_ray(&r, &t_max_refl, objects[i], i);
		r.direction = refraction(objects[i]->n, ray->direction, hitt->n);
		hit_ray(&r, &t_max_refr, objects[i], i);
		i++;
	}
	//r.direction = ray->direction;
	r.direction = reflection(ray->direction, hitt->n);
	hit_new_ray(&r, objects, size, &t_max_refl, hitt, deep);
	//printf("Refl  r:%f, g:%f, b:%f\n", t_max_refl.hit.color.r, t_max_refl.hit.color.g, t_max_refl.hit.color.b);
	if (kr < 1)
	{
		r.direction = refraction(objects[t_max_refr.i]->n, ray->direction, hitt->n);
		hit_new_ray(&r, objects, size, &t_max_refr, hitt, deep);
	}
	else
		t_max_refr.hit.color = (t_color){0,0,0};
	//printf("Refr  r:%f, g:%f, b:%f\n", t_max_refr.hit.color.r, t_max_refr.hit.color.g, t_max_refr.hit.color.b);
	if (t_max_refl.hit.t == INFINITY || t_max_refr.hit.t == INFINITY)
		t_max_refr.hit.t = -1.0;
	else
		t_max_refr.hit.color = color_add2(t_max_refl.hit.color, t_max_refr.hit.color); 
	return (t_max_refr);
}