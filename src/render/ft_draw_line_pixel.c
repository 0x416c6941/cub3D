/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:01:34 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 16:16:46 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>

static void	ft_draw_line_pixel_handle_line_height_smaller_than_win_y(
		struct s_draw_line_pixel_norminette arg)
{
	if (!(arg.draw_line_data->line_height <= WIN_Y))
		return ;
	if (arg.draw_line_data->texture_index == TEXTURE_NO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				arg.ray->x,
				arg.draw_line_data->i * ((BLOCK_Y * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_SO)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(BLOCK_X - 1) - ((int)arg.ray->x % BLOCK_X),
				arg.draw_line_data->i * ((BLOCK_Y * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_WE)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				(BLOCK_Y - 1) - ((int)arg.ray->y % BLOCK_Y),
				arg.draw_line_data->i * ((BLOCK_Y * 1.0f)
					/ arg.draw_line_data->line_height));
	else if (arg.draw_line_data->texture_index == TEXTURE_EA)
		*arg.pixel = ft_pixel_get_from_image(arg.draw_line_data->texture,
				arg.ray->y,
				arg.draw_line_data->i * ((BLOCK_Y * 1.0f)
					/ arg.draw_line_data->line_height));
}

void	ft_draw_line_pixel(struct s_img *img, struct s_ray *ray,
		struct s_draw_line *draw_line_data, int x)
{
	const struct s_rgb	black = (struct s_rgb){0, 0, 0, true};
	struct s_rgb		pixel;

	pixel = black;
	ft_draw_line_pixel_handle_line_height_smaller_than_win_y(
		(struct s_draw_line_pixel_norminette){img, ray, draw_line_data,
		x, &pixel});
	ft_pixel_put_on_image(img,
		x, draw_line_data->line_offset + draw_line_data->i, &pixel);
}
