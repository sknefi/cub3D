#include "../../include/cub3d.h"

static void	skip_empty_line(char **line, int fd);
static int	validate_map(t_engine *engine, char *line, int y);

int	process_map(t_engine *engine, int fd) //TODO more than 25
{
	char	*line;
	char	*tmp;
	bool	error;
	int		y;

	error = 0;
	line = get_next_line(fd);
	tmp = NULL;
	y = 0;
	skip_empty_line(&line, fd);
	while (line)
	{
		if (!error)
		{
			error = validate_map(engine, line, y);
			tmp = ft_strjoin_free(tmp, line);
			if (!tmp)
				return (1);
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	if ((engine->flags & PLAYER_SET) || !(engine->flags & PLAYER_FOUND))
		return (free(tmp), 1);
	engine->map->map = ft_split(tmp, '\n');
	if (!engine->map->map)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

static void	skip_empty_line(char **line, int fd)
{
	size_t	i;

	while (*line)
	{
		i = 0;
		while ((*line)[i])
		{
			if (ft_isalnum((*line)[i]))
				return ;
			i++;
		}
		free(*line);
		*line = get_next_line(fd);
	}
	return ;
}

static int	validate_map(t_engine *engine, char *line, int y)
{
	size_t	i;
	int	found;

	found = false;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NESW'\n'", line[i]))
			return (0);
		if (ft_strchr("10", line[i]))
			found = 1;
		if (ft_strchr("NESW", line[i]))
		{
			if (engine->flags & PLAYER_FOUND)
				return (engine->flags |= PLAYER_SET, 0);
			engine->player->x = i;
			engine->player->y = y;
			engine->flags |= PLAYER_FOUND;
		}
		i++;
	}
	if (!found)
		return (0);
	engine->map->height++;
	return (1);
}
