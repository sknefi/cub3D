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
void	init_player(t_engine *engine, char direction);
bool	create_player(t_engine *engine);
void	move_player(t_engine *engine, double move_x, double move_y);
void	rotate_player(t_player *player, double angle);
bool	start_game(t_engine *engine);
void	raycast_scene(t_engine *engine);
uint32_t	get_ceiling_color(t_engine *engine);
uint32_t	get_floor_color(t_engine *engine);

// Cleaner
void	free_struct(t_engine *engine);
int		ft_error(char *str);

#endif
