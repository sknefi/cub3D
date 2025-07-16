#ifndef PARSER_H
# define PARSER_H

#define	TEXTURE_NO (1 << 0)
#define	TEXTURE_EA (1 << 1)
#define	TEXTURE_SO (1 << 2)
#define	TEXTURE_WE (1 << 3)
#define	COLOR_FLOOR (1 << 4)
#define	COLOR_CEILING (1 << 5)

typedef struct	s_engine	t_engine;

int	parser(t_engine *engine, char *filename);

#endif
