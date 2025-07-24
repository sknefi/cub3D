#include "../include/cub3d.h"

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
	for (int i = 0; i < 4; i++)
		printf("%s\n", engine->textures[i]);
	printf("%d\n", engine->floor->b);
	if ((engine->flags & ALL_SET) == ALL_SET)
		printf("HI!\n");

	// cub3d baby!!!
	ft_printf("cubenzi 3denzi\n");
	free_struct(engine);	
	return (0);
}
