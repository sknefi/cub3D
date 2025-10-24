/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:31:08 by fkarika           #+#    #+#             */
/*   Updated: 2025/10/24 16:31:09 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

int		create_player(t_engine *engine);
void	move_player(t_engine *engine, double move_x, double move_y);
void	rotate_player(t_player *player, double angle);

#endif
