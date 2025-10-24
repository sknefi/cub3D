#include "../../include/cub3d.h"

void	free_struct(t_engine *engine)
{
	if (!engine)
		return ;
	if (engine->mlx)
	{
		if (engine->frame)
			mlx_delete_image(engine->mlx, engine->frame);
		for (int i = 0; i < 4; i++)
		{
			if (engine->img[i])
				mlx_delete_image(engine->mlx, engine->img[i]);
			if (engine->texture[i])
				mlx_delete_texture(engine->texture[i]);
		}
		mlx_terminate(engine->mlx);
		engine->mlx = NULL;
	}
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
	for (int i = 0; i < 4; i++)
	{
		if (engine->texture_path[i])
			free(engine->texture_path[i]);
	}
	free(engine);
}
