/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:20:15 by mkervabo          #+#    #+#             */
/*   Updated: 2019/06/19 14:21:53 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	update_render(t_win *window, uint32_t **pixels)
{
	poll_events(window);
	SDL_UpdateTexture(window->screen, NULL, *pixels,
		window->width * sizeof(uint32_t));
	SDL_RenderCopy(window->renderer, window->screen, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

static void	hit_neg(uint32_t *pixel, t_ray *ray, t_scene *scn,
	t_who t)
{
	t_color color_light;
	bool	mod;

	color_light = (t_color) {
		0, 0, 0
	};
	mod = apply_light(&color_light, ray, t, scn);
	*pixel =
		to_rgb(mod ? clamp_rgb(scn->objects[t.i]->color.r - color_light.r) : 0,
		mod ? clamp_rgb(scn->objects[t.i]->color.g - color_light.g) : 0,
		mod ? clamp_rgb(scn->objects[t.i]->color.b - color_light.b) : 0);
}

static void	raytrace(t_scene *scene, t_cam camera, t_win *window)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	t_who		t;
	uint32_t	*pixels;

	pixels = malloc(sizeof(uint32_t) * window->width * window->height);
	ft_memset(pixels, 0, sizeof(uint32_t) * window->width * window->height);
	y = -1;
	while (++y < window->height && !window->quit)
	{
		x = 0;
		while (x < window->width)
		{
			ray = camera_create_ray(&camera, x, window->height - y - 1, window);
			t = in_objects(&ray, scene->objects, scene->objects_size);
			if (t.hit.t >= 0)
				hit_neg(pixels + y * window->width + x, &ray, scene, t);
			else
				pixels[y * window->width + x] = 0;
			x++;
		}
		update_render(window, &pixels);
	}
	free(pixels);
}

static void	render(t_scene *scene, t_cam camera, t_win *window)
{
	if (init_window(window))
	{
		raytrace(scene, camera, window);
		while (!window->quit)
			poll_events(window);
	}
	destroy_window(window);
}

bool		render_scene(t_toml_table *toml)
{
	t_scene			scene;
	t_cam			camera;
	t_win			window;

	ft_memset(&window, 0, sizeof(t_win));
	ft_memset(&scene, 0, sizeof(t_scene));
	if (!(scene.objects = read_objects(toml, &scene.objects_size)))
	{
		free_scene(&scene);
		free_toml_table(toml);
		return (false);
	}
	if (!(scene.lights = read_lights(toml, &scene.lights_size))
			|| !read_camera(toml, &camera) || !read_window(toml, &window))
	{
		free_scene(&scene);
		free_toml_table(toml);
		return (false);
	}
	free_toml_table(toml);
	render(&scene, camera, &window);
	free_scene(&scene);
	return (true);
}
