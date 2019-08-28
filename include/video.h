#ifndef VIDEO_H
# define VIDEO_H

# include "math/vec3.h"
# include "toml.h"

struct s_shape;
struct s_material;
struct s_light;
struct s_config;

typedef struct	s_video
{
	double		frame_sec;
	double		frame;
}				t_video;

struct 			s_frame
{
	double 		from;
	double		to;
	t_vec3		position;
	t_vec3		rotation;
};

struct 			s_video_light_frame
{
	double 				second;
	struct s_light		*light;
};

struct			s_video_light
{
	size_t							frame_len;
	struct s_video_light_frame		*frame;
};

struct 			s_video_frame
{
	double 				second;
	struct s_shape		*shape;
	struct s_material	*material;
};

struct			s_video_shape
{
	size_t					video_len;
	struct s_frame			*video;
	size_t					frame_len;
	struct s_video_frame	*frame;
};


t_video					*read_video(t_toml_table *toml);
bool					read_frame(struct s_frame *frame, t_toml_table *toml);
bool					read_video_shape(t_toml_table *toml, struct s_video_shape *video);
bool					read_video_frame(t_toml_table *toml, struct s_video_shape *video);
bool					read_video_light(t_toml_table *toml, struct s_video_light *video);
void					video_transform_scene(struct s_config *config, size_t frame);

#endif
