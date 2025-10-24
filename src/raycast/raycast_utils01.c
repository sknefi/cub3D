#include "../../include/cub3d.h"

void	init_ray_helper(t_ray *ray, t_engine *engine, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->dir_x = engine->player->dx + engine->player->plane_x * ray->camera_x;
	ray->dir_y = engine->player->dy + engine->player->plane_y * ray->camera_x;
	ray->map_x = (int)engine->player->x;
	ray->map_y = (int)engine->player->y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

char	get_tile_in_raycast(t_engine *engine, int x, int y)
{
	size_t	len;

	if (y < 0 || y >= (int)engine->map->height)
		return (' ');
	len = ft_strlen(engine->map->map[y]);
	if (x < 0 || x >= (int)len)
		return (' ');
	return (engine->map->map[y][x]);
}

void	calculate_distance_of_ray(t_ray *ray)
{
	if (ray->side == 0)
		ray->distance = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->delta_dist_y;
	if (ray->distance <= 0.0001)
		ray->distance = 0.0001;
}

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
	if (!engine->texture[index] && engine->texture_path[index])
	{
		engine->texture[index] = mlx_load_png(engine->texture_path[index]);
		if (!engine->texture[index])
			return (NULL);
	}
	return (engine->texture[index]);
}
