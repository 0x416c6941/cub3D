/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:01:34 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 19:51:54 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <math.h>

/**
 * Yes, Norminette.
 * @param	arg	Arguments of ft_draw_line_pixel() + pointer to pixel
 * 				stored in ft_draw_line_pixel().
 */
/*
static void	ft_draw_line_pixel_handle_line_height_not_bigger_than_win_y(
		struct s_draw_line_pixel_norminette arg)
{
	if (!(arg.draw_line_data->line_height <= WIN_Y))
		return ;
	if (arg.draw_line_data->texture_index == TEXTURE_NO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				arg.ray->x,
				arg.draw_line_data->i * ((TILE_SIZE * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_SO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)arg.ray->x % TILE_SIZE),
				arg.draw_line_data->i * ((TILE_SIZE * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_WE)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)arg.ray->y % TILE_SIZE),
				arg.draw_line_data->i * ((TILE_SIZE * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_EA)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				arg.ray->y,
				arg.draw_line_data->i * ((TILE_SIZE * 1.0f)
					/ arg.draw_line_data->line_height));
}
 */

/**
 * Yes, Norminette.
 * @param	arg	Arguments of ft_draw_line_pixel() + pointer to pixel
 * 				stored in ft_draw_line_pixel().
 */
/*
static void	ft_draw_line_pixel_handle_line_height_bigger_than_win_y(
		struct s_draw_line_pixel_norminette arg)
{
	const double	padding = TILE_SIZE * (1
			- ((WIN_Y * 1.0f) / arg.draw_line_data->line_height));

	if (!(arg.draw_line_data->line_height > WIN_Y))
		return ;
	if (arg.draw_line_data->texture_index == TEXTURE_NO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				padding + arg.ray->x * (((TILE_SIZE - padding) - padding)
					/ arg.draw_line_data->until),
				padding + arg.draw_line_data->i * (((TILE_SIZE - padding)
						- padding) / arg.draw_line_data->until));
	else if (arg.draw_line_data->texture_index == TEXTURE_SO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)arg.ray->x % TILE_SIZE),
				padding + arg.draw_line_data->i * (((TILE_SIZE - padding)
						- padding) / arg.draw_line_data->until));
	else if (arg.draw_line_data->texture_index == TEXTURE_WE)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)arg.ray->y % TILE_SIZE),
				padding + arg.draw_line_data->i * (((TILE_SIZE - padding)
						- padding) / arg.draw_line_data->until));
	else if (arg.draw_line_data->texture_index == TEXTURE_EA)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				arg.ray->y,
				padding + arg.draw_line_data->i * (((TILE_SIZE - padding)
						- padding) / arg.draw_line_data->until));
}
 */

void	ft_draw_line_pixel(struct s_img *img, struct s_ray *ray,
		struct s_draw_line *draw_line_data, int x)
{
	const struct s_rgb	black = (struct s_rgb){0, 0, 0, true};
	struct s_rgb		pixel;
	int					y;

	pixel = black;
	if (draw_line_data->line_height <= WIN_Y)
		y = (draw_line_data->i - draw_line_data->top_pixel)
			* ((TILE_SIZE * 1.0f) / (draw_line_data->bottom_pixel
						- draw_line_data->top_pixel));
	else
		y = draw_line_data->i * ((TILE_SIZE * 1.0f) / WIN_Y);
		/*
		y = (draw_line_data->line_height - WIN_Y) / TILE_SIZE
				+ draw_line_data->i / TILE_SIZE;
		 */
	if (draw_line_data->texture_index == TEXTURE_NO)
		pixel = ft_pixel_get_from_image(draw_line_data->texture, ray->x, y);
	else if (draw_line_data->texture_index == TEXTURE_SO)
		pixel = ft_pixel_get_from_image(draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)ray->x % TILE_SIZE), y);
	else if (draw_line_data->texture_index == TEXTURE_WE)
		pixel = ft_pixel_get_from_image(draw_line_data->texture,
				(TILE_SIZE - 1) - ((int)ray->y % TILE_SIZE), y);
	else if (draw_line_data->texture_index == TEXTURE_EA)
		pixel = ft_pixel_get_from_image(draw_line_data->texture, ray->y, y);
	ft_pixel_put_on_image(img, x, draw_line_data->i, &pixel);
}
