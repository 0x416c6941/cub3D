/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:13:59 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 17:11:02 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <cub3D.h>
# include <stdbool.h>

/**
 * ----------------------------------------------------------------------------
 * Constants.
 * ----------------------------------------------------------------------------
 */
/**
 * To cast a horizontal ray upwards or vertical ray to the left.
 */
# define FOR_PRECISION	0.0001

/**
 * 1 degree in radians. TODO: should this be in cub3D.h?
 */
# define DEGREE	0.0174533

/**
 * ----------------------------------------------------------------------------
 * Structures.
 * ----------------------------------------------------------------------------
 */
/**
 * Information about the shortest ray that was cast from us and hit the wall.
 * Used to save the end result.
 */
typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;	/* From player to the wall that was hit. */
	/**
	 * Has the ray actually hit the wall?
	 * If not, then variables above may stay uninitialized.
	 */
	bool	hit;
}	t_ray;

/**
 * To actually process (cast) the ray, we'll use this structure.
 * Basically like a working structure for the ray caster.
 * Used primarily to bypass Norminette.
 */
typedef struct s_ray_cast
{
	/**
	 * Which ray we're casting now. H(i) = [0, FOV].
	 */
	int			i;
	double		ray_angle;
	double		ray_angle_tan;
	double		ray_x;
	double		ray_y;
	double		ray_x_offset;
	double		ray_y_offset;
	/**
	 * Ray's coordinates cast to map's, so that we could check
	 * if we hit the wall already or not yet.
	 */
	t_coords	map;
	int			casting_iteration;
	int			max_casting_iterations;
}	t_ray_cast;

/**
 * Norminette Bypass for ft_dist()...
 */
typedef struct s_double_point
{
	double	x;
	double	y;
}	t_double_point;

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
int				ft_render(struct s_data *data);

/*
 * Horizontal ray casting.
 * @param	data	cub3D's data.
 * @param	rays	Out parameter. Where to store the rays information.
 * @param	fov		FOV. Size of \p rays. How many rays to cast.
 * @param	gap		Gap between \p rays.
 */
void			ft_horizontal_ray_cast(struct s_data *data, struct s_ray *rays,
					int fov, double gap);

/**
 * Vertical ray casting.
 * @param	data	cub3D's data.
 * @param	rays	Out parameter. Where to store the rays information.
 * @param	fov		FOV. Size of \p rays. How many rays to cast.
 * @param	gap		Gap between \p rays.
 */
void			ft_vertical_ray_cast(struct s_data *data, struct s_ray *rays,
					int fov, double gap);

/**
 * Draws a \p pixel to a point [\p x, \p y] in \p img.
 * @param	img		Image to draw the \p pixel in.
 * @param	x		x coordinate.
 * @param	y		y coordinate.
 * @param	pixel	Pixel to draw.
 */
void			ft_pixel_put_on_image(struct s_img *img, int x, int y,
					const struct s_rgb *pixel);

/**
 * Gets pixel from \p img with coordinates \p x and \p y.
 * @param	img		Image to get pixel from.
 * @param	x		x coordinate.
 * @param	y		y coordinate.
 * @return	Requested pixed, or black pixel if coordinates are out of bounds.
 */
struct s_rgb	ft_pixel_get_from_image(struct s_img *img, int x, int y);

/**
 * Calculates distance between points \p a and \p b.
 * @param	a		Coordinates of a.
 * @param	b		Coordinates of b.
 * @param	angle	Angle petween boints a and b (does it make any sense?)
 * @return	Distance between these two points.
 */
double			ft_dist(struct s_double_point a, struct s_double_point b,
					double angle);

#endif /* RENDER_H */
