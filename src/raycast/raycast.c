#include "../../include/cub3d.h"

// alpha starting

static void	init_ray(t_ray *ray, t_engine *engine, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->dir_x = engine->player->dx + engine->player->plane_x * ray->camera_x;
	ray->dir_y = engine->player->dy + engine->player->plane_y * ray->camera_x;
	ray->map_x = (int)engine->player->x;
	ray->map_y = (int)engine->player->y;
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1.0 / ray->dir_y);
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

static bool	trace_ray(t_ray *ray, t_engine *engine)
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
	if (ray->side == 0)
		ray->distance = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->distance = ray->side_dist_y - ray->delta_dist_y;
	if (ray->distance <= 0.0001)
		ray->distance = 0.0001;
	return (true);
}

static uint32_t	get_wall_color(t_ray *ray)
{
	t_rgb	wall_color;

	wall_color = (t_rgb){180, 60, 60};
	if (ray->side == 0 && ray->step_x < 0)
		wall_color = (t_rgb){60, 180, 60};
	else if (ray->side == 1 && ray->step_y > 0)
		wall_color = (t_rgb){60, 60, 180};
	else
		wall_color = (t_rgb){180, 180, 60};
	if (ray->side == 1)
		wall_color = (t_rgb){wall_color.r / 2, wall_color.g / 2, wall_color.b / 2};
	return (rgba_from_rgb(&wall_color));
}

static void	draw_column(t_engine *engine, int x, t_ray *ray)
{
	int			y;
	int			draw_end;
	int			draw_start;
	int			line_height;
	uint32_t	floor_color;
	uint32_t	wall_texture;
	uint32_t	ceiling_color;

	line_height = (int)(WIN_H / ray->distance);
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	ceiling_color = get_ceiling_color(engine);
	floor_color = get_floor_color(engine);
	y = 0;
	while (y < draw_start)
		mlx_put_pixel(engine->frame, x, y++, ceiling_color);	
	wall_texture = get_wall_color(ray);
	// TODO draw texture
	while (y <= draw_end)
		mlx_put_pixel(engine->frame, x, y++, wall_texture);
	while (y < WIN_H)
		mlx_put_pixel(engine->frame, x, y++, floor_color);
}

void	raycast_scene(t_engine *engine)
{
	int		x;
	t_ray	ray;

	if (!engine || !engine->frame)
		return ;
	x = 0;
	while (x < WIN_W)
	{
		init_ray(&ray, engine, x);
		if (trace_ray(&ray, engine))
			draw_column(engine, x, &ray);
		x++;
	}
}
