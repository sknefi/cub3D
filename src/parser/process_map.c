#include "../../include/cub3d.h"

static void	prepare_parser(t_parser *structure, int fd, char **tmp);
static void	skip_empty_line(char **line, int fd);
static int	validate_map(t_engine *engine, char *line, int y);

int	process_map(t_engine *engine, int fd)
{
	t_parser	structure;
	char		*tmp;

	prepare_parser(&structure, fd, &tmp);
	skip_empty_line(&structure.line, fd);
	while (structure.line)
	{
		if (!structure.error)
		{
			structure.error = validate_map(engine, structure.line, structure.y);
			tmp = ft_strjoin_free(tmp, structure.line);
			if (!tmp)
				return (1);
		}
		structure.y++;
		free(structure.line);
		structure.line = get_next_line(fd);
	}
	if ((engine->flags & PLAYER_SET) || !(engine->flags & PLAYER_FOUND))
		return (free(tmp), 1);
	engine->map->map = ft_split(tmp, '\n');
	if (!engine->map->map)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

static void	prepare_parser(t_parser *structure, int fd, char **tmp)
{
	structure->line = get_next_line(fd);
	structure->error = 0;
	structure->y = 0;
	*tmp = NULL;
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
	int		found;

	found = false;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NESW'\n'", line[i]))
			return (1);
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
		return (1);
	engine->map->height++;
	return (0);
}
