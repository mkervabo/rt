#ifndef CONFIG_H
# define CONFIG_H

# include "math/size.h"
# include "scene.h"
# include "camera.h"

struct	s_config {
	char			*name;
	struct s_size	size;
	t_scene			scene;
};

bool	read_config(const char *file, struct s_config *config);
void	free_config(struct s_config *config);

#endif
