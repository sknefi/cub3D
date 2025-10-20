#include "../../include/cub3d.h"

static char	get_tile(t_engine *engine, int x, int y)
{
	size_t	len;

	if (y < 0 || y >= (int)engine->map->height)
		return (' ');
	len = ft_strlen(engine->map->map[y]);
	if (x < 0 || x >= (int)len)
		return (' ');
	return (engine->map->map[y][x]);
}

static void	init_ray_helper(t_ray *ray, t_engine *engine, int x)
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

void	init_ray(t_ray *ray, t_engine *engine, int x)
{
	init_ray_helper(ray, engine, x);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (engine->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - engine->player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (engine->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - engine->player->y) * ray->delta_dist_y;
	}
}

static void	calculate_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->distance = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->delta_dist_y;
	if (ray->distance <= 0.0001)
		ray->distance = 0.0001;
}

bool	trace_ray(t_ray *ray, t_engine *engine)
{
	char	tile;

	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		tile = get_tile(engine, ray->map_x, ray->map_y);
		if (tile == '1')
			break ;
		else if (tile == ' ')
			return (false);
	}
	calculate_distance(ray);
	return (true);
}

void	draw_column(t_engine *engine, int x, t_ray *ray)
{
	int			y;
	int			draw_end;
	int			draw_start;
	int			line_height;
	uint32_t	floor_color;
	uint32_t	wall_texture;
	uint32_t	ceiling_color;
	mlx_texture_t	*texture;
	double		wall_x;
	int			tex_x;
	double		tex_step;
	double		tex_pos;
	int			tex_y;

	line_height = (int)(WIN_H / ray->distance);
	if (line_height <= 0)
		line_height = 1;
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	ceiling_color = rgba_from_rgb(engine->ceiling);
	floor_color = rgba_from_rgb(engine->floor);
	y = 0;
	while (y < draw_start)
		mlx_put_pixel(engine->frame, x, y++, ceiling_color);
	texture = get_texture_for_ray(engine, ray);
	if (ray->side == 0)
		wall_x = engine->player->y + ray->distance * ray->dir_y;
	else
		wall_x = engine->player->x + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	if (texture && texture->width)
	{
		tex_x = (int)(wall_x * (double)texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= (int)texture->width)
			tex_x = texture->width - 1;
		if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
			tex_x = texture->width - tex_x - 1;
		tex_step = (double)texture->height / line_height;
		tex_pos = (draw_start - WIN_H / 2 + line_height / 2) * tex_step;
	}
	else
	{
		tex_step = 0.0;
		tex_pos = 0.0;
		tex_x = 0;
	}
	while (y <= draw_end)
	{
		if (texture && texture->height)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)texture->height)
				tex_y = texture->height - 1;
			wall_texture = get_wall_color(ray, texture, tex_x, tex_y);
			tex_pos += tex_step;
		}
		else
			wall_texture = rgba_from_rgb(&(t_rgb){160, 160, 160});
		mlx_put_pixel(engine->frame, x, y++, wall_texture);
	}
	while (y < WIN_H)
		mlx_put_pixel(engine->frame, x, y++, floor_color);
}
