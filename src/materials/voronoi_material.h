#ifndef MATERIALS_VORONOI_MATERIAL_H
# define MATERIALS_VORONOI_MATERIAL_H

# include "material.h"

struct s_voronoi_material {
	t_material	super;
	double		u;
	double		v;
	double		size;
	t_material	*material;
};

t_color						voronoi_material_color(struct s_voronoi_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit);
double						voronoi_material_transparency(struct s_voronoi_material *material, struct s_hit *hit, t_material **color);
struct s_voronoi_material	*read_voronoi_material(t_toml_table *toml);
void						free_voronoi_material(struct s_voronoi_material *material);

#endif
