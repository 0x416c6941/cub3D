/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 15:26:49 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <stddef.h>
#include <errno.h>

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
	int	i, errnobuf, discard, j;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		data->textures[i] = mlx_xpm_file_to_image(data->conn,
			args->textures[i], &discard, &discard);
		if (data->textures[i] == NULL)
		{
			errnobuf = *errno;
			j = 0;
			while (j < i)
			{
				(void)mlx_destroy_image(data->conn, data->textures[j]);
				data->textures[j++] = NULL;
			}
			if (errnobuf == 0)
				errnobuf = EACCES;
			return ((void)mlx_destroy_window(data->conn, data->win),
				data->win = NULL, (void)mlx_destroy_display(data->conn),
				free(data->conn), data->conn = NULL, *errno = errnobuf, -1);
		}
		i++;
	}
	return (0);
}

/**
 * If after some X11 function failed errno is set 0, we'll set it to EACCES.
 */
int	ft_prep_mlx(const struct s_args *args, struct s_data *data)
{
	int	errnobuf;

	data->conn = mlx_init();
	if (data->conn == NULL)
	{
		if (*errno == 0)
			*errno = EACCES;
		return (-1);
	}
	data->win = mlx_new_window(data->conn, WIN_X, WIN_Y, "cub3D");
	if (data->win == NULL)
	{
		errnobuf = errno;
		mlx_destroy_display(data->conn);
		free(data->conn);
		data->conn = NULL;
		*errno = errnobuf;
		if (errnobuf == 0)
			*errno = EACCES;
		return (-1);
	}
	return (ft_prep_mlx_read_textures(args, data));
}
