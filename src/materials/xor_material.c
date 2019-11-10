#include "xor_material.h"
#include "material_types.h"
#include "config_utils.h"

#include <stdlib.h>
#include <math.h>

/*static t_color				hsv_to_rgb(double h, double s, double v)
{
	t_color RGB;
    double H = h, S = s, V = v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        RGB = (t_color){.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        RGB = (t_color){.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        RGB = (t_color){.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        RGB = (t_color){.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        RGB = (t_color){.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        RGB = (t_color){.r = V, .g = P, .b = Q};
    else
        RGB = (t_color){.r = 0., .g = 0., .b = 0.};
    return RGB;
}*/

t_color hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v)
{
    uint8_t region;
	uint8_t remainder;
	uint8_t p;
	uint8_t q;
	uint8_t t;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		return ((t_color){v, t, p });
	if (region == 1)
		return ((t_color){ q, v, p });
	if (region == 2)
		return ((t_color){ p, v, t });
	if (region == 3)
		return ((t_color){ p, q, v });
	if (region == 4)
		return((t_color){ t, p, v });
	else
		return((t_color){ v, p, q });
}

double	xor_material_transparency(struct s_xor_material *material, struct s_hit *hit)
{
	(void)material;
	(void)hit;
	return (0.0);
}

static t_color				xor_hsv(struct s_hit *hit)
{
	uint8_t c = (uint8_t)(hit->u * 255) ^ (uint8_t)(hit->v * 255);
	return (hsv_to_rgb(c, 255, 255));
}

static t_color				xor_rgb( struct s_hit *hit)
{
	uint8_t c = (uint8_t)(hit->u * 255) ^ (uint8_t)(hit->v * 255);
	return((t_color) {c, c, c});
}

t_color						xor_material_color(struct s_xor_material *material, t_scene *scene, struct s_ray ray, struct s_hit *hit)
{
	(void)scene;
	(void)ray;

	if (material->color)
		return (xor_hsv(hit));
	return (xor_rgb(hit));
}

struct s_xor_material	*read_xor_material(t_toml_table *toml)
{
	struct s_xor_material	*material;
	t_toml					*value;

	(void)toml;
	if (!(material = malloc(sizeof(*material))))
		return (rt_error(NULL, "Can not allocate xor material"));
	if (!read_toml_type(toml, &value, "color", TOML_Boolean))
		material->color = true;
	material->super.type = MATERIAL_XOR;
	return (material);
}
