#include "../../include/cub3d.h"

#define COLLISION_MARGIN 0.2

static char	get_tile(t_engine *engine, int x, int y);
static bool	can_move_x(t_engine *engine, double new_x, double current_y, double delta);
static bool	can_move_y(t_engine *engine, double current_x, double new_y, double delta);

bool	create_player(t_engine *engine)
{
	uint32_t	y;
	uint32_t	x;
	char		tile;

	if (!engine || !engine->map || !engine->map->map)
		return (false);
	y = 0;
	while (engine->map->map[y])
	{
		x = 0;
		while (engine->map->map[y][x])
		{
			tile = engine->map->map[y][x];
			if (ft_strchr("NESW", tile))
			{
				engine->player->x = (double)x + 0.5;
				engine->player->y = (double)y + 0.5;
				init_player(engine, tile);
				engine->map->map[y][x] = '0';
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	move_player(t_engine *engine, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	if (!engine || !engine->player)
		return ;
	new_x = engine->player->x + move_x;
	new_y = engine->player->y + move_y;
	if (can_move_x(engine, new_x, engine->player->y, move_x))
		engine->player->x = new_x;
	if (can_move_y(engine, engine->player->x, new_y, move_y))
		engine->player->y = new_y;
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!player)
		return ;
	old_dir_x = player->dx;
	old_plane_x = player->plane_x;
	player->dx = player->dx * cos(angle) - player->dy * sin(angle);
	player->dy = old_dir_x * sin(angle) + player->dy * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

static bool	can_move_x(t_engine *engine, double new_x, double current_y, double delta)
{
	double	offset;

	if (!engine || !engine->map || !engine->map->map)
		return (false);
	offset = 0;
	if (delta > 0)
		offset = COLLISION_MARGIN;
	else if (delta < 0)
		offset = -COLLISION_MARGIN;
	if (get_tile(engine, (int)floor(new_x + offset), (int)floor(current_y)) == '0')
		return (true);
	return (false);
}

static bool	can_move_y(t_engine *engine, double current_x, double new_y, double delta)
{
	double	offset;

	if (!engine || !engine->map || !engine->map->map)
		return (false);
	offset = 0;
	if (delta > 0)
		offset = COLLISION_MARGIN;
	else if (delta < 0)
		offset = -COLLISION_MARGIN;
	if (get_tile(engine, (int)floor(current_x), (int)floor(new_y + offset)) == '0')
		return (true);
	return (false);
}

static char	get_tile(t_engine *engine, int x, int y)
{
	size_t	len;

	if (!engine || !engine->map || !engine->map->map)
		return ('1');
	if (y < 0 || y >= (int)engine->map->height)
		return ('1');
	len = ft_strlen(engine->map->map[y]);
	if (x < 0 || x >= (int)len)
		return ('1');
	return (engine->map->map[y][x]);
}
