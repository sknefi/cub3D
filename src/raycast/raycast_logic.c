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
		ray->side_dist_x = (ray->map_x + 1.0 - engine->player->x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (engine->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - engine->player->y)
			* ray->delta_dist_y;
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

static bool	init_texture_state(t_engine *engine, t_ray *ray,
				t_coloumn_info *ci, t_tex_state *tex)
{
	double	wall_x;

	tex->texture = get_texture_for_ray(engine, ray);
	if (!tex->texture)
		return (false);
	if (!tex->texture->width)
		return (true);
	if (ray->side == 0)
		wall_x = engine->player->y + ray->distance * ray->dir_y;
	else
		wall_x = engine->player->x + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	tex->tex_x = (int)(wall_x * tex->texture->width);
	if (tex->tex_x < 0)
		tex->tex_x = 0;
	else if (tex->tex_x >= (int)tex->texture->width)
		tex->tex_x = tex->texture->width - 1;
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex->tex_x = tex->texture->width - tex->tex_x - 1;
	tex->tex_step = (double)tex->texture->height / ci->line_height;
	tex->tex_pos = (ci->draw_start - WIN_H / 2 + ci->line_height / 2)
		* tex->tex_step;
	return (true);
}

bool	draw_wall_coloumn(t_engine *engine, t_ray *ray, t_coloumn_info *ci)
{
	t_tex_state	tex;
	uint32_t	color;
	int			tex_y;

	tex = (t_tex_state){0};
	if (!init_texture_state(engine, ray, ci, &tex))
		return (false);
	while (ci->y <= ci->draw_end)
	{
		if (!tex.texture || !tex.texture->height)
			color = rgba_from_rgb(&(t_rgb){160, 160, 160});
		else
		{
			tex_y = (int)tex.tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= (int)tex.texture->height)
				tex_y = tex.texture->height - 1;
			color = get_wall_color(ray, tex.texture, tex.tex_x, tex_y);
			tex.tex_pos += tex.tex_step;
		}
		mlx_put_pixel(engine->frame, ci->x, ci->y++, color);
	}
	return (true);
}

bool	draw_scene(t_engine *engine, int x, t_ray *ray)
{
	int				y;
	int				draw_start;
	int				draw_end;
	int				line_height;
	t_coloumn_info	ci;

	line_height = (int)(WIN_H / ray->distance);
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	y = 0;
	ci = (t_coloumn_info){y, x, draw_start, draw_end, line_height};
	while (ci.y < draw_start)
		mlx_put_pixel(engine->frame, x, ci.y++, rgba_from_rgb(engine->ceiling));
	draw_wall_coloumn(engine, ray, &ci);
	while (ci.y < WIN_H)
		mlx_put_pixel(engine->frame, x, ci.y++, rgba_from_rgb(engine->floor));
	return (true);
}
