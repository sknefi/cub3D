#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../tym_libft/libft.h"

# include "structs.h"
# include "enums.h"
# include "parser.h"

# define WIN_H 800
# define WIN_W 600

bool	init_engine(t_engine **engine);
int		ft_isspace(char c);

// Cleaner
void	free_struct(t_engine *engine);

#endif
