/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 20:59:58 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <mlx.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

int	ft_render(struct s_data *data)
{
	t_img	img;

	img.img = mlx_new_image(data->conn, WIN_X, WIN_Y);
	if (img.img == NULL)
	{
		if (errno == 0)
			errno = EACCES;
		return (perror("cub3D"), ft_mlx_exit(data, EXIT_FAILURE), -1);
	}
	img.width = WIN_X;
	img.height = WIN_Y;
	img.img_pixels = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.size_line, &img.endianness);
	(void)mlx_destroy_image(data->conn, img.img);
	return (0);
}
