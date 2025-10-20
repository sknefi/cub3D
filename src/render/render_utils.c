#include "../../include/cub3d.h"

uint32_t	rgba_from_rgb(t_rgb *color)
{
	return ((uint32_t)color->r << 24 | (uint32_t)color->g << 16
		| (uint32_t)color->b << 8 | 0xFF);
}
