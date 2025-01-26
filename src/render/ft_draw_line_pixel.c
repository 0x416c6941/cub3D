/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:01:34 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 21:56:19 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <math.h>

static void	ft_draw_line_pixel_norminette(struct s_img *img, int img_x,
		struct s_draw_line *draw_line_data, struct s_coords pixel_coords)
{
	struct s_rgb		pixel;

	pixel = ft_pixel_get_from_image(draw_line_data->texture,
			pixel_coords.x, pixel_coords.y);
	ft_pixel_put_on_image(img, img_x, draw_line_data->img_y, &pixel);
}

void	ft_draw_line_pixel(struct s_img *img, struct s_ray *ray,
		struct s_draw_line *draw_line_data, int img_x)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = 0;
	pixel_y = 0;
	if (draw_line_data->texture_index == TEXTURE_NO)
		pixel_x = round(ray->x);
	else if (draw_line_data->texture_index == TEXTURE_SO)
		pixel_x = round((TILE_SIZE - 1) - fmod(ray->x, TILE_SIZE));
	else if (draw_line_data->texture_index == TEXTURE_WE)
		pixel_x = round((TILE_SIZE - 1) - fmod(ray->y, TILE_SIZE));
	else if (draw_line_data->texture_index == TEXTURE_EA)
		pixel_x = round(ray->y);
	if (draw_line_data->line_height <= WIN_Y)
		pixel_y = round((draw_line_data->img_y - (int)draw_line_data->top_pixel)
				* ((TILE_SIZE * 1.0f) / draw_line_data->line_height));
	else
	{
		pixel_y = round(((draw_line_data->line_height - WIN_Y) / 2)
				* ((TILE_SIZE * 1.0f) / draw_line_data->line_height)
				+ draw_line_data->img_y * (
					(TILE_SIZE * 1.0f) / draw_line_data->line_height));
	}
	ft_draw_line_pixel_norminette(img, img_x,
		draw_line_data, (struct s_coords){pixel_x, pixel_y});
}
