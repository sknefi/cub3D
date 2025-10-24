#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

void			init_ray(t_ray *ray, t_engine *engine, int x);
bool			trace_ray(t_ray *ray, t_engine *engine);
uint32_t		get_wall_color(t_ray *ray, mlx_texture_t *texture,
					int tex_x, int tex_y);
mlx_texture_t	*get_texture_for_ray(t_engine *engine, t_ray *ray);
bool			draw_scene(t_engine *engine, int x, t_ray *ray);
bool			raycast_scene(t_engine *engine);
char			get_tile_in_raycast(t_engine *engine, int x, int y);	
void			init_ray_helper(t_ray *ray, t_engine *engine, int x);
void			calculate_distance_of_ray(t_ray *ray);

#endif
