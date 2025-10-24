#include "../../include/cub3d.h"

#define COLLISION_MARGIN 0.2

static void	init_player(t_engine *engine, char direction)
{
	engine->player->direction = direction;
	if (direction == 'N')
	{
		engine->player->dx = 0;
		engine->player->dy = -1;
	}
	else if (direction == 'S')
	{
		engine->player->dx = 0;
		engine->player->dy = 1;
	}
	else if (direction == 'E')
	{
		engine->player->dx = 1;
		engine->player->dy = 0;
	}
	else if (direction == 'W')
	{
		engine->player->dx = -1;
		engine->player->dy = 0;
	}
	engine->player->plane_x = -engine->player->dy * 0.66;
	engine->player->plane_y = engine->player->dx * 0.66;
	engine->player->move_speed = 0.02;
	engine->player->rotation_speed = 0.02;
}

int	create_player(t_engine *engine)
{
	uint32_t	y;
	uint32_t	x;
	char		tile;

	if (!engine || !engine->map || !engine->map->map)
		return (1);
	y = 0;
	while (engine->map->map[y])
	{
		x = 0;
		while (engine->map->map[y][x])
		{
			tile = engine->map->map[y][x];
			if (ft_strchr("NESW", tile))
			{
				init_player(engine, tile);
				engine->map->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
