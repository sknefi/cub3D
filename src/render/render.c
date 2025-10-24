/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:30:27 by fkarika           #+#    #+#             */
/*   Updated: 2025/10/24 16:59:01 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	process_input(t_engine *engine)
{
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(engine->mlx);
		return ;
	}
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		move_player(engine, engine->player->dx * engine->player->move_speed,
			engine->player->dy * engine->player->move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
		move_player(engine, -engine->player->dx * engine->player->move_speed,
			-engine->player->dy * engine->player->move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
		move_player(engine, -engine->player->dy * engine->player->move_speed,
			engine->player->dx * engine->player->move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
		move_player(engine, engine->player->dy * engine->player->move_speed,
			-engine->player->dx * engine->player->move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT))
		rotate_player(engine->player, -engine->player->rotation_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		rotate_player(engine->player, engine->player->rotation_speed);
}

static void	render_loop(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (!engine || !engine->frame || !engine->mlx || !engine->player)
		return ;
	process_input(engine);
	if (!raycast_scene(engine))
	{
		free_struct(engine);
		ft_error("Failed in raycasting scene");
		exit(1);
	}
}

bool	start_game(t_engine *engine)
{
	if (!engine)
		return (false);
	engine->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!engine->mlx)
		return (false);
	engine->frame = mlx_new_image(engine->mlx, WIN_W, WIN_H);
	if (!engine->frame)
		return (false);
	if (mlx_image_to_window(engine->mlx, engine->frame, 0, 0) < 0)
		return (false);
	mlx_loop_hook(engine->mlx, render_loop, engine);
	return (true);
}
