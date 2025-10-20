#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_rgb	t_rgb;

typedef struct s_engine
{
	mlx_t			*mlx;
	mlx_image_t		*img[4];
	char			*textures[4];
	t_rgb			*floor;
	t_rgb			*ceiling;
	uint8_t			flags;
	t_map			*map;
	t_player		*player;
}	t_engine;

/*
 * Used to store map, two dimentional array.
 * Also for map width and height.
 */
typedef struct s_map
{
	char		**map;
	uint32_t	height;
	uint32_t	width;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}	t_player;

/*
 * Stores red, green and blue value, from 0 - 255.
 */
typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

/*
 * Structure used in DFS, to determine postion on map.
 */
typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

/*
 * Used to store variables for map parsing.
 */
typedef struct	s_parser
{
	char	*line;
	bool	err;
	int		y;
}	t_parser;

/*
 * Used to store variables for configuration parsing.
 */
typedef struct	s_parser_config
{
	char	*ptr;
	char	*tmp;
	int		i;
}	t_parser_config;

typedef struct s_check_map_utils
{
	int	i;
	int	tmp;
}	t_check_map_utils;

