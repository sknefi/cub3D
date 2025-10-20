#include "../../include/cub3d.h"

static void	prepare_parser(t_parser_map *structure, int fd, char **tmp);
static void	skip_empty_line(char **line, int fd);
static int	validate_map(t_engine *engine, char *line, int y);

int	process_map(t_engine *engine, int fd)
{
	t_parser_map	utils;
	char		*tmp;

	prepare_parser(&utils, fd, &tmp);
	skip_empty_line(&utils.line, fd);
	while (utils.line)
	{
		if (!utils.err)
		{
			utils.err = validate_map(engine, utils.line, utils.y);
			tmp = ft_strjoin_free(tmp, utils.line);
			if (!tmp)
				return (1);
		}
		utils.y++;
		free(utils.line);
		utils.line = get_next_line(fd);
	}
	if ((engine->flags & (1 << 7)) || !(engine->flags & (1 << 6)) || utils.err)
		return (free(tmp), 1);
	engine->map->map = ft_split(tmp, '\n');
	if (!engine->map->map)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

/*
 * Prepares strucutre that holds variables for parsing map.
 */

static void	prepare_parser(t_parser_map *structure, int fd, char **tmp)
{
	structure->line = get_next_line(fd);
	structure->err = 0;
	structure->y = 0;
	*tmp = NULL;
}

/*
 * Skip lines between last config line and first line of map.
 */

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

/*
 * Check map line, if it contains onyl valid char.
 * Returns 1 on failure, 0 on success.
 */

static int	validate_map(t_engine *engine, char *line, int y)
{
	size_t	i;
	int		found;

	found = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NESW'\n'", line[i]))
			return (1);
		if (ft_strchr("10", line[i]))
			found = 1;
		if (ft_strchr("NESW", line[i]))
		{
			if (engine->flags & (1 << 6))
				return (engine->flags |= (1 << 7), 0);
			engine->player->x = i;
			engine->player->y = y;
			engine->flags |= (1 << 6);
		}
		i++;
	}
	if (!found)
		return (1);
	engine->map->height++;
	return (0);
}
