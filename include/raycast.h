#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	distance;
}	t_ray;

void	raycast_scene(t_engine *engine);

#endif
