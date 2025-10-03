#include "../../include/cub3d.h"

static int	check_extension(char *filename);

int	parser(t_engine *engine, char *filename)
{
	int	fd;

	if (check_extension(filename))
		return (ft_error("Wrong extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), 1);
	if (process_config(engine, fd))
		return (close(fd), ft_error("Issue with textures"));
	if (process_map(engine, fd))
		return (close(fd), ft_error("Error with parsing map"));
	close(fd);
	if (!check_map(engine))
		return (ft_error("Strange map"));
	return (0);
}

/*
 * Function checks for file extension (.cub).
 * Returns non-zero value on failure, 0 on success.
 */

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
