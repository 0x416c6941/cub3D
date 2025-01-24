/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 16:55:29 by asagymba         ###   ########.fr       */
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

#define BEGINNING	0

/**
 * Draws a ceiling and floor (defined in \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image where to draw them.
 */
static void	ft_draw_ceiling_and_floor(struct s_data *data,
		struct s_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height / 2)
	{
		j = 0;
		while (j < img->width)
			ft_pixel_put_on_image(img, j++, i, &data->colors[COLOR_CEILING]);
		i++;
	}
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
			ft_pixel_put_on_image(img, j++, i, &data->colors[COLOR_FLOOR]);
		i++;
	}
}

/**
 * Draws walls (use textures from \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image to where draw them.
 */
static void	ft_draw_walls(struct s_data *data, struct s_img *img)
{
	struct s_ray	rays[FOV];
	const double	gap_between_rays = DEGREE;

	(void)ft_memset(rays, 0, sizeof(struct s_ray) * FOV);
	ft_horizontal_ray_cast(data, rays, FOV, gap_between_rays);
	ft_vertical_ray_cast(data, rays, FOV, gap_between_rays);
	(void)img;
}

int	ft_render(struct s_data *data)
{
	struct s_img	img;

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
	ft_draw_ceiling_and_floor(data, &img);
	ft_draw_walls(data, &img);
	printf("Putting image to window...\n");
	(void)mlx_put_image_to_window(data->conn, data->win, img.img,
		BEGINNING, BEGINNING);
	(void)mlx_destroy_image(data->conn, img.img);
	return (0);
}
