/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:13:59 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 23:28:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3D.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
/**
 * To cast a horizontal ray upwards.
 */
# define FOR_PRECISION	0.0001

/**
 * ----------------------------------------------------------------------------
 * Functions.
 * ----------------------------------------------------------------------------
 */
/**
 * Renders the image. If something goes wrong - exits the program.
 * @param	data	cub3D's data.
 * @return	Safe to ignore. Some non-negative value if everything went fine;
 * 			-1 on error (error log will be written and program will exit).
 */
int		ft_render(struct s_data *data);

/**
 * Draws a \p pixel to a point [\p x, \p y] in \p img.
 * @param	img		Image to draw the \p pixel in.
 * @param	x		x coordinate.
 * @param	y		y coordinate.
 * @param	pixel	Pixel to draw.
 */
void	ft_pixel_put_on_image(struct s_img *img, int x, int y,
			const struct s_rgb *pixel);

#endif /* RENDER_H */
