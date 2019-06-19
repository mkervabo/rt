/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:32 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:51:17 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "toml.h"
# include <stdlib.h>
# include <stdbool.h>
# include <SDL.h>

# define SHADOW_BIAS 1e-4
# define WINDOW_ERR "Could not create window: "
# define ERR_INVALID_FILE "Error Invalid file\n"
# define USAGE_PRE "Usage: "
# define USAGE_POST " [scene.toml]\n"

typedef struct	s_polynome
{
	double		a;
	double		b;
	double		c;
}				t_polynome;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

enum			e_object_type
{
	Type_Sphere,
	Type_Cylinder,
	Type_Cone,
	Type_Plane
};

enum			e_light_type
{
	Light_Diffuse,
	Light_Specular,
	Light_Phong
};

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_light
{
	t_vec3				pos;
	t_color				color;
	double				intensity;
	int					expose;
}				t_light;

typedef struct	s_hit_info
{
	double		t;
	t_vec3		n;
}				t_hit_info;

typedef struct	s_who
{
	t_hit_info	hit;
	size_t		i;
}				t_who;

typedef struct	s_object
{
	enum e_object_type	type;
	enum e_light_type	light;
	t_vec3				pos;
	t_color				color;
	t_vec3				rot;
}				t_object;

typedef struct	s_sphere
{
	t_object	super;
	double		r;
}				t_sphere;

typedef struct	s_cylinder
{
	t_object	super;
	double		r;
}				t_cylinder;

typedef struct	s_cone
{
	t_object	super;
	double		angle;
	bool		revolution;
}				t_cone;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		rot;
}				t_cam;

typedef struct	s_win
{
	size_t			width;
	size_t			height;
	char			*name;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*screen;
	bool			quit;
}				t_win;

typedef struct	s_scene
{
	t_object	**objects;
	size_t		objects_size;
	t_light		**lights;
	size_t		lights_size;
}				t_scene;

int				ft_strcmp(const char *s1, const char *s2);

void			*nfree(void *ptr);

bool			read_window(t_toml_table *toml, t_win *win);

t_object		**read_objects(t_toml_table *toml, size_t *size);
t_light			**read_lights(t_toml_table *toml, size_t *size);
bool			read_camera(t_toml_table *toml, t_cam *camera);

bool			read_digit(t_toml *toml, double *digit);
bool			read_toml_type(t_toml_table *toml, t_toml **value, char *name,
				enum e_toml_type type);

bool			read_t_vec3(t_toml_table *toml, t_vec3 *vec);
t_object		*read_object(t_toml_table *toml);
bool			read_super(t_toml_table *toml, t_object *object);
t_light			*read_light(t_toml_table *toml);
bool			read_light_type(char *light, enum e_light_type *type);
bool			read_color(t_toml_table *toml, t_color *color);

bool			render_scene(t_toml_table *toml);

void			*ft_memset(void *s, int c, size_t n);
void			poll_events(t_win *window);
bool			init_window(t_win *window);
void			destroy_window(t_win *window);

t_ray			camera_create_ray(t_cam *camera, int x, int y, t_win *window);

t_vec3			vec3_multv(t_vec3 a, double v);
t_vec3			vec3_unit(t_vec3 v);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_divv(t_vec3 a, double v);
double			vec3_dot(t_vec3 a, t_vec3 b);
double			vec3_length(t_vec3 v);
t_vec3			vec3_rotate(t_vec3 v, t_vec3 rot);

t_color			color_add(t_color a, t_color b);
uint8_t			clamp_rgb(double value);
uint32_t		to_rgb(uint8_t r, uint8_t g, uint8_t b);

t_hit_info		in_sphere(t_sphere *sphere, t_ray *ray);
t_hit_info		in_cylinder(t_cylinder *cylinder, t_ray *ray);
t_hit_info		in_cone(t_cone *cone, t_ray *ray);
t_hit_info		in_plane(t_ray *ray);
t_who			in_objects(t_ray *ray, t_object *objects[], size_t size);

bool			solve_quadratic(t_polynome poly, float *t1, float *t2);
float			solve_quadratic_min(t_polynome poly);

double			receive_light(t_light *light, t_vec3 p, t_object *objects[],
				size_t size);
t_color			diffuse(t_light *light, t_vec3 n, t_vec3 p);
t_color			specular(t_light *light, t_hit_info hit, t_ray *ray);
t_color			phong(t_light *light, t_hit_info hit, t_ray *ray);
bool			apply_light(t_color *clr_light, t_ray *ray, t_who t,
				t_scene *s);
void			free_scene(t_scene *scene);
void			*free_ptr_array(void **array, size_t size);
size_t			ft_strlen(const char *s);

#endif
