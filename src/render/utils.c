/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:06:29 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 17:11:10 by asagymba         ###   ########.fr       */
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
	int	offset;
	int	to_put;

	offset = (x * (img->bits_per_pixel / 8)) + (img->size_line * y);
	to_put = pixel->r;
	to_put <<= OCTET;
	to_put += pixel->g;
	to_put <<= OCTET;
	to_put += pixel->b;
	*((int *)(img->img_pixels + offset)) = to_put;
}

struct s_rgb	ft_pixel_get_from_image(struct s_img *img, int x, int y)
{
	const struct s_rgb	black = {0, 0, 0, true};
	struct s_rgb		ret;
	int					offset;
	unsigned char		*pixel;

	if (x >= img->width || y >= img->height)
		return (black);
	(void)ft_memset(&ret, 0, sizeof(struct s_rgb));
	offset = (x * (img->bits_per_pixel / 8)) + (img->size_line * y);
	pixel = ((unsigned char *)(img->img_pixels + offset));
	ret.r = *(++pixel);
	ret.g = *(++pixel);
	ret.b = *(++pixel);
	ret.set = true;
	return (ret);
}

#undef OCTET

/**
 * Literally a copy paste from @3DSage.
 */
double	ft_dist(struct s_double_point a, struct s_double_point b, double angle)
{
	return (cos(angle) * (b.x - a.x) - sin(angle) * (b.y - a.y));
}
