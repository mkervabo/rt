#include "filter.h"
#include "filter_types.h"

#include "toml.h"
#include "config_utils.h"
#include "debug/assert.h"
#include <stdlib.h>

#include "black_and_white.h"
#include "sepia.h"
#include "negative.h"
#include "anti_aliasing.h"
#include "cartoon.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void			apply_filter(t_filter *filter, uint32_t *pixels, struct s_pixel_hit *hits, struct s_size window)
{
	if (filter->type == FILTER_BLACK_AND_WHITE)
		black_and_white_filter(pixels, hits, window);
	else if (filter->type == FILTER_SEPIA)
		sepia_filter(pixels, hits, window);
	else if (filter->type == FILTER_NEGATIVE)
		negative_filter(pixels, hits, window);
	else if (filter->type == FILTER_ANTI_ALIASING)
		anti_aliasing_filter((struct s_anti_aliasing_filter *)filter, pixels, hits, window);
	else if (filter->type == FILTER_CARTOON)
		cartoon_filter((struct s_cartoon_filter *)filter, pixels, hits, window);
	else
		assertf(false, "Unimplemented filter type: %d", filter->type);

}

t_filter		*read_filter(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_String)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "BLACK_AND_WHITE") == 0)
		return ((t_filter *)read_black_and_white_filter(toml));
	else if (ft_strcmp(type->value.string_v, "SEPIA") == 0)
		return ((t_filter *)read_sepia_filter(toml));
	else if (ft_strcmp(type->value.string_v, "NEGATIVE") == 0)
		return ((t_filter *)read_negative_filter(toml));
	else if (ft_strcmp(type->value.string_v, "ANTI_ALIASING") == 0)
		return ((t_filter *)read_anti_aliasing_filter(toml));
	else if (ft_strcmp(type->value.string_v, "CARTOON") == 0)
		return ((t_filter *)read_cartoon_filter(toml));
	return (NULL);
}

t_filter 	**read_filters(t_toml_table *toml, size_t *size)
{
	t_toml		*value;
	t_filter	**filters;
	size_t		i;

	if (read_toml_type(toml, &value, "filters", TOML_Array) == false)
	{
		*size = 0;
		return (NULL + 1);
	}
	if (value->value.array_v->len == 0
		|| value->value.array_v->inner[0].type != TOML_Table)
		return (NULL);
	*size = value->value.array_v->len;
	if (!(filters = malloc(sizeof(*filters) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(filters[i] = read_filter(value->value.array_v->inner[i].value.table_v)))
			return (NULL);
		i++;
	}
	return (filters);
}
