/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:56:57 by root              #+#    #+#             */
/*   Updated: 2025/01/27 20:54:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/**
 * This file contains different constants and structure definitions.
 * Thanks a lot to @3DSage. Their resources and guides were really useful!
 * Also thanks to Oceano (@suspectedoceano)
 * for showing tricks on how to work with MLX efficiently,
 * and for Ahmed Fatir (@afatir) for showing some useful render tricks!
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
# define TEXTURES_SIZE	4
# define TEXTURE_NO		0
# define TEXTURE_SO		1
# define TEXTURE_WE		2
# define TEXTURE_EA		3
/* Colors and their indexes. */
# define COLORS_SIZE	2
# define COLOR_FLOOR	0
# define COLOR_CEILING	1

/**
 * We don't want to go through too fancy resolution,
 * otherwise performace would be bad.
 */
# define WIN_X	800
# define WIN_Y	600

/**
 * Every block's (place on map) coordinate
 * will be TILE_SIZE * TILE_SIZE untis.
 */
# define TILE_SIZE	128

/**
 * Degrees (in radians) for north, south, east and west respectively.
 */
# define UP		1.57079632679
# define DOWN	4.71238898038
# define RIGHT	6.28318530718
# define LEFT	3.14159265359

/**
 * Values returned by cos(), sin()
 * and other trigonometric functions may be too small.
 * To fix that, we'll amplify their return values.
 * Used primarily in "movements" part of controls.
 */
# define TF_AMP	5

/**
 * Yes, field of view!
 */
# define FOV	70

/**
 * For system crashes: malloc, write...
 */
# define FATAL_ERROR	-1
# define ERR_USAGE		"usage: ./cub3d <path/to/map.cub>"
/* Parameter which we can't identify. */
# define INV_PAR		1
/* Some parameter is duplicated. */
# define DUP_PAR		2

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
	bool			set;	/* Basically is used only in parser. */
}	t_rgb;

/**
 * Every node of \ref map contains a string (a row) of a map.
 * Parser will save information here.
 */
typedef struct s_args
{
	char		*textures[TEXTURES_SIZE];
	t_rgb		colors[COLORS_SIZE];
	t_list		*map;
}	t_args;

/**
 * MLX stuff.
 */
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*img_pixels;
	int		bits_per_pixel;
	int		size_line;
	int		endianness;		/* We don't care about it tho. */
}	t_img;

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

/**
 * Everything here will be measured in radians.
 * \ref delta_x and \ref delta_y are required for moving.
 */
typedef struct s_angle
{
	double	angle;
	/**
	 * For movements (not required, but they make everything easier).
	 */
	double	delta_x;
	double	delta_y;
}	t_angle;

/**
 * Mainly MLX data, but also player's position,
 * floor's and ceiling's colors, map, etc.
 */
typedef struct s_data
{
	void		*conn;
	void		*win;
	t_img		textures[TEXTURES_SIZE];
	t_rgb		colors[COLORS_SIZE];
	t_list		*map;
	t_coords	map_size;
	t_coords	player;
	t_angle		player_angle;
}	t_data;

#endif /* CUB3D_H */
