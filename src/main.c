#include "../include/cub3d.h"

static void	parser_tester(t_engine *engine);

int	main(int argc, char **argv)
{
	t_engine	*engine;

	if (argc != 2)
		return (printf("Usage: ./cub3d <path_to_map>\n"), 1);
	if (!init_engine(&engine))
		return (free_struct(engine), 1);
	if (parser(engine, argv[1]))
		return (free_struct(engine), 1);
	if (0)
		parser_tester(engine);
	// cub3d baby!!!
	ft_printf("cubenzi 3denzi\n");
	parser_tester(engine);
	free_struct(engine);	
	return (0);
}

static void	parser_tester(t_engine *engine)
{
	// TESTER
	printf("---------- Start of tester ----------\n");
	printf("Textures from file:\n");
	for (int i = 0; i < 4; i++)
		printf("%s\n", engine->textures[i]);
	printf("-------\n");
	printf("Floor colors (in rgb fomrmat):\n");
	printf("%d\n", engine->floor->r);
	printf("%d\n", engine->floor->g);
	printf("%d\n", engine->floor->b);
	printf("-------\n");
	printf("Ceiling colors (in rgb fomrmat):\n");
	printf("%d\n", engine->ceiling->r);
	printf("%d\n", engine->ceiling->g);
	printf("%d\n", engine->ceiling->b);
	printf("-------\n");
	printf("Check if flags for textures and colors are set\n");
	if ((engine->flags & ALL_SET) == ALL_SET)
		printf("Aye Capitan!\n");
	printf("-------\n");
	printf("Map height: %d\n", engine->map->height);
	printf("-------\n");
	printf("Map width: %d\n", engine->map->width);
	printf("-------\n");
	printf("Player x and y: %f and %f\n", engine->player->x, engine->player->y);
	printf("-------\n");
	printf("Map:\n");
	for (uint32_t i = 0; i < engine->map->height; i++)
		printf("%s\n", engine->map->map[i]);
	printf("---------- End of tester ----------\n");
	// END OF TESTER
}
