/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 14:35:09 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <cub3D.h>
#include <errno.h>
#include <stddef.h>
#include <mlx.h>
#include <stdlib.h>
#include <utils.h>
#include <math.h>

/**
 * We can't get display's dimensions through MLX,
 * so we'll just window's dimensions to HD.
 */
#define WIN_X	1280
#define WIN_Y	720

/**
 * cub3D.h -> BLOCK_X / 2, BLOCK_Y / 2.
 */
#define BLOCK_X_MIDDLE	64
#define BLOCK_Y_MIDDLE	64

/**
 * May be required to access some defines, like M_PI on older platforms.
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
	int	discard;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		data->textures[i] = mlx_xpm_file_to_image(data->conn,
				args->textures[i], &discard, &discard);
		if (data->textures[i] == NULL)
		{
			if (errno == 0)
				errno = EACCES;
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * Prepares MLX: opens the connection, window
 * and reads all textures from \p args.
 * If after some X11 function failed errno is set 0, we'll set it to EACCES.
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
		data->player_angle.angle = M_PI / 2;
	}
	else if (direction == 'S')
	{
		data->player_angle.angle = M_PI / 2 * 3;
	}
	else if (direction == 'E')
	{
		data->player_angle.angle = M_PI * 2;
	}
	else if (direction == 'W')
	{
		data->player_angle.angle = M_PI;
	}
	data->player_angle.delta_x = cos(data->player_angle.angle) * TF_AMP;
	data->player_angle.delta_y = sin(data->player_angle.angle) * TF_AMP;
}

/**
 * Sets the player coordinates based on values in \p data->map.
 * @param	data	cub3D's data.
 */
static void	ft_init_player(struct s_data *data)
{
	const int	map_size = ft_lstsize(data->map);
	int			i;
	const char	*current_row;
	int			j;

	i = 0;
	while (i < map_size)
	{
		current_row = ft_get_map_row(data->map, i);
		j = 0;
		while (current_row[j] != '\0')
		{
			if (current_row[j] == 'N' || current_row[j] == 'S'
				|| current_row[j] == 'E' || current_row[j] == 'W')
			{
				data->player.x = j * BLOCK_X + BLOCK_X_MIDDLE;
				data->player.y = i * BLOCK_Y + BLOCK_Y_MIDDLE;
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
		(void)ft_memset(&args->colors[i], 0, sizeof(struct s_rgb));
		i++;
	}
	data->map = args->map;
	args->map = NULL;
	ft_init_player(data);
	return (0);
}
