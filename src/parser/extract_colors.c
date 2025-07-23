#include "../../include/cub3d.h"

static int	extract_color(t_engine *engine, char *line);

int	extract_colors(t_engine *engine, char *line, char **id, size_t i)
{
	int	exit_status;

	(void)engine;
	exit_status = 1;
	(*id)[i] = '\0';
	if (ft_strcmp(*id, "F") == 0)
	{
		exit_status = extract_color(engine, line);
	}
	else if (ft_strcmp(*id, "C") == 0)
	{
		exit_status = extract_color(engine, line);
	}
	return (exit_status);
}

//TODO
static bool	check_overflow(char *color)
{
	(void)color;
	return (true);
}

static bool	check_rgb(char **rgb)
{
	size_t	i;
	int		value;

	i = 0;
	while (rgb[i])
	{
		if (!check_overflow(rgb[i]))
			return (false);
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (false);
		i++;
	}
	return (true);
}

static int	extract_color(t_engine *engine, char *line)
{
	size_t	i;
	size_t	j;
	char	**rgb;

	(void)engine;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			line[j++] = line[i];
		i++;
	}
	line[j] = '\0';
	rgb = ft_split(line, ',');
	if (NULL == rgb)
		return (1);
	if (!check_rgb(rgb))
		return (free_split(rgb), 1);
	// save_rgb(rgb);
	for (int z = 0; z < 3; z++)
	{
		if (rgb[z])
			printf("%s\n", rgb[z]);
	}
	printf("%s\n", line);
	free_split(rgb);
	return (0);
}
