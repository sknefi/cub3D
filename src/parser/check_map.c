#include "../../include/cub3d.h"
#include <stdio.h>

static void	get_map_width(t_engine *engine);
static bool	validate_map(t_engine *engine);
static bool	flags_and_stack(t_engine *engine, t_position **stack, uint8_t **map_flags);

bool	check_map(t_engine *engine)
{
	get_map_width(engine);
	if (!validate_map(engine))
		return (false);
	return (true);
}

// Obtain the width of map, by calculating the widest row.

static void	get_map_width(t_engine *engine)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	len = 0;
	while (engine->map->map[i])
	{
		len = ft_strlen(engine->map->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	engine->map->width = max;
}

/*
 * Validate map, by checking if it is closed by walls (1).
 * Uses DFS and stack.
 * It is saving memory by having flags set/check bit for visited square.
 * Return true on success, otherwise false.
 */

static bool	validate_map(t_engine *engine)
{
	t_position	*stack;
	t_position	current;
	uint8_t		*map_flags;
	int			index;
	int			i;

	if (!flags_and_stack(engine, &stack, &map_flags))
		return (false);
	i = 0;
	stack[i++] = (t_position){engine->player->x, engine->player->y};
	current = stack[i - 1];
	while (i > 0)
	{
		current = stack[--i];
		if (current.x < 0 || current.y < 0 || current.x > (int)engine->map->width || current.y > (int)engine->map->height)
			return (free(stack), free(map_flags), false);
		if (engine->map->map[current.y][current.x] == ' ')
			return (free(stack), free(map_flags), false);
		if (engine->map->map[current.y][current.x] == '1')
			continue ;
		index = current.x * engine->map->height + current.y;
		if ((map_flags[index / 8] >> (index % 8)) & 1)
			continue ;
		map_flags[index / 8] |= (1 << (index % 8));
		stack[i++] = (t_position){current.x, current.y + 1};
		stack[i++] = (t_position){current.x + 1, current.y};
		stack[i++] = (t_position){current.x, current.y - 1};
		stack[i++] = (t_position){current.x - 1, current.y};
	}
	free(map_flags);
	free(stack);
	return (true);
}

/*
 * Function that prepares stack and flags for checking map.
 * Takes addresses from validate_map().
 * Allocates memory for stack and flags.
 * @size: need to allocate whole bytes, so + 7 ensures that it will be whole bit, becasue dividing by 8 can cound size to smaller size than needed.
 * Return true on success, otherwise false
 */

static bool	flags_and_stack(t_engine *engine, t_position **stack, uint8_t **map_flags)
{
	size_t	size;

	size = ((engine->map->width * engine->map->height) + 7) / 8;
	*map_flags = malloc(size);
	if (!(*map_flags))
		return (false);
	ft_memset(*map_flags, 0, size);
	*stack = malloc(sizeof(t_position) * (engine->map->height * engine->map->width));
	if (!(*stack))
	{
		free(*map_flags);
		return (false);
	}
	return (true);
}
