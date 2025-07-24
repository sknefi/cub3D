#include "../../include/cub3d.h"

static void	skip_empty_line(char **line, int fd);

int process_map(t_engine *engine, int fd)
{
    char	*line;
	line = get_next_line(fd);
	skip_empty_line(&line, fd);
	//printf("%s", line); //DEBUG printf TODO
	while (line)
	{
		//printf("%s\n", line); //DEBUG printf TODO
		//validate_map(engine, line);
		engine->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	//printf("HERE SHOULD BE MAP PARSER\n"); //DEBUG printf TODO
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
