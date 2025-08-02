#include "../../include/cub3d.h"
#include <stdio.h>

static void	get_map_width(t_engine *engine);
static bool	validate_map(t_engine *engine);
static bool	flags_and_stack(t_engine *engine, t_position **stack, uint8_t **map_flags);

bool	check_map(t_engine *engine)
{
	get_map_width(engine);
	// Should I check for width = 1? or even 2	
	if (!validate_map(engine))
		return (false);
	/* I think doing one algorithm for checking map will be more efficient
	if (!closed_map(engine))
		return (1);
	if (!valid_path(engine))
		return (1);
	*/
	return (true);
}

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
			return (free(stack), free(map_flags), false); // error, map is not closed
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
	//for (int i = 0; (uint32_t)i < (((engine->map->width * engine->map->height) + 7 ) / 8) ; i++)
	//	free(map_flags);
	printf("freeing %p\n", (void *)map_flags);
	free(map_flags);
	free(stack);
	return (true);
}

static bool	flags_and_stack(t_engine *engine, t_position **stack, uint8_t **map_flags)
{
	size_t	size;

	size = ((engine->map->width * engine->map->height) + 7) / 8;
	*map_flags = malloc(size);
	if (!(*map_flags))
		return (false); // error message, map too big
	printf("malloc at %p\n", (void *)*map_flags);
	ft_memset(*map_flags, 0, size);
	*stack = malloc(sizeof(t_position) * (engine->map->height * engine->map->width));
	if (!(*stack))
	{
		free(*map_flags);
		return (false); // Need to add error message, that to big map
	}
	return (true);
}
