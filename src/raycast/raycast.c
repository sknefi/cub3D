#include "../../include/cub3d.h"

bool	raycast_scene(t_engine *engine)
{
	int		x;
	t_ray	ray;

	if (!engine || !engine->frame)
		return (false);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(&ray, engine, x);
		if (trace_ray(&ray, engine))
		{
			if (!draw_scene(engine, x, &ray))
				return (false);
		}
		x++;
	}
	return (true);
}
