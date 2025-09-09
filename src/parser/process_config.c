#include "../../include/cub3d.h"

static int	process_line(t_engine *engine, char *line);
static int	determine_cardinal_point(t_engine *engine, char *line, char **dir);
static int	check_set(t_engine *engine, char *line);

/*
 * Checks every lines till it gets all textures and colors requried from map.
 * Checks engine->flags, first 6 bits.
 * On error returns 1, 0 on success.
 */

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
			exit_status = check_set(engine, line);
		}
		free(line);
		if ((engine->flags & ALL_SET) == ALL_SET)
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
	if ((engine->flags & ALL_SET) != ALL_SET)
		exit_status = process_line(engine, line);
	return (exit_status);
}

/*
 * Going throught line, checks if it is texture or colour.
 * Returns 0 on success, 1 on error.
 */

static int	process_line(t_engine *engine, char *line) // TODO more than 25 lines
{
	char	*ptr;
	char	*tmp;
	size_t	i;

	ptr = line;
	i = 0;
	tmp = malloc(3);
	if (!tmp)
		return (1);
	while (*ptr)
	{
		if (!ft_isspace(*ptr))
			tmp[i++] = *ptr;
		ptr++;
		if (i == 1 && (tmp[0] == 'F' || tmp[0] == 'C'))
		{
			if (extract_colors(engine, ptr, &tmp, i))
				return (free(tmp), 1);
			break ;
		}
		if (i == 2)
		{
			tmp[i] = '\0';
			if (determine_cardinal_point(engine, ptr, &tmp))
				return (free(tmp), 1);
			break ;
		}
	}
	free(tmp);
	return (0);
}

/*
 * Checks for what direction the texture should be.
 * Also setting texture flag and checking if it was set before.
 * Returns 0 on success, 1 on fail.
 */

static int	determine_cardinal_point(t_engine *engine, char *line, char **dir) //TODO more than 25 lines, maybe do hash tables?
{
	int	exit_status;

	exit_status = 1;
	if (ft_strcmp(*dir, "NO") == 0)
	{
		if (engine->flags & TEXTURE_NO)
			return (1);
		exit_status = extract_texture(engine, line, "NO");
		engine->flags |= TEXTURE_NO;
	}
	else if (ft_strcmp(*dir, "EA") == 0)
	{
		if (engine->flags & TEXTURE_EA)
			return (1);
		exit_status = extract_texture(engine, line, "EA");
		engine->flags |= TEXTURE_EA;
	}
	else if (ft_strcmp(*dir, "SO") == 0)
	{
		if (engine->flags & TEXTURE_SO)
			return (1);
		exit_status = extract_texture(engine, line, "SO");
		engine->flags |= TEXTURE_SO;
	}
	else if (ft_strcmp(*dir, "WE") == 0)
	{
		if (engine->flags & TEXTURE_WE)
			return (1);
		exit_status = extract_texture(engine, line, "WE");
		engine->flags |= TEXTURE_WE;
	}
	dir = NULL;
	return (exit_status);
}
