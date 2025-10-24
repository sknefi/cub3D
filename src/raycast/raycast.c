/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:30:29 by fkarika           #+#    #+#             */
/*   Updated: 2025/10/24 16:30:30 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	raycast_scene(t_engine *engine)
{
	int		x;
	t_ray	ray;

	if (!engine || !engine->frame)
		return (false);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(&ray, engine, x);
		if (trace_ray(&ray, engine))
		{
			if (!draw_scene(engine, x, &ray))
				return (false);
		}
		x++;
	}
	return (true);
}
