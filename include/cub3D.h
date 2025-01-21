/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:56:57 by root              #+#    #+#             */
/*   Updated: 2025/01/21 17:50:10 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <libft.h>

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
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
}	t_rgb;

/**
 * Every node of \ref map contains a string (a row) of a map.
 * Parser will save information here.
 */
typedef struct s_args
{
	int			map_info_added;
	char		*textures[TEXTURES_SIZE];
	t_rgb		colors[COLORS_SIZE];
	t_list		*map;
}	t_args;

typedef struct s_coords
{
	double	x;
	double	y;
}	t_coords;

/**
 * Mainly MLX data, but also player's position,
 * floor's and ceiling's colors, map, etc.
 */
typedef struct s_data
{
	void		*conn;
	void		*win;
	void		*textures[TEXTURES_SIZE];
	t_rgb		colors[COLORS_SIZE];
	t_list		*map;
	t_coords	player;
}	t_data;

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Parses file at \p file_path and saves parsed information to \p out.
 * @param	file_path	Path to a .cub file.
 * @param	out			Output.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_parse(const char *file_path, struct s_args *out);

/**
 * Frees content of \p to_free.
 * @param	to_free	Parsed arguments to free().
 */
void	ft_free_s_args_content(struct s_args *to_free);

/**
 * Prepares MLX: opens the connection, window, reads all textures from \p args;
 * and also prepares all other data required for cub3D, e.g. user's base coords.
 * @param	args	Parsed arguments.
 * @param	data	Where to save MLX connection, window and textures.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_prep_data(struct s_args *args, struct s_data *data);

/**
 * Frees content of \p to_free.
 * @param	to_free	cub3D's data to free().
 */
void	ft_free_s_data_content(struct s_data *to_free);

#endif /* CUB3D_H */
