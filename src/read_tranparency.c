#include "rt.h"
#include "toml.h"

void	reflection(t_toml *toml, *bool ref)
{
	t_toml value;

	if (!(value = table_get(toml, "reflection"))
		|| value.type != TOML_Boolean)
		ref = false;
	else
		ref = value.value;
}

void	transparency(t_toml *toml, double *n)
{
	t_toml value;

	if (!(value = table_get(toml, "n")))
		n = INFINITY;
	if (read_digit(value, n) == false)
		n = INFINITY;
	if (n = 0)
		n = 0,001
}