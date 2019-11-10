#include "string_utils.h"

#include "config_utils.h"
#include <stdlib.h>
#include <unistd.h>

bool	read_digit(t_toml *toml, double *digit)
{
	if (toml->type == TOML_Float)
		*digit = toml->value.float_v;
	else if (toml->type == TOML_Integer)
		*digit = toml->value.integer_v;
	else
		return ((bool)rt_error(NULL, "Is not a number"));
	return (true);
}

bool	read_vec3(t_toml_table *toml, t_vec3 *vec)
{
	t_toml	*value;

	if (!(value = table_get(toml, "x")))
		vec->x = 0;
	else if (read_digit(value, &vec->x) == false)
		return ((bool)rt_error(NULL, "Invalid vec3 x"));
	if (!(value = table_get(toml, "y")))
		vec->y = 0;
	else if (read_digit(value, &vec->y) == false)
		return ((bool)rt_error(NULL, "Invalid vec3 y"));
	if (!(value = table_get(toml, "z")))
		vec->z = 0;
	else if (read_digit(value, &vec->z) == false)
		return ((bool)rt_error(NULL, "Invalid vec3 z"));
	return (true);
}

bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in red color"));
	else
		color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in green color"));
	else
		color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->b = 0;
	else if (value->type != TOML_Integer)
		return ((bool)rt_error(NULL, "Is not a interger in blue color"));
	else
		color->b = value->value.integer_v;
	return (true);
}

bool	read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type)
{
	if (!(*value = table_get(toml, name)))
		return (false);
	if ((*value)->type != type)
		return ((bool)rt_error(NULL, "Unexpected type in table get"));
	return (true);
}


#define CSI "\033["
#define CSI_GREEN CSI "32;01m"
#define CSI_WHITE CSI "37;01m"
#define CSI_BLUE CSI "34;01m"
#define CSI_YELLOW CSI "33;01m"
#define CSI_RED CSI "31m"
#define CSI_RESET CSI "0m"
#define RT_ERROR CSI_BLUE "rt: " CSI_RED "Error: " CSI_WHITE

void	*rt_error(void *ptr, const char *msg)
{
	write(STDERR_FILENO, RT_ERROR, sizeof(RT_ERROR) - 1);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, CSI_RESET "\n", sizeof(CSI_RESET));
	free(ptr);
	return (NULL);	
}

void	*nfree(void	*ptr)
{
	free(ptr);
	return (NULL);
}

