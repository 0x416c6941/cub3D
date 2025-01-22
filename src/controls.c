/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:59:28 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 16:40:02 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <controls.h>
#include <cub3D.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <utils.h>
#include <math.h>
#include <init.h>

/**
 * Moves the player to the side they've pressed (\p keycode).
 * @param	keycode	Code of the pressed key.
 * @param	data	cub3D's data.
 */
static void	ft_handle_movement(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_W || keycode == XKB_KEY_w)
	{
		data->player.x += round(data->player_angle.delta_x * MOV_EPS);
		data->player.y -= round(data->player_angle.delta_y * MOV_EPS);
	}
	else if (keycode == XKB_KEY_A || keycode == XKB_KEY_a)
	{
		data->player.x -= round(data->player_angle.delta_y * MOV_EPS);
		data->player.y -= round(data->player_angle.delta_x * MOV_EPS);
	}
	else if (keycode == XKB_KEY_S || keycode == XKB_KEY_s)
	{
		data->player.x -= round(data->player_angle.delta_x * MOV_EPS);
		data->player.y += round(data->player_angle.delta_y * MOV_EPS);
	}
	else if (keycode == XKB_KEY_D || keycode == XKB_KEY_d)
	{
		data->player.x += round(data->player_angle.delta_y * MOV_EPS);
		data->player.y += round(data->player_angle.delta_x * MOV_EPS);
	}
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
	{
		data->player_angle.angle += ANGLE_EPS;
		if (data->player_angle.angle > 2 * M_PI)
			data->player_angle.angle -= 2 * M_PI;
	}
	else if (keycode == XKB_KEY_Right)
	{
		data->player_angle.angle -= ANGLE_EPS;
		if (data->player_angle.angle < 0)
			data->player_angle.angle += 2 * M_PI;
	}
	ft_calculate_angle_deltas(data);
}

int	ft_handle_keysyms(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_Escape)
		(void)ft_mlx_exit(data);
	else if ((keycode == XKB_KEY_W || keycode == XKB_KEY_w)
		|| (keycode == XKB_KEY_A || keycode == XKB_KEY_a)
		|| (keycode == XKB_KEY_S || keycode == XKB_KEY_s)
		|| (keycode == XKB_KEY_D || keycode == XKB_KEY_d))
		ft_handle_movement(keycode, data);
	else if (keycode == XKB_KEY_Left || keycode == XKB_KEY_Right)
		ft_handle_angle(keycode, data);
	return (0);
}
