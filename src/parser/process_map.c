#include "../../include/cub3d.h"

int process_map(t_engine *engine, int fd)
{
    char	*line;
    (void)engine;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("HERE SHOULD BE MAP PARSER\n");
	return (0);
}
