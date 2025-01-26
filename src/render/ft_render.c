/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:15:20 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 13:57:59 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <mlx.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utils.h>
#include <stdbool.h>

#define BEGINNING	0

/**
 * Draws a ceiling and floor (defined in \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image where to draw them.
 */
static void	ft_draw_ceiling_and_floor(struct s_data *data, struct s_img *img)
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
 * Draws a pixel to \p image.
 * @param	img				Image where to draw it.
 * @param	ray				Information where did the cast ray lay.
 * @param	draw_line_data	Data calculated in ft_draw_line().
 * @param	x				x coordinate of a pixel to draw.
 */
void	ft_draw_line_pixel(struct s_img *img, struct s_ray *ray,
		struct s_draw_line *draw_line_data, int x)
{
	struct s_rgb	pixel;

	if (draw_line_data->line_height <= WIN_Y)
	{
		if (draw_line_data->should_invert_coords == false)
			pixel = ft_pixel_get_from_image(draw_line_data->texture,
					ray->y,
					draw_line_data->i * ((BLOCK_Y * 1.0f)
						/ draw_line_data->line_height));
		else
			pixel = ft_pixel_get_from_image(draw_line_data->texture,
					ray->x,
					draw_line_data->i * ((BLOCK_Y * 1.0f)
						/ draw_line_data->line_height));
	}
	else
		pixel = (struct s_rgb){255, 255, 255, true};
		/*
		pixel = ft_pixel_get_from_image(draw_line_data->texture,
				ray->x,
				draw_line_data->i * ((BLOCK_Y * 1.0f)
					/ draw_line_data->line_height));
	 	 */
	ft_pixel_put_on_image(img,
		x, draw_line_data->line_offset + draw_line_data->i, &pixel);
}

/**
 * Draw a line to \p img based on cast \p ray values.
 * Thanks a lot to @3DSage.
 * @param	data		cub3D's data.
 * @param	img			Where to draw a line.
 * @param	ray			Cast ray.
 * @param	x_offset	On which x to start the drawing process.
 */
static void	ft_draw_line(struct s_data *data, struct s_img *img,
		struct s_ray *ray, int x)
{
	struct s_draw_line	draw_line_data;

	draw_line_data.fix_fisheye = ft_initialize_angle(data->player_angle.angle
			- ray->angle);
	ray->distance = ray->distance * cos(draw_line_data.fix_fisheye);
	draw_line_data.line_height = WIN_Y * BLOCK_Y / ray->distance;
	draw_line_data.line_offset = WIN_Y / 2 - draw_line_data.line_height / 2;
	if (draw_line_data.line_height > WIN_Y)
		draw_line_data.line_offset = 0;
	ft_set_texture(data, ray, &draw_line_data);
	draw_line_data.i = 0;
	if (draw_line_data.line_height > WIN_Y)
		draw_line_data.until = WIN_Y;
	else
		draw_line_data.until = draw_line_data.line_height;
	while (draw_line_data.i < draw_line_data.until)
	{
		ft_draw_line_pixel(img, ray, &draw_line_data, x);
		draw_line_data.i++;
	}
}

/**
 * Draws walls (use textures from \p data) to \p img.
 * @param	data	cub3D's data.
 * @param	img		Image where to draw them.
 */
static void	ft_draw_walls(struct s_data *data, struct s_img *img)
{
	struct s_ray	rays[WIN_X];
	const double	gap_between_rays = DEGREE * ((FOV * 1.0f) / WIN_X);
	int				i;

	(void)ft_memset(rays, 0, sizeof(struct s_ray) * WIN_X);
	ft_horizontal_ray_cast(data, rays, WIN_X, gap_between_rays);
	ft_vertical_ray_cast(data, rays, WIN_X, gap_between_rays);
	i = 0;
	while (i < WIN_X)
	{
		ft_draw_line(data, img, rays + i, i);
		i++;
	}
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
	(void)mlx_put_image_to_window(data->conn, data->win, img.img,
		BEGINNING, BEGINNING);
	(void)mlx_destroy_image(data->conn, img.img);
	/* REMOVE THIS! */
#include <sys/time.h>
	struct timeval	time;
	(void)gettimeofday(&time, NULL);
	(void)printf("%ld\n", time.tv_sec * 1000 + time.tv_usec / 1000);
	return (0);
}
