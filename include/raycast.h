#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

void		init_ray(t_ray *ray, t_engine *engine, int x);
bool		trace_ray(t_ray *ray, t_engine *engine);
uint32_t	get_wall_color(t_ray *ray, mlx_texture_t *texture,
						int tex_x, int tex_y);
mlx_texture_t	*get_texture_for_ray(t_engine *engine, t_ray *ray);
void		draw_column(t_engine *engine, int x, t_ray *ray);
void		raycast_scene(t_engine *engine);

#endif
