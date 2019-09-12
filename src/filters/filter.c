#include "filter.h"
#include "filter_types.h"

#include "toml.h"
#include "config_utils.h"
#include "debug/assert.h"
#include <stdlib.h>

#include "black_and_white.h"

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
