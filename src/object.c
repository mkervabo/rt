#include "object.h"
#include "config_utils.h"
#include "shapes/shape_types.h"

bool	read_object(t_object *obj, t_toml_table *toml)
{
	t_toml	*value;

	if (!(obj->shape = read_shape(toml)))
		return (false);
	if (obj->shape->type != SHAPE_GROUP)
	{
		if (!read_toml_type(toml, &value, "material", TOML_Table))
			return (false);
		if (!(obj->material = read_material(value->value.table_v)))
			return (false);
	}
	return (true);
}
