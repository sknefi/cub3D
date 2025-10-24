/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:30:55 by fkarika           #+#    #+#             */
/*   Updated: 2025/10/24 16:30:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "raycast.h"
# include "player.h"
# include "render.h"

# define WIN_H 1000
# define WIN_W 1000

bool	init_engine(t_engine **engine);
void	move_player(t_engine *engine, double move_x, double move_y);

// Cleaner
void	free_struct(t_engine *engine);
int		ft_error(char *str);

#endif
