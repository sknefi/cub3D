#include "../../include/cub3d.h"

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
		tile = get_tile_in_raycast(engine, ray->map_x, ray->map_y);
		if (tile == '1')
			break ;
		else if (tile == ' ')
			return (false);
	}
	calculate_distance_of_ray(ray);
	return (true);
}

bool	draw_wall_coloumn(t_engine *engine, t_ray *ray, t_coloumn_info *coloumn_info)
{

	uint32_t	wall_texture;
	double		wall_x;
	int			tex_x;
	double		tex_step;
	double		tex_pos;
	mlx_texture_t	*texture;
	int			tex_y;

	texture = get_texture_for_ray(engine, ray);
	if (!texture)
		return (false);
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
        tex_step = (double)texture->height / coloumn_info->line_height;
        tex_pos = (coloumn_info->draw_start - WIN_H / 2 + coloumn_info->line_height / 2) * tex_step;
    }
	else
	{
		tex_step = 0.0;
		tex_pos = 0.0;
		tex_x = 0;
	}
	while (coloumn_info->y <= coloumn_info->draw_end)
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
		mlx_put_pixel(engine->frame, coloumn_info->x, coloumn_info->y++, wall_texture);
	}
	return (true);
}


bool	draw_scene(t_engine *engine, int x, t_ray *ray)
{
	int				y;
	int				draw_start;
	int				draw_end;
	int				line_height;
	t_coloumn_info	coloumn_info;

	line_height = (int)(WIN_H / ray->distance);
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	// draw column
	y = 0;
	coloumn_info = (t_coloumn_info){y, x, draw_start, draw_end, line_height};
	while (coloumn_info.y < draw_start)
		mlx_put_pixel(engine->frame, x, coloumn_info.y++, rgba_from_rgb(engine->ceiling));
	draw_wall_coloumn(engine, ray, &coloumn_info);
	while (coloumn_info.y < WIN_H)
		mlx_put_pixel(engine->frame, x, coloumn_info.y++, rgba_from_rgb(engine->floor));
	return (true);
}
