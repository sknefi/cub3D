#include "../../include/cub3d.h"

static t_textures_dir	get_direction(char *dir);
static int	check_extension(char *line);
static void	set_flag(t_engine *engine, char *dir);

int	extract_texture(t_engine *engine, char *line, char *dir)
{
	size_t			i;
	size_t			j;
	t_textures_dir	direction;

	i = 0;
	j = 0;
	direction = get_direction(dir);
	if (ERROR == direction)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			line[j++] = line[i];
		i++;
	}
	line[j] = '\0';
	if (check_extension(line))
		return (1);
	engine->textures[direction] = ft_strdup(line);
	if (!engine->textures[direction])
		return (1);
	set_flag(engine, dir);
	return (0);
}

/*
 * Function determines direction of texture.
 * Returns ERROR from enum on failure, direction from enum on success.
 */

static t_textures_dir	get_direction(char *dir)
{
	if (ft_strcmp(dir, "NO") == 0)
		return (NO);
	else if (ft_strcmp(dir, "EA") == 0)
		return (EA);
	else if (ft_strcmp(dir, "SO") == 0)
		return (SO);
	else if (ft_strcmp(dir, "WE") == 0)
		return (WE);
	else
		return (ERROR);
}

/*
 * Check if texture file extension is .xpm.
 * Retruns non-zero value on failure, 0 on success.
 */

static int	check_extension(char *line)
{
	size_t	len;
	char	*extension;

	len = ft_strlen(line);
	if (len >= 5)
	{
		extension = ft_strrchr(line, '.');
		return (ft_strcmp(extension, ".xpm"));
	}
	return (1);
}

/*
 * Set flag for set texture.
 */

static void	set_flag(t_engine *engine, char *dir)
{
	if (ft_strcmp(dir, "NO") == 0)
		engine->flags |= (1 << 0);
	else if (ft_strcmp(dir, "EA") == 0)
		engine->flags |= (1 << 1);
	else if (ft_strcmp(dir, "SO") == 0)
		engine->flags |= (1 << 2);
	else if (ft_strcmp(dir, "WE") == 0)
		engine->flags |= (1 << 3);
}
