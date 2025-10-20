#include "../../include/cub3d.h"

uint32_t	get_wall_color(t_ray *ray, mlx_texture_t *texture,
						int tex_x, int tex_y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	uint8_t	*pixel;

	if (!texture || !texture->pixels || tex_x < 0 || tex_y < 0
		|| tex_x >= (int)texture->width || tex_y >= (int)texture->height)
		return (rgba_from_rgb(&((t_rgb){255, 0, 0})));
	pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
	r = pixel[0];
	g = pixel[1];
	b = pixel[2];
	a = pixel[3];
	if (ray->side == 1)
	{
		r /= 2;
		g /= 2;
		b /= 2;
	}
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

mlx_texture_t	*get_texture_for_ray(t_engine *engine, t_ray *ray)
{
	t_textures_dir	index;

	if (!engine)
		return (NULL);
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			index = WE;
		else
			index = EA;
	}
	else
	{
		if (ray->step_y > 0)
			index = NO;
		else
			index = SO;
	}
	if (!engine->texture[index] && engine->textures[index])
		engine->texture[index] = mlx_load_png(engine->textures[index]);
	return (engine->texture[index]);
}
