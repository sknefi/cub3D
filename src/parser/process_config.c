/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:35:44 by tmateja           #+#    #+#             */
/*   Updated: 2025/10/24 16:35:45 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	prepare_parser_values(t_parser_config *structure, char *line);
static int	process_line(t_engine *engine, char *line);
static int	determine_direction(t_engine *engine, char *line, char **dir);
static int	check_set(t_engine *engine, char *line);

int	process_config(t_engine *engine, int fd)
{
	char	*line;
	size_t	length;
	int		exit_status;

	exit_status = 0;
	line = get_next_line(fd);
	length = 0;
	while (line)
	{
		if (!exit_status)
		{
			length = ft_strlen(line);
			trim_new_line(&line, length);
			if ((engine->flags & (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 \
				| 1 << 5)) != (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 \
				| 1 << 5))
				exit_status = check_set(engine, line);
		}
		free(line);
		if ((engine->flags & (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | \
			1 << 5)) == (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5))
			break ;
		line = get_next_line(fd);
	}
	return (exit_status);
}

// TODO erase it
static int	check_set(t_engine *engine, char *line)
{
	int	exit_status;

	exit_status = 1;
	if ((engine->flags & (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 \
		| 1 << 5)) != (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 \
			| 1 << 5))
		exit_status = process_line(engine, line);
	return (exit_status);
}

/*
 * Going throught line, checks if it is texture or colour.
 * Returns 0 on success, 1 on error.
 */

static int	process_line(t_engine *engine, char *line)
{
	t_parser_config	utils;

	if (prepare_parser_values(&utils, line))
		return (1);
	while (*utils.ptr)
	{
		if (!ft_isspace(*utils.ptr))
			utils.tmp[utils.i++] = *utils.ptr;
		utils.ptr++;
		if (utils.i == 1 && (utils.tmp[0] == 'F' || utils.tmp[0] == 'C'))
		{
			if (extract_colors(engine, utils.ptr, &utils.tmp, utils.i))
				return (free(utils.tmp), 1);
			break ;
		}
		if (utils.i == 2)
		{
			utils.tmp[utils.i] = '\0';
			if (determine_direction(engine, utils.ptr, &utils.tmp))
				return (free(utils.tmp), 1);
			break ;
		}
	}
	free(utils.tmp);
	return (0);
}

/*
 * Function that prepares structure that holds important variables
 * for parsing config.
 * Returns 1 on failure, 0 on success.
 */

static int	prepare_parser_values(t_parser_config *structure, char *line)
{
	structure->ptr = line;
	structure->i = 0;
	structure->tmp = malloc(3);
	if (!structure->tmp)
		return (1);
	return (0);
}

/*
 * Checks for what direction the texture should be.
 * Also setting texture flag and checking if it was set before.
 * Returns 0 on success, 1 on fail.
 */

static int	determine_direction(t_engine *engine, char *line, char **dir)
{
	int	exit_status;

	exit_status = 1;
	if (ft_strcmp(*dir, "NO") == 0)
		exit_status = extract_texture(engine, line, "NO");
	else if (ft_strcmp(*dir, "EA") == 0)
		exit_status = extract_texture(engine, line, "EA");
	else if (ft_strcmp(*dir, "SO") == 0)
		exit_status = extract_texture(engine, line, "SO");
	else if (ft_strcmp(*dir, "WE") == 0)
		exit_status = extract_texture(engine, line, "WE");
	dir = NULL;
	return (exit_status);
}
