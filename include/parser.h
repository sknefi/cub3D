#ifndef PARSER_H
# define PARSER_H

#include "stdlib.h"

#define	TEXTURE_NO (1 << 0)
#define	TEXTURE_EA (1 << 1)
#define	TEXTURE_SO (1 << 2)
#define	TEXTURE_WE (1 << 3)
#define	COLOR_FLOOR (1 << 4)
#define	COLOR_CEILING (1 << 5)
#define PLAYER_FOUND (1 << 6)
#define PLAYER_SET (1 << 7)
#define	ALL_SET (TEXTURE_NO | TEXTURE_EA | TEXTURE_SO | TEXTURE_WE | COLOR_FLOOR | COLOR_CEILING)

typedef struct	s_engine	t_engine;

int	parser(t_engine *engine, char *filename);
int	check_lines(t_engine *engine, int fd);
int process_map(t_engine *engine, int fd);
bool	check_map(t_engine *engine);

// Extract functions
int	extract_texture(t_engine *engine, char *line, char *dir);
int	extract_colors(t_engine *engine, char *line, char **id, size_t i);

// Utils
void	trim_new_line(char **line, size_t length);
void	free_split(char **rgb);
#endif
