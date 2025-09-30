#include "../../include/cub3d.h"

int	ft_error(char *str)
{
	if (!str)
		return 1;
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}
