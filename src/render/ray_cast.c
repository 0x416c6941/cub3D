/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:19:04 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/24 18:44:21 by asagymba         ###   ########.fr       */
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
 * 						Where to Store information where the ray hits the wall
 * 						and distance between that coordinate and us.
 * @param	cast_data	Where to store the information
* 						on where would the ray stop.
* 						Basically a working structure.
 */
static void	ft_ray_cast_until_wall_is_hit(struct s_data *data,
		struct s_ray *ray, struct s_ray_cast *cast_data)
{
	double	dist;

	cast_data->casting_iteration = 0;
	while (cast_data->casting_iteration < cast_data->max_casting_iterations)
	{
		cast_data->map.x = (int)cast_data->ray_x / BLOCK_X;
		cast_data->map.y = (int)cast_data->ray_y / BLOCK_Y;
		if ((cast_data->map.x >= 0 && cast_data->map.y >= 0)
			&& (cast_data->map.x < data->map_size.x
				&& cast_data->map.y < data->map_size.y)
			&& ft_get_map_row(data->map,
				cast_data->map.y)[cast_data->map.x] == '1')
		{
			/**
			 * Just replace this with such function,
			 * like ft_try_to_set_the_ray().
			 */
			dist = ft_dist((t_double_point){data->player.x, data->player.y},
					(t_double_point){cast_data->ray_x, cast_data->ray_y},
					cast_data->ray_angle);
			if (!ray->hit || ray->distance < dist)
			{
				ray->x = cast_data->ray_x;
				ray->y = cast_data->ray_y;
				ray->distance = dist;
				ray->hit = true;
			}
			return ;
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
		cast_data->ray_y = (data->player.y / BLOCK_Y * BLOCK_Y) - FOR_PRECISION;
		cast_data->ray_x = (data->player.y - cast_data->ray_y)
			* cast_data->ray_angle_tan + data->player.x;
		cast_data->ray_y_offset = -BLOCK_Y;
		/* This may be incorrent in our case. */
		cast_data->ray_x_offset = -cast_data->ray_y_offset
			* cast_data->ray_angle_tan;
	}
	else if (cast_data->ray_angle > M_PI)
	{
		cast_data->ray_y = (data->player.y / BLOCK_Y * BLOCK_Y) + BLOCK_Y;
		cast_data->ray_x = (data->player.y - cast_data->ray_y)
			* cast_data->ray_angle_tan + data->player.x;
		cast_data->ray_y_offset = BLOCK_Y;
		/* This may be incorrent in our case. */
		cast_data->ray_x_offset = -cast_data->ray_y_offset
			* cast_data->ray_angle_tan;
	}
}

/**
 * Horizontal ray casting.
 * If player looks straight left or straight right,
 * it's impossible for a ray to ever hit horizontal line.
 * Works differently if player looks up or down.
 * @brief	Horizontal ray casting.
 * @param	data	cub3D's data.
 * @param	rays	Out parameter. Where to store the rays information.
 * @param	fov		FOV. Size of \p rays. How many rays to cast.
 * @param	gap		Gap between \p rays.
 */
void	ft_horizontal_ray_cast(struct s_data *data, struct s_ray *rays,
		int fov, double gap)
{
	struct s_ray_cast	cast_data;

	(void)ft_memset(&cast_data, 0, sizeof(struct s_ray_cast));
	if (BLOCK_X < BLOCK_Y)
		cast_data.max_casting_iterations = BLOCK_X;
	else
		cast_data.max_casting_iterations = BLOCK_Y;
	cast_data.ray_angle = data->player_angle.angle - ((fov / 2) * gap);
	while (cast_data.i < fov)
	{
		cast_data.ray_angle_tan = -1 / tan(cast_data.ray_angle);
		if (cast_data.ray_angle == LEFT || cast_data.ray_angle == RIGHT)
		{
			cast_data.ray_angle += gap;
			cast_data.i++;
			continue ;
		}
		ft_horizontal_ray_cast_handle_up_and_down(data, &cast_data);
		ft_ray_cast_until_wall_is_hit(data, rays + cast_data.i, &cast_data);
		cast_data.ray_angle += gap;
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
	if (cast_data->ray_angle > UP && cast_data->ray_angle < DOWN)
	{
		cast_data->ray_x = (data->player.x / BLOCK_X * BLOCK_X) - FOR_PRECISION;
		cast_data->ray_y = (data->player.x - cast_data->ray_x)
			* cast_data->ray_angle_tan + data->player.y;
		cast_data->ray_x_offset = -BLOCK_X;
		/* This may be incorrent in our case. */
		cast_data->ray_y_offset = -cast_data->ray_x_offset
			* cast_data->ray_angle_tan;
	}
	else if (cast_data->ray_angle < UP || cast_data->ray_angle > DOWN)
	{
		cast_data->ray_x = (data->player.x / BLOCK_X * BLOCK_Y) + BLOCK_X;
		cast_data->ray_y = (data->player.x - cast_data->ray_x)
			* cast_data->ray_angle_tan + data->player.y;
		cast_data->ray_x_offset = BLOCK_X;
		/* This may be incorrent in our case. */
		cast_data->ray_y_offset = -cast_data->ray_x_offset
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
 * @param	data	cub3D's data.
 * @param	rays	Out parameter. Where to store the rays information.
 * @param	fov		FOV. Size of \p rays. How many rays to cast.
 * @param	gap		Gap between \p rays.
 */
void	ft_vertical_ray_cast(struct s_data *data, struct s_ray *rays,
		int fov, double gap)
{
	struct s_ray_cast	cast_data;

	(void)ft_memset(&cast_data, 0, sizeof(struct s_ray_cast));
	if (BLOCK_X < BLOCK_Y)
		cast_data.max_casting_iterations = BLOCK_X;
	else
		cast_data.max_casting_iterations = BLOCK_Y;
	cast_data.ray_angle = data->player_angle.angle - ((fov / 2) * gap);
	while (cast_data.i < fov)
	{
		cast_data.ray_angle_tan = -tan(cast_data.ray_angle);
		if (cast_data.ray_angle == UP || cast_data.ray_angle == DOWN)
		{
			cast_data.ray_angle += gap;
			cast_data.i++;
			continue ;
		}
		ft_vertical_ray_cast_handle_left_and_right(data, &cast_data);
		ft_ray_cast_until_wall_is_hit(data, rays + cast_data.i, &cast_data);
		cast_data.ray_angle += gap;
		cast_data.i++;
	}
}
