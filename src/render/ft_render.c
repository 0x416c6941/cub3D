/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 19:25:19 by asagymba         ###   ########.fr       */
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
	t_render	render_data;

	(void)data;
	render_data.image = mlx_new_image(data->conn, WIN_X, WIN_Y);
	if (render_data.image == NULL)
	{
		if (errno == 0)
			errno = EACCES;
		return (perror("cub3D"), ft_mlx_exit(data, EXIT_FAILURE), -1);
	}
	render_data.image_pixels = mlx_get_data_addr(render_data.image,
			&render_data.bits_per_pixel, &render_data.size_line,
			&render_data.endianness);
	(void)mlx_destroy_image(data->conn, render_data.image);
	return (0);
}
