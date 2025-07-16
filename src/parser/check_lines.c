#include "../../include/cub3d.h"

static int	process_line(t_engine *engine, char *line, size_t length);
static int	determine_cardinal_point(t_engine *engine, char *line, char *dir);

int	check_lines(t_engine *engine, int fd)
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

static int	process_line(t_engine *engine, char *line, size_t length)
{
	char	*direction;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	direction = malloc(3);
	if (!direction)
		return (1);
	while(line[i])
	{
		if (!ft_isspace(line[i]))
			direction[j++] = line[i];
		if (direction[j] == 'F' || direction[j] == 'C')
			extract_colors(engine, line, tmp, length);
		if (j == 2)
		{
			direction[j] = '\0';
			if (determine_cardinal_point(engine, line, direction))
				return (free(direction), 1);
			break ;
		}
		i++;
	}
	free(direction);
	return (0);
}

static int	determine_cardinal_point(t_engine *engine, char *line, char *dir)
{
	int	exit_status;
	
	exit_status = 1;
	if (ft_strcmp(dir, "NO") == 0)
	{
		if (engine->flags & TEXTURE_NO)
			return (1);
		exit_status = extract_texture(engine, line, "NO");
	}
	else if (ft_strcmp(dir, "EA") == 0)
	{
		if (engine->flags & TEXTURE_EA)
			return (1);
		exit_status = extract_texture(engine, line, "EA");
	}
	else if (ft_strcmp(dir, "SO") == 0)
	{
		if (engine->flags & TEXTURE_SO)
			return (1);
		exit_status = extract_texture(engine, line, "SO");
	}
	else if (ft_strcmp(dir, "WE") == 0)
	{
		if (engine->flags & TEXTURE_WE)
			return (1);
		exit_status = extract_texture(engine, line, "WE");
	}
	return (exit_status);
}

