#include "../../include/cub3d.h"

void	free_data(char **data, int i)
{
	while (i > 0)
		free(data[--i]);
	free(data);
}

void	free_struct(t_engine *engine)
{
	if (engine->mlx)
		free(engine->mlx);
	if (engine->ceiling)
		free(engine->ceiling);
	if (engine->floor)
		free(engine->floor);
	if (engine->map->map)
		free_data(engine->map->map, engine->map->height);
	if (engine->map_copy)
		free_data(engine->map_copy, engine->map->height);
	if (engine->map)
		free(engine->map);
	if (engine->player)
		free(engine->player);
	for (int i = 0; i < 4; i++)
	{
		if (engine->textures[i])
			free(engine->textures[i]);
	}
	if (engine)
		free(engine);
}
