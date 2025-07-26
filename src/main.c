#include "../include/cub3d.h"

static void	tester(t_engine *engine);

int	main(int argc, char **argv)
{
	t_engine	*engine;

	if (argc != 2)
		return (printf("Usage: ./cub3d <path_to_map>\n"), 1);
	engine = ft_calloc(1, sizeof(t_engine));
	if (!engine)
		return (printf("Error\nCalloc error\n"), 1);
	if (parser(engine, argv[1]))
		return (free_struct(engine), 1);
	tester(engine);
	// cub3d baby!!!
	ft_printf("cubenzi 3denzi\n");
	free_struct(engine);	
	return (0);
}

static void	tester(t_engine *engine)
{
	// TESTER
	printf("---------- Start of tester ----------\n");
	printf("Textures\n");
	for (int i = 0; i < 4; i++)
		printf("%s\n", engine->textures[i]);
	printf("Floor blue color\n");
	printf("%d\n", engine->floor->b);
	printf("Check if flag set\n");
	if ((engine->flags & ALL_SET) == ALL_SET)
		printf("HI!\n");
	printf("Map height: %d\n", engine->map->height);
	printf("Map:\n");
	for (uint32_t i = 0; i < engine->map->height; i++)
		printf("%s\n", engine->map->map[i]);
	printf("---------- End of tester ----------\n");
	// END OF TESTER
}
