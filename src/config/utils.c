#include "config_utils.h"

bool	read_digit(t_toml *toml, double *digit)
{
	if (toml->type == TOML_Float)
		*digit = toml->value.float_v;
	else if (toml->type == TOML_Integer)
		*digit = toml->value.integer_v;
	else
		return (false);
	return (true);
}

bool	read_vec3(t_toml_table *toml, t_vec3 *vec)
{
	t_toml	*value;

	if (!(value = table_get(toml, "x")))
		vec->x = 0;
	else if (read_digit(value, &vec->x) == false)
		return (false);
	if (!(value = table_get(toml, "y")))
		vec->y = 0;
	else if (read_digit(value, &vec->y) == false)
		return (false);
	if (!(value = table_get(toml, "z")))
		vec->x = 0;
	else if (read_digit(value, &vec->z) == false)
		return (false);
	return (true);
}


bool	read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type)
{
	if (!(*value = table_get(toml, name)))
		return (false);
	if ((*value)->type != type)
		return (false);
	return (true);
}
