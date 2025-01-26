/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:13:59 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 22:52:07 by asagymba         ###   ########.fr       */
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
 * To distinguish horizontal from vertical rays.
 */
# define HORIZONTAL_RAY	1
# define VERTICAL_RAY	2

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
	double	angle;
	/**
	 * Has the ray actually hit the wall?
	 * If not, then variables above may stay uninitialized.
	 */
	bool	hit;
	int		type;		/* Horizontal or vertical. */
}	t_ray;

/**
 * To actually process (cast) the ray, we'll use this structure.
 * Basically like a working structure for the ray caster.
 * Used primarily to bypass Norminette.
 */
typedef struct s_ray_cast
{
	/**
	 * Which ray we're casting now. H(i) = [0, WIN_X].
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

typedef struct s_set_ray
{
	struct s_ray			*ray;
	struct s_double_point	player_coords;
	struct s_double_point	ray_coords;
	double					ray_angle;
	int						ray_type;
}	t_set_ray;

/**
 * Yet another Norminette bypass, this time for ft_draw_line()!
 */
typedef struct s_draw_line
{
	double			fix_fisheye;
	double			line_height;
	double			top_pixel;		/* With minimum y (top of the screen). */
	double			bottom_pixel;	/* With maximum y (bottom of the screen). */
	struct s_img	*texture;
	int				texture_index;
	int				img_y;			/* y coordinate where to draw pixel. */
}	t_draw_line;

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
 * @param	data		cub3D's data.
 * @param	rays		Out parameter. Where to store the rays information.
 * @param	rays_size	How many rays to cast.
 * @param	gap			Gap between \p rays.
 */
void			ft_horizontal_ray_cast(struct s_data *data, struct s_ray *rays,
					int rays_size, double gap);

/**
 * Vertical ray casting.
 * @param	data		cub3D's data.
 * @param	rays		Out parameter. Where to store the rays information.
 * @param	rays_size	How many rays to cast.
 * @param	gap			Gap between \p rays.
 */
void			ft_vertical_ray_cast(struct s_data *data, struct s_ray *rays,
					int rays_size, double gap);

/**
 * Draws a pixel to \p image.
 * @param	img				Image where to draw it.
 * @param	ray				Information where did the cast ray lay.
 * @param	draw_line_data	Data calculated in ft_draw_line().
 * @param	img_x			x coordinate on \p img where to draw the pixel.
 */
void			ft_draw_line_pixel(struct s_img *img, struct s_ray *ray,
					struct s_draw_line *draw_line_data, int img_x);

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
 * If \p x or \p y are bigger than TILE_SIZE,
 * they'll get modulo'ed by TILE_SIZE.
 * Does the scaling of the image, if it's not exactly
 * TILE_SIZE pixels wide or TILE_SIZE pixels tall.
 * @warning	\p x and \p y can't be negative.
 * @param	img		Image to get pixel from.
 * @param	x		x coordinate.
 * @param	y		y coordinate.
 * @return	Requested pixel.
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

/**
 * Norminette bypass. Try to set the "ray" in \p arg,
 * if it wasn't set already or if we found a shorter one.
 * @param	arg	Please consult with the structure definition.
 */
void			ft_try_to_set_the_ray(struct s_set_ray arg);

/**
 * Sets the "texture" and "texture_index" attributes in \p out.
 * @param	data	cub3D's data.
 * @param	ray		Information on where did the cast ray lay.
 * @param	out		Out parameter.
 */
void			ft_set_texture(struct s_data *data, struct s_ray *ray,
					struct s_draw_line *out);

#endif /* RENDER_H */
