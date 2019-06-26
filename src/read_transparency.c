#include "rt.h"
#include "toml.h"

void	read_reflection(t_toml_table *toml, bool *ref)
{
	t_toml *value;

	if (!(value = table_get(toml, "reflection"))
		|| value->type != TOML_Boolean)
		*ref = false;
	else
		*ref = value->value.boolean_v;
}

void	read_transparency(t_toml_table *toml, double *n)
{
	t_toml *value;

	if (!(value = table_get(toml, "n")))
		*n = INFINITY;
	else if (read_digit(value, n) == false)
		*n = INFINITY;
	if (n == 0)
		*n = 0.001;
}