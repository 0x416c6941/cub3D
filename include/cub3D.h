/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:56:57 by root              #+#    #+#             */
/*   Updated: 2025/01/22 21:48:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/**
 * This file contains different constants and structure definitions.
 * Thanks a lot to @3DSage. Their resources and guides were really useful!
 * Also thanks to Oceano (@suspectedoceano)
 * for showing tricks on how to work with MLX efficiently!
 */

# include <libft.h>
# include <stdbool.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
/**
 * For t_args.
 */
/* Textures and their indexes. */
# define TEXTURES_SIZE 4
# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3
/* Colors and their indexes. */
# define COLORS_SIZE 2
# define COLOR_FLOOR 0
# define COLOR_CEILING 1

/**
 * Every block's (place on map) coordinate will be 128x128 units wide.
 * All images (textures) will also be cropped
 * or extended (with black spaces) to those dimensions.
 * It's not stated in the subject, that we need to change those values
 * depending on what's set in width or height
 * after we run mlx_xpm_file_to_image().
 */
# define BLOCK_X 128
# define BLOCK_Y 128

/**
 * Values returned by cos(), sin()
 * and other trigonometric functions may be too small.
 * To fix that, we'll amplify their return values.
 */
# define TF_AMP 5

/**
 * For system crashes: malloc, write...
 */
# define FATAL_ERROR -1
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"
/* parameter which is not he map and we can't identify */
# define INV_PAR 1
/* one of parameter is duplicated */
# define DUP_PAR 2

/**
 * ----------------------------------------------------------------------------
 * Structures.
 * ----------------------------------------------------------------------------
 */
typedef struct s_rgb
{
	/* One byte for each.
		* We suppose that byte is an octet, so:
		* unsigned char b; => H(b) = [0, 255].
		*/
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	bool			setted;
}					t_rgb;

/**
 * Every node of \ref map contains a string (a row) of a map.
 * Parser will save information here.
 */
typedef struct s_args
{
	int				texture_count;
	char			*textures[TEXTURES_SIZE];
	t_rgb			colors[COLORS_SIZE];
	t_list			*map;
}					t_args;

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

/**
 * Everything here will be measured in radians.
 * \ref delta_x and \ref delta_y are required for moving.
 */
typedef struct s_angle
{
	double			angle;
	double			delta_x;
	double			delta_y;
}					t_angle;

/**
 * Mainly MLX data, but also player's position,
 * floor's and ceiling's colors, map, etc.
 */
typedef struct s_data
{
	void			*conn;
	void			*win;
	void			*textures[TEXTURES_SIZE];
	t_rgb			colors[COLORS_SIZE];
	t_list			*map;
	t_coords		player;
	t_angle			player_angle;
}					t_data;

int					ft_save_colors(char *trimmed_line, t_args *out, int id);
int					ft_save_textures(char *trimmed_line, t_args *out, int id);

/**
 * @brief  Checks if the given file is a valid .cub or .xpm file and it's
 * 	possible to open
 *
 * @param path path to file
 * @param cub true if the file should be a .cub file
 * @return int	0 in SUCCESS
 */
int					check_file(const char *path, bool cub);

#endif /* CUB3D_H */
