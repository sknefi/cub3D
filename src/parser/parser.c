#include "../../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_extension(char *filename);

int	parser(t_engine *engine, char *filename)
{
	int	fd;

	// TODO check if fail
	engine->ceiling = ft_calloc(1, sizeof(t_rgb));
	engine->floor = ft_calloc(1, sizeof(t_rgb));
	engine->map = ft_calloc(1, sizeof(t_map));
	engine->player = ft_calloc(1, sizeof(t_player));
	if (check_extension(filename))
		return (printf("Error\nWrong extension\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), 1);
	if (check_lines(engine, fd))
		return (printf("Error\nIssue with textures\n"), close(fd), 1);
	if (process_map(engine, fd))
		return (printf("Error with parsing map\n"), close(fd), 1);
	close(fd);
	if (!check_map(engine))
		return (1);
	ft_printf("one day it will parse something\n");
	return (0);
}

static int	check_extension(char *filename)
{
	size_t	len;
	char	*extension;

	len = ft_strlen(filename);
	if (len >= 5)
	{
		extension = ft_strrchr(filename, '.');
		return (ft_strcmp(extension, ".cub"));
	}
	return (1);
}
