/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 18:00:23 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Everything related to initialization (construction) will be here.
 */

#include <init.h>
#include <cub3D.h>
#include <errno.h>
#include <stddef.h>
#include <mlx.h>
#include <stdlib.h>
#include <utils.h>
#include <math.h>

/**
 * May be required to access some defines (like M_PI) on older platforms.
 */
#define _USE_MATH_DEFINES

/**
 * Norminette bypass. Reads textures and saves them to \p data.
 * @param	args	Parsed arguments.
 * @param	data	Where to save MLX connection, window and textures.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
static int	ft_prep_mlx_read_textures(const struct s_args *args,
					struct s_data *data)
{
	int	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->conn,
				args->textures[i],
				&data->textures[i].width, &data->textures[i].height);
		if (data->textures[i].img == NULL)
		{
			if (errno == 0)
				errno = EACCES;
			return (-1);
		}
		data->textures[i].img_pixels = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].size_line, &data->textures[i].endianness);
		i++;
	}
	return (0);
}

/**
 * Prepares MLX: opens the connection, window
 * and reads all textures from \p args.
 * If after some X11 function failed errno is set 0, we'll set it to EACCES.
 * Note: Valgrind tells us that some syscall points to uninitialized value
 * created by mlx_int_anti_resize_win().
 * It's not our fault - it's created by MiniLibX.
 * We do everything in accordance to its manpages.
 * @param	args	Parsed arguments.
 * @param	data	Where to save MLX connection, window and textures.
 * @return	-1, if something went wrong. errno will also be set;
 * 			Some non-negative value, if everything went fine.
 */
static int	ft_prep_mlx(const struct s_args *args, struct s_data *data)
{
	data->conn = mlx_init();
	if (data->conn == NULL)
	{
		if (errno == 0)
			errno = EACCES;
		return (-1);
	}
	data->win = mlx_new_window(data->conn, WIN_X, WIN_Y, "cub3D");
	if (data->win == NULL)
	{
		if (errno == 0)
			errno = EACCES;
		return (-1);
	}
	return (ft_prep_mlx_read_textures(args, data));
}

/**
 * Initializes player's angle depending on the \p direction they're looking at.
 * @param	data		cub3D's data.
 * @param	direction	Direction player is looking at.
 */
static void	ft_init_player_angle(struct s_data *data, char direction)
{
	if (direction == 'N')
	{
		data->player_angle.angle = UP;
	}
	else if (direction == 'S')
	{
		data->player_angle.angle = DOWN;
	}
	else if (direction == 'E')
	{
		data->player_angle.angle = RIGHT;
	}
	else if (direction == 'W')
	{
		data->player_angle.angle = LEFT;
	}
	ft_calculate_angle_deltas(data);
}

/**
 * Sets the player coordinates based on values in \p data->map.
 * @param	data	cub3D's data.
 */
static void	ft_init_player(struct s_data *data)
{
	int			i;
	const char	*current_row;
	int			j;

	i = 0;
	while (i < data->map_size.y)
	{
		current_row = ft_get_map_row(data->map, i);
		j = 0;
		while (current_row[j] != '\0')
		{
			if (current_row[j] == 'N' || current_row[j] == 'S'
				|| current_row[j] == 'E' || current_row[j] == 'W')
			{
				data->player.x = j * TILE_SIZE + TILE_SIZE / 2;
				data->player.y = i * TILE_SIZE + TILE_SIZE / 2;
				ft_init_player_angle(data, current_row[j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_prep_data(struct s_args *args, struct s_data *data)
{
	int	errnobuf;
	int	i;

	if (ft_prep_mlx(args, data) == -1)
	{
		errnobuf = errno;
		if (errnobuf == 0)
			errnobuf = EACCES;
		ft_free_s_data_content(data);
		errno = errnobuf;
		return (-1);
	}
	i = 0;
	while (i < COLORS_SIZE)
	{
		data->colors[i] = args->colors[i];
		i++;
	}
	data->map = args->map;
	args->map = NULL;
	data->map_size.x = ft_strlen((const char *)data->map->content);
	data->map_size.y = ft_lstsize(data->map);
	ft_init_player(data);
	return (0);
}
