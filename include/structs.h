#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_rgb	t_rgb;

typedef struct s_engine
{
	mlx_t			*mlx;
	mlx_image_t		*img[4];
	char			*texture_path[4];
	mlx_image_t		*frame;
	mlx_texture_t	*texture[4];
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

/**
 * This structure contains all information about player
 * and his movement, there are vectors for direction and plane.
 * Plane is used to calculate the FOV (plane vector is perpendicular
 * to direction vector). 
 * 
 * [x, y] is player position on map (in 2D matrix)
 * (dx, dy) is direction vector
 * (plane_x, plane_y) is plane vector 
 * 
 * @brief Player structure for player and his movement
 * @param x 				x coordinate of player on map
 * @param y 				y coordinate of player on map
 * @param dx 				x value of direction vector
 * @param dy 				y value of direction vector
 * @param plane_x 			x value of plane vector
 * @param plane_y 			y value of plane vector
 * @param move_speed 		Speed of player movement
 * @param rotation_speed 	Speed of player rotation
 * @param direction 		Direction of player (N, S, E, W)
 */
typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rotation_speed;
	char	direction;
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
typedef struct	s_process_map_utils
{
	char	*line;
	bool	err;
	int		y;
}	t_parser_map;

/*
 * Used to store variables for configuration parsing.
 */
typedef struct	s_process_config_utils
{
	char	*ptr;
	char	*tmp;
	int		i;
}	t_parser_config;

/*
 * Used to store variables for validation map
 */

typedef struct s_check_map_utils
{
	int	i;
	int	tmp;
}	t_check_map_utils;

/**
 * This structure contains all information needed for one ray in
 * the raycasting process. For each screen column, we cast a ray
 * and use DDA to efficiently find where it hits a wall.
 * 
 * How it works:
 * 1. For each screen column, we shoot one ray
 * 2. The ray's direction depends on:
 *    - Which way the player is looking
 *    - Which screen column we're drawing (left side, center, or right side)
 *    - How wide we want the player's field of view to be
 * 
 * DDA works by:
 * 1. Starting at player position in 2D matrix in [map_x, map_y]
 * 2. Following the ray by stepping through grid cells in 2D matrix
 * 3. Using side_dist and delta_dist to efficiently find the next cell boundary
 * 4. Continuing until we hit a wall
 * 
 * @brief Everything we need to know about one ray/screen column
 *
 * @param camera_x      Where on screen (-1.0 = left edge, 0 = center, 1.0 = right edge)
 * @param dir_x         X component of ray's direction vector
 * @param dir_y         Y component of ray's direction vector
 * @param map_x         Current X position in map grid (changes during DDA)
 * @param map_y         Current Y position in map grid (changes during DDA)
 * @param side_dist_x   Distance to next vertical grid line
 * @param side_dist_y   Distance to next horizontal grid line
 * @param delta_dist_x  Distance between vertical grid lines along ray
 * @param delta_dist_y  Distance between horizontal grid lines along ray
 * @param step_x        Direction to step in X (-1 for left, 1 for right)
 * @param step_y        Direction to step in Y (-1 for up, 1 for down)
 * @param side          Which wall face was hit (0: EW/vertical, 1: NS/horizontal)
 * @param distance      Perpendicular distance to wall (for wall height) 
 */
typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	distance;
}	t_ray;

typedef struct s_coloumn_info
{
	int	y;
	int	x;
	int	draw_start;
	int	draw_end;
	int	line_height;
}	t_coloumn_info;

typedef struct s_tex_state
{
	mlx_texture_t	*texture;
	int				tex_x;
	double			tex_step;
	double			tex_pos;
}	t_tex_state;
