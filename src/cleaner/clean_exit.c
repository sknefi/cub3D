#include "../../include/cub3d.h"

static void	free_texture_path(t_engine *engine);

void	free_struct(t_engine *engine)
{
	if (engine->mlx)
		free(engine->mlx);
	if (engine->ceiling)
		free(engine->ceiling);
	if (engine->floor)
		free(engine->floor);
	if (engine->map)
	{
		if (engine->map->map)
			ft_free_i_data(engine->map->map, engine->map->height);
		free(engine->map);
	}
	if (engine->player)
		free(engine->player);
	free_texture_path(engine);
	if (engine)
		free(engine);
}

static void	free_texture_path(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (engine->texture_path[i])
			free(engine->texture_path[i]);
		i++;
	}
}
