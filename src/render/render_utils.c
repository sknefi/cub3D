#include "../../include/cub3d.h"

static uint32_t	rgba_from_rgb(t_rgb *color)
{
	return ((uint32_t)color->r << 24 | (uint32_t)color->g << 16 | \
		(uint32_t)color->b << 8 | 0xFF);
}

uint32_t	get_ceiling_color(t_engine *engine)
{
	if (!engine || !engine->ceiling)
		return (0x000000FF);
	return (rgba_from_rgb(engine->ceiling));
}

uint32_t	get_floor_color(t_engine *engine)
{
	if (!engine || !engine->floor)
		return (0x141414FF);
	return (rgba_from_rgb(engine->floor));
}
