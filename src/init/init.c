#include "../../include/cub3d.h"

bool	init_engine(t_engine **engine)
{
	*engine = ft_calloc(1, sizeof(t_engine));
	if (!(*engine))
		return (false);
	(*engine)->ceiling = ft_calloc(1, sizeof(t_rgb));
	(*engine)->floor = ft_calloc(1, sizeof(t_rgb));
	(*engine)->map = ft_calloc(1, sizeof(t_map));
	(*engine)->player = ft_calloc(1, sizeof(t_player));
	if (!(*engine)->ceiling || !(*engine)->floor || !(*engine)->map \
		|| !(*engine)->ceiling)
		return (false);
	return (true);
}

void	init_player(t_engine *engine, char direction)
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
	engine->player->move_speed = 0.05;
	engine->player->rotation_speed = 0.05;
}
