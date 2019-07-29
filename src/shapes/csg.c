#include "csg.h"
#include "shape_types.h"
#include "utils.h"
#include "math/quadratic.h"
#include "config_utils.h"
#include <stdlib.h>
#include <math.h>
#include "toml.h"

#include <stdio.h>

static size_t	min(size_t i, size_t j)
{
	if (i < j)
		return (i);
	return (j);
}

static void	swap(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort4(double *a, double *b, double *c, double *d)
{
	if (*a > *b)
		swap(a, b);
	if (*c > *d)
		swap(c, d);
	if (*a > *c)
		swap(a, c);
	if (*b > *d)
		swap(b, d);
	if (*b > *c)
		swap(b, c);
}

static struct s_intersection_tab csg_difference(struct s_intersection_tab first, struct s_intersection_tab second)
{
	struct s_intersection	f;
	struct s_intersection	s;
	struct s_intersection_tab tab;
	size_t					i;
	size_t					j;
	size_t					len;

	len = first.len + second.len;
	tab.inner = malloc(len * sizeof(struct s_intersection));
	tab.len = 0;
	i = 0;
	j = 0;
	while (i < first.len)
	{
		f = first.inner[i];
		s = second.inner[min(j, second.len - 1)];
		if (f.to < s.to || j >= second.len)
			i++;
		else
			j++;
		if (f.to >= s.from && s.to >= f.from)
		{
			if (f.from < s.from)
				tab.inner[tab.len++] = (struct s_intersection) {
					.from = f.from,
					.to = s.from
				};
			if (f.to > s.to)
				tab.inner[tab.len++] = (struct s_intersection) {
					.from = s.to,
					.to = f.to
				};
			if (f.to < s.to)
				j++;
			else
				i++;
		
		}
		else if (f.to < s.to || j >= second.len)
			tab.inner[tab.len++] = f;
	}
	while (i < first.len)
	{
		tab.inner[tab.len++] = first.inner[i];
		i++;
	}
	return (tab);
}

static struct s_intersection_tab csg_intersection(struct s_intersection_tab first, struct s_intersection_tab second)
{
	struct s_intersection	f;
	struct s_intersection	s;
	struct s_intersection_tab tab;
	size_t					i;
	size_t					j;
	size_t					len;

	len = first.len > second.len ? first.len : second.len;
	tab.inner = malloc((len + 1) * sizeof(struct s_intersection));
	tab.len = 0;
	i = 0;
	j = 0;
	while (i < first.len && j < second.len)
	{
		f = first.inner[i];
		s = second.inner[j];
		if (f.to < s.to)
			i++;
		else
			j++;
		if (f.to >= s.from && s.to >= f.from)
		{
			double a = f.from;
			double b = f.to;
			double c = s.from;
			double d = s.to;
			sort4(&a, &b, &c, &d);
			tab.inner[tab.len++] = (struct s_intersection) {
				.from = b,
				.to = c
			};
		}
	}
	return (tab);
}

static struct s_intersection_tab csg_union(struct s_intersection_tab first, struct s_intersection_tab second)
{
	struct s_intersection	f;
	struct s_intersection	s;
	struct s_intersection_tab tab;
	size_t					i;
	size_t					j;
	size_t					len;

	len = first.len + second.len;
	tab.inner = malloc((len + 1) * sizeof(struct s_intersection));
	tab.len = 0;
	i = 0;
	j = 0;
	while (i < first.len && j < second.len)
	{
		f = first.inner[i];
		s = second.inner[j];
		if (f.to < s.to)
			i++;
		else
			j++;
		//one inside another
		if ((f.from < s.from  && f.to > s.to) || (s.from < f.from  && s.to > f.to))
			continue;
		//overlap
		if (f.to >= s.from && s.to >= f.from)
		{
			double a = f.from;
			double b = f.to;
			double c = s.from;
			double d = s.to;
			sort4(&a, &b, &c, &d);
			tab.inner[tab.len++] = (struct s_intersection) {
				.from = a,
				.to = d
			};
			if (f.to < s.to)
				j++;
			else
				i++;
		}
		else
		{
			if (f.to < s.to)
				tab.inner[tab.len++] = f;
			else
				tab.inner[tab.len++] = s;
		}
	}
	while (i < first.len)
	{
		tab.inner[tab.len++] = first.inner[i];
		i++;
	}
	while (j < second.len)
	{
		tab.inner[tab.len++] = second.inner[j];
		j++;
	}
	return (tab);
}

struct s_hit	hit_csg(struct s_ray ray, struct s_csg *csg,
		struct s_intersection_tab *intersections)
{
	struct s_hit				first;
	struct s_hit				second;
	struct s_intersection_tab	t1;
	struct s_intersection_tab	t2;
	struct s_intersection_tab	tab;

	t1.len = 0;
	t2.len = 0;
	first = hit_shape(ray, csg->first, &t1);
	second = hit_shape(ray, csg->second, &t2);
	if (csg->op == CSG_DIFFERENCE)
		tab = csg_difference(t1, t2);
	else if (csg->op == CSG_INTERSECTION)
		tab = csg_intersection(t1, t2);
	else
		tab = csg_union(t1, t2);
	if (intersections)
		*intersections = tab;
	if (tab.len == 0)
		return ((struct s_hit) { .t = -1 });
	else if (tab.inner[0].from == t1.inner[0].to || tab.inner[0].from == t1.inner[0].from)
		return (first);
	else
		return (second);
}

struct s_csg			*read_csg(t_toml_table *toml, enum e_csg_op op)
{
	struct s_csg	*csg;
	t_toml			*value;

	if (!(csg = malloc(sizeof(struct s_csg))))
		return (NULL);
	if (!read_shape_super(toml, &csg->super))
		return (NULL);
	if (!(value = table_get(toml, "first")))
		return (nfree(csg));
	if ((csg->first = read_shape(value->value.table_v)) == NULL)
		return (nfree(csg));
	if (!(value = table_get(toml, "second")))
		return (nfree(csg));
	if ((csg->second = read_shape(value->value.table_v)) == NULL)
		return (nfree(csg));
	csg->super.type = SHAPE_CSG;
	csg->op = op;
	return (csg);
}
