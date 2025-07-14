#include "../../include/cub3d.h"

static int	check_extension(char *filename);

int	parser(t_engine *engine, char *filename)
{
	(void)engine;
	if (check_extension(filename))
		return (printf("Error\nWrong extension\n"), 1);
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
