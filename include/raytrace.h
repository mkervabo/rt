/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:38:10 by mkervabo          #+#    #+#             */
/*   Updated: 2019/11/05 14:38:29 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "color.h"
# include "scene.h"
# include "ray.h"
# include "filter.h"

t_color			raytrace(t_scene *scene, struct s_ray ray,
	struct s_pixel_hit *hit);
struct s_hit	hit_scene(t_object *objects, size_t object_size,
	struct s_ray ray, struct s_intersection_tab *intersections);
#endif
