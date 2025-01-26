/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:19:04 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 22:48:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>
#include <cub3D.h>
#include <libft.h>
#include <math.h>
#include <utils.h>

/**
 * May be required to access some defines (like M_PI) on older platforms.
 */
#define _USE_MATH_DEFINES

/**
 * Continue the ray cast, until ray hits the wall.
 * @param	data		cub3D's data.
 * @param	ray			Out parameter.
 * 						Where to store information where the ray hits the wall
 * 						and distance between that coordinate and us
 * 						(and type of the ray).
 * @param	cast_data	Where to store the information
* 						on where would the ray stop.
* 						Basically a working structure.
* @param
 */
static void	ft_ray_cast_until_wall_is_hit(struct s_data *data,
		struct s_ray *ray, struct s_ray_cast *cast_data, int ray_type)
{
	cast_data->casting_iteration = 0;
	while (cast_data->casting_iteration < cast_data->max_casting_iterations)
	{
		cast_data->map.x = cast_data->ray_x / TILE_SIZE;
		cast_data->map.y = cast_data->ray_y / TILE_SIZE;
		if ((cast_data->map.x >= 0 && cast_data->map.y >= 0)
			&& (cast_data->map.x < data->map_size.x
				&& cast_data->map.y < data->map_size.y)
			&& ft_get_map_row(data->map,
				cast_data->map.y)[cast_data->map.x] == '1')
		{
			ft_try_to_set_the_ray((struct s_set_ray){ray,
				(struct s_double_point){data->player.x, data->player.y},
				(struct s_double_point){cast_data->ray_x, cast_data->ray_y},
				cast_data->ray_angle, ray_type});
		}
		cast_data->ray_x += cast_data->ray_x_offset;
		cast_data->ray_y += cast_data->ray_y_offset;
		cast_data->casting_iteration++;
	}
}

/**
 * Handle one of ray cast iterations up or down.
 * Calculate rays initial position and its offsets.
 * @brief	Bypass Norminette.
 * @param	data		cub3D's data.
 * @param	cast_data	Out parameter. Where to store the information
 * 						on where would the ray stop.
 */
static void	ft_horizontal_ray_cast_handle_up_and_down(struct s_data *data,
		struct s_ray_cast *cast_data)
{
	if (cast_data->ray_angle < M_PI)
	{
		cast_data->ray_y = (data->player.y / TILE_SIZE * TILE_SIZE)
			- FOR_PRECISION;
		cast_data->ray_x = data->player.x
			- (data->player.y - cast_data->ray_y) * cast_data->ray_angle_tan;
		cast_data->ray_y_offset = -TILE_SIZE;
		cast_data->ray_x_offset = cast_data->ray_y_offset
			* cast_data->ray_angle_tan;
	}
	else if (cast_data->ray_angle > M_PI)
	{
		cast_data->ray_y = (data->player.y / TILE_SIZE * TILE_SIZE) + TILE_SIZE;
		cast_data->ray_x = data->player.x
			- (data->player.y - cast_data->ray_y) * cast_data->ray_angle_tan;
		cast_data->ray_y_offset = TILE_SIZE;
		cast_data->ray_x_offset = cast_data->ray_y_offset
			* cast_data->ray_angle_tan;
	}
}

/**
 * Horizontal ray casting.
 * If player looks straight left or straight right,
 * it's impossible for a ray to ever hit horizontal line.
 * Works differently if player looks up or down.
 * @brief	Horizontal ray casting.
 * @param	data		cub3D's data.
 * @param	rays		Out parameter. Where to store the rays information.
 * @param	rays_size	How many rays to cast.
 * @param	gap			Gap between \p rays.
 */
void	ft_horizontal_ray_cast(struct s_data *data, struct s_ray *rays,
		int rays_size, double gap)
{
	struct s_ray_cast	cast_data;

	(void)ft_memset(&cast_data, 0, sizeof(struct s_ray_cast));
	cast_data.max_casting_iterations = TILE_SIZE;
	cast_data.ray_angle = ft_initialize_angle(data->player_angle.angle
			+ ((rays_size / 2) * gap));
	while (cast_data.i < rays_size)
	{
		cast_data.ray_angle_tan = -1 / tan(cast_data.ray_angle);
		if (cast_data.ray_angle == LEFT || cast_data.ray_angle == RIGHT)
		{
			cast_data.ray_angle += gap;
			cast_data.i++;
			continue ;
		}
		ft_horizontal_ray_cast_handle_up_and_down(data, &cast_data);
		ft_ray_cast_until_wall_is_hit(data, rays + cast_data.i, &cast_data,
			HORIZONTAL_RAY);
		cast_data.ray_angle = ft_initialize_angle(cast_data.ray_angle - gap);
		cast_data.i++;
	}
}

/**
 * Handle one of ray cast iterations left or right.
 * Calculate rays initial position and its offsets.
 * @brief	Bypass Norminette.
 * @param	data		cub3D's data.
 * @param	cast_data	Out parameter. Where to store the information
 * 						on where would the ray stop.
 */
static void	ft_vertical_ray_cast_handle_left_and_right(struct s_data *data,
		struct s_ray_cast *cast_data)
{
	if (cast_data->ray_angle > M_PI / 2 && cast_data->ray_angle < M_PI / 2 * 3)
	{
		cast_data->ray_x = (data->player.x / TILE_SIZE * TILE_SIZE)
			- FOR_PRECISION;
		cast_data->ray_y = data->player.y
			- (data->player.x - cast_data->ray_x) * cast_data->ray_angle_tan;
		cast_data->ray_x_offset = -TILE_SIZE;
		cast_data->ray_y_offset = cast_data->ray_x_offset
			* cast_data->ray_angle_tan;
	}
	else if (cast_data->ray_angle < M_PI / 2
		|| cast_data->ray_angle > M_PI / 2 * 3)
	{
		cast_data->ray_x = (data->player.x / TILE_SIZE * TILE_SIZE) + TILE_SIZE;
		cast_data->ray_y = data->player.y
			- (data->player.x - cast_data->ray_x) * cast_data->ray_angle_tan;
		cast_data->ray_x_offset = TILE_SIZE;
		cast_data->ray_y_offset = cast_data->ray_x_offset
			* cast_data->ray_angle_tan;
	}
}

/**
 * Vertical ray casting.
 * If player looks straight up or straight down,
 * it's impossible for a ray to ever hit vertical line.
 * Works differently if player looks left or right.
 * This is a code duplicate, however we can't pass more
 * than 4 parameters due to Norminette.
 * @brief	Horizontal ray casting.
 * @param	data		cub3D's data.
 * @param	rays		Out parameter. Where to store the rays information.
 * @param	rays_size	How many rays to cast.
 * @param	gap			Gap between \p rays.
 */
void	ft_vertical_ray_cast(struct s_data *data, struct s_ray *rays,
		int rays_size, double gap)
{
	struct s_ray_cast	cast_data;

	(void)ft_memset(&cast_data, 0, sizeof(struct s_ray_cast));
	cast_data.max_casting_iterations = TILE_SIZE;
	cast_data.ray_angle = ft_initialize_angle(data->player_angle.angle
			+ ((rays_size / 2) * gap));
	while (cast_data.i < rays_size)
	{
		cast_data.ray_angle_tan = -tan(cast_data.ray_angle);
		if (cast_data.ray_angle == UP || cast_data.ray_angle == DOWN)
		{
			cast_data.ray_angle += gap;
			cast_data.i++;
			continue ;
		}
		ft_vertical_ray_cast_handle_left_and_right(data, &cast_data);
		ft_ray_cast_until_wall_is_hit(data, rays + cast_data.i, &cast_data,
			VERTICAL_RAY);
		cast_data.ray_angle = ft_initialize_angle(cast_data.ray_angle - gap);
		cast_data.i++;
	}
}
