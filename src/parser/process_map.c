#include "../../include/cub3d.h"

static void	skip_empty_line(char **line, int fd);
static bool	validate_map(t_engine *engine, char *line);

int process_map(t_engine *engine, int fd)
{
	char	*line;
	char	*tmp;
	bool	error;

	engine->player_found = false;
	error = false;
	line = get_next_line(fd);
	tmp = NULL;
	skip_empty_line(&line, fd);
	//printf("%s", line); //DEBUG printf TODO
	while (line)
	{
		//printf("%s\n", line); //DEBUG printf TODO
		if (!error)
		{
			error = validate_map(engine, line);
			tmp = ft_strjoin_free(tmp, line);
			if (!tmp)
				return (1);
			printf("%s", line);
			engine->map->height++;
		}

		free(line);
		line = get_next_line(fd);
	}
	if (!engine->player_found)
		return (free(tmp), 1); // TODO error player not found
	engine->map->map = ft_split(tmp, '\n');
	engine->map_copy = ft_split(tmp, '\n');
	if (!engine->map->map || !engine->map_copy)
		return (free(tmp), 1);
	free(tmp);
	printf("HERE SHOULD BE MAP PARSER\n"); //DEBUG printf TODO
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

static bool	validate_map(t_engine *engine, char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NESW'\n'", line[i]))
			return (true);
		if (ft_strchr("NESW", line[i]))
		{
			printf("%c", line[i]);
			if (engine->player_found)
				return (true);
			engine->player_found = true;
			printf("Player found!\n");
		}
		i++;
	}
	return (false);
}
