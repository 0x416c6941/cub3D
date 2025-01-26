/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:06:29 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 14:35:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <stdbool.h>
#include <math.h>

#define OCTET	8

/**
 * Thanks to @suspectedoceano!
 */
void	ft_pixel_put_on_image(struct s_img *img, int x, int y,
			const struct s_rgb *pixel)
{
	int				offset;
	unsigned int	to_put;
	(void)to_put;

	offset = (x * (img->bits_per_pixel / 8)) + (img->size_line * y);
	to_put = (pixel->r << (OCTET * 2)) | (pixel->g << OCTET) | pixel->b;
	*((unsigned int *)(img->img_pixels + offset)) = to_put;
}

struct s_rgb	ft_pixel_get_from_image(struct s_img *img, int x, int y)
{
	struct s_rgb		ret;
	int					offset;
	unsigned int		*pixel;

	(void)ft_memset(&ret, 0, sizeof(struct s_rgb));
	if (x >= BLOCK_X)
		x %= BLOCK_X;
	if (y >= BLOCK_Y)
		y %= BLOCK_Y;
	offset = (int)((x * ((img->width * 1.0f) / BLOCK_X))
			* (img->bits_per_pixel / OCTET)) + (img->size_line
			* (int)(y * ((img->height * 1.0f) / BLOCK_Y)));
	pixel = ((unsigned int *)(img->img_pixels + offset));
	ret.r = *pixel >> OCTET * 2;
	ret.g = *pixel >> OCTET;
	ret.b = *pixel;
	ret.set = true;
	return (ret);
}

#undef OCTET

/**
 * Literally a copy paste from @3DSage.
 */
double	ft_dist(struct s_double_point a, struct s_double_point b, double angle)
{
	double	ret;

	ret = cos(angle) * (b.x - a.x) - sin(angle) * (b.y - a.y);
	return (ret);
}

/**
 * Norminette bypass. Try to set the \p ray,
 * if it wasn't set already or if we found a shorter one.
 * "minimal_possible_dist" is a dirty hack thingy, but it works!
 * @param	ray				Ray to try to set.
 * @param	player_coords	Current players coords.
 * @param	ray_coords		Rays coords.
 * @param	ray_angle		Rays angle.
 */
void	ft_try_to_set_the_ray(struct s_ray *ray,
		struct s_double_point player_coords, struct s_double_point ray_coords,
		double ray_angle)
{
	const double	dist = ft_dist(player_coords, ray_coords, ray_angle);
	const double	minimal_possible_dist = 1.0f;

	if (dist >= minimal_possible_dist && (!ray->hit || ray->distance > dist))
	{
		ray->x = ray_coords.x;
		ray->y = ray_coords.y;
		ray->distance = dist;
		ray->angle = ray_angle;
		ray->hit = true;
	}
}

void	ft_set_texture(struct s_data *data, struct s_ray *ray,
		struct s_draw_line *out)
{
	out->should_invert_coords = false;
	if ((int)ray->y % BLOCK_Y == BLOCK_Y - 1)
	{
		out->texture = &data->textures[TEXTURE_NO];
		out->should_invert_coords = true;
	}
	else if ((int)ray->y % BLOCK_Y == 0)
	{
		out->texture = &data->textures[TEXTURE_SO];
		out->should_invert_coords = true;
	}
	else if ((int)ray->x % BLOCK_X == BLOCK_X - 1)
		out->texture = &data->textures[TEXTURE_WE];
	else if ((int)ray->x % BLOCK_X == 0)
		out->texture = &data->textures[TEXTURE_EA];
}
