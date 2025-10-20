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
	t_parser_config	storage;

	if (prepare_parser_values(&storage, line))
		return (1);
	while (*storage.ptr)
	{
		if (!ft_isspace(*storage.ptr))
			storage.tmp[storage.i++] = *storage.ptr;
		storage.ptr++;
		if (storage.i == 1 && (storage.tmp[0] == 'F' || storage.tmp[0] == 'C'))
		{
			if (extract_colors(engine, storage.ptr, &storage.tmp, storage.i))
				return (free(storage.tmp), 1);
			break ;
		}
		if (storage.i == 2)
		{
			storage.tmp[storage.i] = '\0';
			if (determine_direction(engine, storage.ptr, &storage.tmp))
				return (free(storage.tmp), 1);
			break ;
		}
	}
	free(storage.tmp);
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
