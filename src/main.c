#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_engine	*engine;

	if (argc != 2)
		return (printf("Usage: ./cub3d <path_to_map>\n"), 1);
	if (!init_engine(&engine))
		return (free_struct(engine), 1);
	if (parser(engine, argv[1]))
		return (free_struct(engine), 1);
	if (!start_game(engine))
		return (free_struct(engine), ft_error("Failed to initialise MLX"));
	mlx_loop(engine->mlx);
	mlx_terminate(engine->mlx);
	engine->mlx = NULL;
	engine->frame = NULL;
	free_struct(engine);
	return (0);
}
