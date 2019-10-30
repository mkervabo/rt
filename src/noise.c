#include "math/vec3.h"

#include <math.h>
#include <stdint.h>
#include <stddef.h>

#define DOUBLE_TAB(...) __VA_ARGS__, __VA_ARGS__

uint8_t g_permutation_table[512] = { DOUBLE_TAB(
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7,
	225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6,
	148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35,
	11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168,
	68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111,
	229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
	102, 143, 54,  65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208,
	89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198,
	173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
	255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
	223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163,  70, 221, 153, 101,
	155, 167,  43, 172, 9, 129, 22, 39, 253,  19, 98, 108, 110, 79, 113,
	224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238,
	210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
	49, 192, 214,  31, 181, 199, 106, 157, 184,  84, 204, 176, 115, 121, 50,
	45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
	141, 128, 195, 78, 66, 215, 61, 156, 180
) };

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static double	lerp(double t, double a, double b)
{
   return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
   int		h;
   double	u;
   double	v;

   h = hash & 15;
   u = h < 8 ? x : y;
   v = h < 4 || h == 12 || h == 13 ? y : z;
   return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);

}

double		noise(t_vec3 p)
{
	uint8_t		x2;
	uint8_t		y2;
	uint8_t		z2;
	double		u;
	double		v;
	double		w;
	int 		a;
	int		aa;
	int		ab;
	int		b;
	int		ba;
	int		bb;

	x2 = floor(p.x);
	y2 = floor(p.y);
	z2 = floor(p.z);
	p.x -= floor(p.x);
	p.y -= floor(p.y);
	p.z -= floor(p.z);
	u = fade(p.x);
	v = fade(p.y);
	w = fade(p.z);
	a = g_permutation_table[x2] + y2;
	aa = g_permutation_table[a] + z2;
	ab = g_permutation_table[a + 1] + z2;
	b = g_permutation_table[x2 + 1] + y2;
	ba = g_permutation_table[b] + z2;
	bb = g_permutation_table[b + 1] + z2;

  return
	  (lerp(w, lerp(v, lerp(u, grad(g_permutation_table[aa], p.x, p.y, p.z),
				grad(g_permutation_table[ba], p.x - 1, p.y, p.z)),
			lerp(u, grad(g_permutation_table[ab], p.x, p.y - 1, p.z),
				grad(g_permutation_table[bb], p.x - 1, p.y - 1, p.z))),
		lerp(v, lerp(u, grad(g_permutation_table[aa+1], p.x, p.y, p.z - 1),
				grad(g_permutation_table[ba+1], p.x - 1, p.y, p.z - 1)),
			lerp(u, grad(g_permutation_table[ab+1], p.x, p.y - 1, p.z - 1),
				grad(g_permutation_table[bb+1], p.x - 1, p.y - 1, p.z - 1)))));
}

double		turbulence(t_vec3 p)
{
	double	lacunarity = 2;
	double	gain = 0.6;
	float	sum = 0;
	float	scale = 1;
	float	totalgain = 1;
	int		i = 0;

	while (i++ < 10)
	{
		sum += totalgain * noise(vec3_multv(p, scale));
		scale *= lacunarity;
		totalgain *= gain;
	}
	return fabs(sum);
}
