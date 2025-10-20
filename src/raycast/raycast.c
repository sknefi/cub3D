#include "../../include/cub3d.h"

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
