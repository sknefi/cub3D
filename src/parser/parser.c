#include "../../include/cub3d.h"

static int	check_extension(char *filename);
static int	check_textures(t_engine *engine, int fd);

int	parser(t_engine *engine, char *filename)
{
	int	fd;
	(void)engine;
	if (check_extension(filename))
		return (printf("Error\nWrong extension\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), 1);
	if (check_textures(engine, fd))
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

static int	process_line(t_engine *engine, char *line)
{
	
}

static int	check_textures(t_engine *engine, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while(line)
	{
		if (process_line(engine, line))
			return (1);
	}
	return (0);
}
