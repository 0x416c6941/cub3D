/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 18:07:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <errno.h>
#include <stddef.h>
#include <mlx.h>
#include <stdlib.h>
#include <utils.h>

/**
 * We can't get display's dimensions through MLX,
 * we'll just them to HD.
 */
#define WIN_X	1280
#define WIN_Y	720

/**
 * All images will be cropped or extended (with black spaces)
 * to those dimensions.
 * Why? Because I'm lazy to handle different sizes of textures.
 * I hate Norminette enough already.
 */
#define TEXTURE_X	128
#define TEXTURE_Y	128

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
				data->player.x = j;
				data->player.y = i;
				return;
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
		(void)ft_memset(&args->colors + i, 0, sizeof(struct s_rgb));
		i++;
	}
	data->map = args->map;
	args->map = NULL;
	ft_init_player(data);
	return (0);
}
