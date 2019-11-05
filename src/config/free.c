#include "config.h"
#include "config_utils.h"
#include <stdlib.h>

bool	config_error(t_toml_table *toml, struct s_config *config, const char *msg)
{
	rt_error(NULL, msg);
	free_toml_table(toml);
	free_config(config);
	return (false);
}

void	*free_filter_array(t_filter **filters, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free_filter(filters[i]);
		i++;
	}
	free(filters);
	return (NULL);
}

void	*free_light_array(t_light **lights, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free_light(lights[i]);
		i++;
	}
	free(lights);
	return (NULL);
}

void	*free_object_array(t_object *objects, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free_shape(objects[i].shape);
		free_material(objects[i].material);
		i++;
	}
	free(objects);
	return (NULL);
}

void	free_config(struct s_config *config)
{
	free(config->name);
	free_object_array(config->scene.objects, config->scene.objects_size);
	free_light_array(config->scene.lights, config->scene.lights_size);
	free_filter_array(config->scene.filters, config->scene.filters_size);
	if (config->scene.camera)
		free_camera(config->scene.camera);
}
