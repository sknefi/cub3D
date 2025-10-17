#include "../../include/cub3d.h"

static void	process_input(t_engine *engine)
{
	double	move_speed;
	double	rot_speed;
	double	perp_x;
	double	perp_y;

	if (!engine || !engine->mlx || !engine->player)
		return ;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(engine->mlx);
		return ;
	}
	move_speed = engine->player->move_speed;
	rot_speed = engine->player->rotation_speed;
	perp_x = -engine->player->dy;
	perp_y = engine->player->dx;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		move_player(engine, engine->player->dx * move_speed, engine->player->dy * move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
		move_player(engine, -engine->player->dx * move_speed, -engine->player->dy * move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
		move_player(engine, perp_x * move_speed, perp_y * move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
		move_player(engine, -perp_x * move_speed, -perp_y * move_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT))
		rotate_player(engine->player, -rot_speed);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_RIGHT))
		rotate_player(engine->player, rot_speed);
}

static void	render_loop(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (!engine || !engine->frame)
		return ;
	process_input(engine);
	raycast_scene(engine);
}

bool	start_game(t_engine *engine)
{
	if (!engine)
		return (false);
	engine->mlx = mlx_init(WIN_W, WIN_H, "cub3d", false);
	if (!engine->mlx)
		return (false);
	engine->frame = mlx_new_image(engine->mlx, WIN_W, WIN_H);
	if (!engine->frame)
		return (mlx_terminate(engine->mlx), engine->mlx = NULL, false);
	if (mlx_image_to_window(engine->mlx, engine->frame, 0, 0) < 0)
	{
		mlx_delete_image(engine->mlx, engine->frame);
		engine->frame = NULL;
		mlx_terminate(engine->mlx);
		engine->mlx = NULL;
		return (false);
	}
	mlx_loop_hook(engine->mlx, render_loop, engine);
	return (true);
}
