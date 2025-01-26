/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:59:28 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 21:27:58 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <controls.h>
#include <cub3D.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <utils.h>
#include <stdlib.h>
#include <math.h>
#include <init.h>
#include <render.h>

/**
 * Continuation of ft_handle_collision() to bypass Norminette.
 * Handles \p new_y.
 * @param	data	cub3D's data.
 * @param	new_x	Player's new x coordinate.
 * @param	new_y	Player's new y coordinate.
 */
static void	ft_handle_collision_norminette(struct s_data *data,
		int new_x, int new_y)
{
	const int	y_offset = TILE_SIZE / 16;

	if (new_y < data->player.y
		&& (ft_get_map_row(data->map,
				new_y / TILE_SIZE)[data->player.x / TILE_SIZE] == '1'
		|| (new_y % TILE_SIZE < y_offset
			&& ft_get_map_row(data->map, data->player.y / TILE_SIZE - 1)
			[data->player.x / TILE_SIZE] == '1')))
		new_y = data->player.y / TILE_SIZE * TILE_SIZE + y_offset;
	else if (new_y > data->player.y
		&& (ft_get_map_row(data->map,
				new_y / TILE_SIZE)[data->player.x / TILE_SIZE] == '1'
		|| (((TILE_SIZE - 1) - new_y % TILE_SIZE) < y_offset
			&& ft_get_map_row(data->map, data->player.y / TILE_SIZE + 1)
			[data->player.x / TILE_SIZE] == '1')))
		new_y = data->player.y / TILE_SIZE * TILE_SIZE
			+ ((TILE_SIZE - 1) - y_offset);
	data->player.x = new_x;
	data->player.y = new_y;
}

/**
 * Moves the player to new \p new_x and \p new_y, while handling collision.
 * @warning	It's up to you to make sure that \p new_x / TILE_SIZE
 * 			and \p new_y / TILE_SIZE aren't out of bounds of the map.
 * @param	data	cub3D's data.
 * @param	new_x	Player's new x coordinate.
 * @param	new_y	Player's new y coordinate.
 */
static void	ft_handle_collision(struct s_data *data,
		int new_x, int new_y)
{
	const int	x_offset = TILE_SIZE / 16;

	if (new_x < data->player.x
		&& (ft_get_map_row(data->map,
				data->player.y / TILE_SIZE)[new_x / TILE_SIZE] == '1'
		|| (new_x % TILE_SIZE < x_offset
			&& ft_get_map_row(data->map, data->player.y / TILE_SIZE)
			[data->player.x / TILE_SIZE - 1] == '1')))
		new_x = data->player.x / TILE_SIZE * TILE_SIZE + x_offset;
	else if (new_x > data->player.x
		&& (ft_get_map_row(data->map,
				data->player.y / TILE_SIZE)[new_x / TILE_SIZE] == '1'
		|| (((TILE_SIZE - 1) - new_x % TILE_SIZE) < x_offset
			&& ft_get_map_row(data->map, data->player.y / TILE_SIZE)
			[data->player.x / TILE_SIZE + 1] == '1')))
		new_x = data->player.x / TILE_SIZE * TILE_SIZE
			+ ((TILE_SIZE - 1) - x_offset);
	ft_handle_collision_norminette(data, new_x, new_y);
}

/**
 * Moves the player to the side they've pressed (\p keycode).
 * @param	keycode	Code of the pressed key.
 * @param	data	cub3D's data.
 */
static void	ft_handle_movement(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_W || keycode == XKB_KEY_w)
		ft_handle_collision(data,
			data->player.x + round(data->player_angle.delta_x * MOV_EPS),
			data->player.y - round(data->player_angle.delta_y * MOV_EPS));
	else if (keycode == XKB_KEY_A || keycode == XKB_KEY_a)
		ft_handle_collision(data,
			data->player.x - round(data->player_angle.delta_y * MOV_EPS),
			data->player.y - round(data->player_angle.delta_x * MOV_EPS));
	else if (keycode == XKB_KEY_S || keycode == XKB_KEY_s)
		ft_handle_collision(data,
			data->player.x - round(data->player_angle.delta_x * MOV_EPS),
			data->player.y + round(data->player_angle.delta_y * MOV_EPS));
	else if (keycode == XKB_KEY_D || keycode == XKB_KEY_d)
		ft_handle_collision(data,
			data->player.x + round(data->player_angle.delta_y * MOV_EPS),
			data->player.y + round(data->player_angle.delta_x * MOV_EPS));
}

/**
 * Moves the angle the player is looking from at the map
 * depending on the \p keycode.
 * @param	keycode	Code of the pressed key.
 * @param	data	cub3D's data.
 */
static void	ft_handle_angle(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_Left)
		data->player_angle.angle = ft_initialize_angle(data->player_angle.angle
				+ ANGLE_EPS);
	else if (keycode == XKB_KEY_Right)
		data->player_angle.angle = ft_initialize_angle(data->player_angle.angle
				- ANGLE_EPS);
	ft_calculate_angle_deltas(data);
}

int	ft_handle_keysyms(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_Escape)
		(void)ft_mlx_exit(data, EXIT_SUCCESS);
	else if ((keycode == XKB_KEY_W || keycode == XKB_KEY_w)
		|| (keycode == XKB_KEY_A || keycode == XKB_KEY_a)
		|| (keycode == XKB_KEY_S || keycode == XKB_KEY_s)
		|| (keycode == XKB_KEY_D || keycode == XKB_KEY_d))
		ft_handle_movement(keycode, data);
	else if (keycode == XKB_KEY_Left || keycode == XKB_KEY_Right)
		ft_handle_angle(keycode, data);
	else
		return (0);
	(void)ft_render(data);
	return (0);
}
