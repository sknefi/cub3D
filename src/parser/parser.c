#include "../../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_extension(char *filename);
static int	check_line(t_engine *engine, int fd);

int	parser(t_engine *engine, char *filename)
{
	int	fd;
	(void)engine;
	if (check_extension(filename))
		return (printf("Error\nWrong extension\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), 1);
	if (check_lines(engine, fd))
		return (printf("Error\nIssue with textures\n"), 1);
	// check characters used in filename
	// check map
	// flood fill
	// check and fill textures and colors
	// create char	**map
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
