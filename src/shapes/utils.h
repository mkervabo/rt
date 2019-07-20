#ifndef SRC_SHAPES_UTILS_H
# define SRC_SHAPES_UTILS_H

#include "toml.h"
#include "shapes.h"

void	*nfree(void *ptr);
bool	read_shape_super(t_toml_table *toml, t_shape *shape);

#endif
