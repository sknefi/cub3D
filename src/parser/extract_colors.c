#include "../../include/cub3d.h"

static int	extract_color(t_engine *engine, char *line, t_color_types type);
static bool	check_rgb(char **rgb);
static bool	check_overflow(char *color);
static bool	save_rgb(t_engine *engine, char **rgb, t_color_types type);

int	extract_colors(t_engine *engine, char *line, char **id, size_t i)
{
	int	exit_status;

	(void)engine;
	exit_status = 1;
	(*id)[i] = '\0';
	if (ft_strcmp(*id, "F") == 0)
	{
		if (engine->flags & COLOR_FLOOR)
			return (1);
		exit_status = extract_color(engine, line, FLOOR);
		engine->flags |= COLOR_FLOOR;
	}
	else if (ft_strcmp(*id, "C") == 0)
	{
		if (engine->flags & COLOR_CEILING)
			return (1);
		exit_status = extract_color(engine, line, CEILING);
		engine->flags |= COLOR_CEILING;
	}
	return (exit_status);
}

static int	extract_color(t_engine *engine, char *line, t_color_types type)
{
	size_t	i;
	size_t	j;
	char	**rgb;

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
	save_rgb(engine, rgb, type);
	free_split(rgb);
	return (0);
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

static bool	check_overflow(char *color)
{
	size_t	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (false);
		i++;
	}
	if (i != 3)
		return (false);
	return (true);
}

static bool	save_rgb(t_engine *engine, char **rgb, t_color_types type)
{
	size_t	i;

	i = 0;
	if (type == CEILING)
	{
		engine->ceiling->r = (uint8_t)ft_atoi(rgb[i++]);
		engine->ceiling->g = (uint8_t)ft_atoi(rgb[i++]);
		engine->ceiling->b = (uint8_t)ft_atoi(rgb[i++]);
	}
	else if (type == FLOOR)
	{
		engine->floor->r = (uint8_t)ft_atoi(rgb[i++]);
		engine->floor->g = (uint8_t)ft_atoi(rgb[i++]);
		engine->floor->b = (uint8_t)ft_atoi(rgb[i++]);
	}
	return (true);
}
