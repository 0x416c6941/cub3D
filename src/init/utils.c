/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:17:33 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 20:06:28 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Useful functions that couldn't be stored
 * in other source files due to Norminette.
 */

#include <init.h>
#include <cub3D.h>
#include <math.h>

/**
 * May be required to access some defines (like M_PI) on older platforms.
 */
#define _USE_MATH_DEFINES

void	ft_calculate_angle_deltas(struct s_data *data)
{
	data->player_angle.delta_x = cos(data->player_angle.angle) * TF_AMP;
	data->player_angle.delta_y = sin(data->player_angle.angle) * TF_AMP;
}
