#include "../../include/cub3d.h"

void	trim_new_line(char **line, size_t length)
{
	if ((*line)[length - 1] == '\n')
		(*line)[length - 1] = '\0';
}

void	free_split(char **rgb)
{
	size_t	i;

	if (!rgb)
		return ;
	i = 0;
	while(rgb[i])
		free(rgb[i++]);
	free(rgb);
}
