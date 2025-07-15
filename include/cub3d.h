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
# include "../libft_divinus/libft.h"

# include "structs.h"
# include "enums.h"
# include "parser.h"

# define WIN_H 800
# define WIN_W 600

void	game_init(t_engine *engine);
int		ft_isspace(char c);

#endif
