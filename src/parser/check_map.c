#include "../../include/cub3d.h"
#include <stdio.h>

static void	get_map_width(t_engine *engine);
static bool	validate_map(t_engine *engine);
//static bool	closed_map(t_engine *engine);
//static bool	valid_path(t_engine *engine);

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
	while (engine->map_copy[i])
	{
		len = ft_strlen(engine->map_copy[i]);
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
	int	i;

	printf("%f\n", engine->player->y);
	printf("I am here\n");
	stack = malloc(sizeof(t_position) * (engine->map->height * engine->map->width));
	if (!stack)
		return (false); // Need to add error message, that to big map
	i = 0;
	stack[i++] = (t_position){engine->player->x, engine->player->y};
	current = stack[i - 1];
	while (i > 0)
	{
		current = stack[--i];
		if (current.x < 0 || current.y < 0 || current.x > (int)engine->map->width || current.y > (int)engine->map->height)
			return (free(stack), false);
		// pop node
		if (engine->map_copy[current.y][current.x] == ' ')
			return (free(stack), false); // error, map is not closed
		if (engine->map_copy[current.y][current.x] == '1')
			continue ;
		engine->map_copy[current.y][current.x] = '1';
		stack[i++] = (t_position){current.x, current.y + 1};
		stack[i++] = (t_position){current.x + 1, current.y};
		stack[i++] = (t_position){current.x, current.y - 1};
		stack[i++] = (t_position){current.x - 1, current.y};
		// what if it is not visited?
		// need to check for 1, 0, ' ', etc.
		// go to each node on up, right, down and left
		
	}
	// BFS with queue and maybe bitset to take less RAM?
	free(stack);
	printf("Good map mate\n");
	return (true);
}

/*
static bool	closed_map(t_engine *engine)
{

	return (true);
}

static bool	valid_path(t_engine *engine)
{
	return (true);
}
*/
