#ifndef PARSER_H
# define PARSER_H

# include "stdlib.h"

/*
 * Norminette does not like it, so I leave it here for reference.
# define TEXTURE_NO (1 << 0)
# define TEXTURE_EA (1 << 1)
# define TEXTURE_SO (1 << 2)
# define TEXTURE_WE (1 << 3)
# define COLOR_FLOOR (1 << 4)
# define COLOR_CEILING (1 << 5)
# define PLAYER_FOUND (1 << 6)
# define PLAYER_SET (1 << 7)
# define ALL_SET (TEXTURE_NO | TEXTURE_EA | TEXTURE_SO \
    | TEXTURE_WE | COLOR_FLOOR | COLOR_CEILING)
 */

typedef struct s_engine	t_engine;

/*
 * Main parser function. Contains all steps to parse file.
 * Returns 1 on failure, 0 on sucess.
 */
int		parser(t_engine *engine, char *filename);

/*
 * Checks every lines till it gets all textures and colors requried from map.
 * Checks engine->flags, if every config was parsed.
 * It uses first 6 bits of flags.
 * On error returns 1, 0 on success.
 */
int		process_config(t_engine *engine, int fd);

/*
 * Process map, after skipping empty lines after last config line.
 * Use strucutre to keep all variables.
 * Returns 1 on failure, 0 on sucess.
 */
int		process_map(t_engine *engine, int fd);

/*
 * Ckeck map with DFS. Also assign width of map.
 * Returns 1 on failure, 0 on sucess.
 */
bool	check_map(t_engine *engine);

// Extract functions

/*
 * Save texture path to line, skipping whitespaces characters, and saving
 * it to engine structure.
 * Returns 1 on failure, 0 on sucess.
 */
int		extract_texture(t_engine *engine, char *line, char *dir);

/*
 * Save color RGB, value between 0 and 255, and save it.
 * Returns 1 on failure, 0 on sucess.
 */
int		extract_colors(t_engine *engine, char *line, char **id, size_t i);

// Utils
void	trim_new_line(char **line, size_t length);
#endif
