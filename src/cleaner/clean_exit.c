#include "../../include/cub3d.h"

void	free_struct(t_engine *engine)
{
	if (engine->mlx)
		free(engine->mlx);
	if (engine->ceiling)
		free(engine->ceiling);
	if (engine->floor)
		free(engine->floor);
	for (int i = 0; i < 4; i++)
	{
		if (engine->textures[i])
			free(engine->textures[i]);
	}
	if (engine)
		free(engine);
}
