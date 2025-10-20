#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

bool	create_player(t_engine *engine);
void	move_player(t_engine *engine, double move_x, double move_y);
void	rotate_player(t_player *player, double angle);

#endif
