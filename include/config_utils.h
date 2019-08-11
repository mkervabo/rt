#ifndef CONFIG_UTILS
# define CONFIG_UTILS

# include "toml.h"
# include "math/vec3.h"
# include <stdbool.h>

bool	read_digit(t_toml *toml, double *digit);
bool	read_vec3(t_toml_table *toml, t_vec3 *vec);
bool	read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type);
void	*nfree(void *ptr);

#endif
