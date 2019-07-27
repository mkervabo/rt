#include "object.h"

bool	read_object(t_object *obj, t_toml_table *toml)
{
	if (!(obj->shape = read_shape(toml)))
		return (false);
	if (!(obj->material = read_material(toml)))
		return (false);
	return (true);
}
