/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 15:16:36 by asagymba         ###   ########.fr       */
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
	int	i;

	i = 0;
}

/**
 * X11 is unique, since it doesn't set errno.
 * Therefore, if something failed within X11 (errno isn't set to ENOMEM),
 * we'll just set errno to EACCES.
 */
int	ft_prep_mlx(const struct s_args *args, struct s_data *data)
{
	int	errnobuf;

	data->conn = mlx_init();
	if (data->conn == NULL)
	{
		if (*errno != ENOMEM)
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
		*errno = EACCES;
		if (errnobuf == ENOMEM)
			*errno = ENOMEM;
		return (-1);
	}
	return (ft_prep_mlx_read_textures(args, data));
}
