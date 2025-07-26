#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_rgb	t_rgb;

typedef struct	s_engine
{
	mlx_t			*mlx;
	mlx_image_t		*img[4];
	char			*textures[4];
	t_rgb			*floor;
	t_rgb			*ceiling;
	uint8_t			flags;
	t_map			*map;
	char			**map_copy;
	t_player		*player;
	bool			player_found;
}	t_engine;

typedef struct	s_map
{
	char		**map;
	uint32_t	height;
	uint32_t	width;
}	t_map;

typedef struct	s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}	t_player;

typedef struct	s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

