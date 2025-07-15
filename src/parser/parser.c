#include "../../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

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

static int	determine_cardinal_point(t_engine *engine, char *line, size_t *j)
{
	(void)engine;
	(void)j;
	if (ft_strcmp(line, "NO") == 0)
		return (printf("yes, yes!\n"), 0);
	else if (ft_strcmp(line, "EA") == 0)
		printf("b\n");
	else if (ft_strcmp(line, "SO") == 0)
		printf("c\n");
	else if (ft_strcmp(line, "WE") == 0)
		printf("d\n");
	return (1);
}

static int	process_line(t_engine *engine, char *line, size_t length)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = malloc(length);
	if (!tmp)
		return (1);
	while(line[i])
	{
		if (!ft_isspace(line[i]))
			tmp[j++] = line[i];
		if (j == 2)
		{
			tmp[j] = '\0';
			if (determine_cardinal_point(engine, tmp, &j))
				return (free(tmp), 1);
			break ;
		}
		i++;
	}
	free(tmp);
	return (0);
}

static void	trim_new_line(char **line, size_t length)
{
	if ((*line)[length - 1] == '\n')
		(*line)[length - 1] = '\0';
}

static int	check_textures(t_engine *engine, int fd)
{
	char	*line;
	size_t	length;

	line = get_next_line(fd);
	length = 0;
	while(line)
	{
		length = ft_strlen(line);
		trim_new_line(&line, length);
		if (process_line(engine, line, length))
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
