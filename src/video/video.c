#include "toml.h"
#include "video.h"
#include "config_utils.h"
#include <stdlib.h>

t_video			*read_video(t_toml_table *toml)
{
	t_video	*video;
	t_toml	     *value;

	if (!(video = malloc(sizeof(*video))))
		return (NULL);
	if (!(value = table_get(toml, "frame_sec")))
		return (nfree(video));
	if (read_digit(value, &video->frame_sec) == false)
		return (nfree(video));
	if (!(value = table_get(toml, "secondes")))
		return (nfree(video));
	if (read_digit(value, &video->frame) == false)
		return (nfree(video));
	video->frame *= video->frame_sec;
	return (video);
}
