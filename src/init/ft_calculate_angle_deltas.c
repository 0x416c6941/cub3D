/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_angle_deltas.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:17:33 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 16:18:37 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <cub3D.h>
#include <math.h>

void	ft_calculate_angle_deltas(struct s_data *data)
{
	data->player_angle.delta_x = cos(data->player_angle.angle) * TF_AMP;
	data->player_angle.delta_y = sin(data->player_angle.angle) * TF_AMP;
}
