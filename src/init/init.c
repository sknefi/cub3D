/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmateja <tmateja@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:36:08 by tmateja           #+#    #+#             */
/*   Updated: 2025/10/24 16:36:09 by tmateja          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	init_engine(t_engine **engine)
{
	*engine = ft_calloc(1, sizeof(t_engine));
	if (!(*engine))
		return (false);
	(*engine)->ceiling = ft_calloc(1, sizeof(t_rgb));
	(*engine)->floor = ft_calloc(1, sizeof(t_rgb));
	(*engine)->map = ft_calloc(1, sizeof(t_map));
	(*engine)->player = ft_calloc(1, sizeof(t_player));
	if (!(*engine)->ceiling || !(*engine)->floor || !(*engine)->map
		|| !(*engine)->ceiling)
		return (false);
	return (true);
}
