/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:35:30 by tmateja           #+#    #+#             */
/*   Updated: 2025/10/24 16:35:31 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	extract_color(t_engine *engine, char *line, t_color_types type);
static bool	check_rgb(char **rgb);
static bool	check_overflow(char *color);
static bool	save_rgb(t_engine *engine, char **rgb, t_color_types type);

int	extract_colors(t_engine *engine, char *line, char **id, size_t i)
{
	int	exit_status;

	exit_status = 1;
	(*id)[i] = '\0';
	if (ft_strcmp(*id, "F") == 0)
	{
		if (engine->flags & (1 << 4))
			return (1);
		exit_status = extract_color(engine, line, FLOOR);
		if (!exit_status)
			engine->flags |= (1 << 4);
	}
	else if (ft_strcmp(*id, "C") == 0)
	{
		if (engine->flags & (1 << 5))
			return (1);
		exit_status = extract_color(engine, line, CEILING);
		if (!exit_status)
			engine->flags |= (1 << 5);
	}
	return (exit_status);
}

/*
 * Function that extract RGB color from line;
 * Return 0 on success, otherwise 1.
 */

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

/*
 * Function that check RGBs.
 */

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
	if (i != 3)
		return (false);
	return (true);
}

/*
 * Function checks if @color has less than 3 digit.
 * Returns 1 on failure, 0 on success.
 */

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
	if (i > 3)
		return (false);
	return (true);
}

/*
 * Function saves rhb in struct.
 */

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
