#include "../MLX42/include/MLX42/MLX42.h"

#include <stdlib.h>

typedef struct s_player	t_player;

typedef struct	s_engine
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
}	t_engine;

typedef struct	s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}	t_player;
