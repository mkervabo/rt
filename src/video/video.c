#include "toml.h"
#include "video.h"
#include "config_utils.h"
#include <stdlib.h>

t_video			*read_video(t_toml_table *toml)
{
	t_video	*video;
	t_toml	     *value;

	if (!(video = malloc(sizeof(*video))))
		return (rt_error(NULL, "Can not allocate video"));
	if (!(value = table_get(toml, "frame_sec")))
		return (rt_error(video, "Missing frame_sec in video"));
	if (read_digit(value, &video->frame_sec) == false)
		return (rt_error(video, "Invalid frame_sec in video"));
	if (!(value = table_get(toml, "secondes")))
		return (rt_error(video, "Missing secondes in video"));
	if (read_digit(value, &video->frame) == false)
		return (rt_error(video, "Invalid secondes in video"));
	video->frame *= video->frame_sec;
	return (video);
}
