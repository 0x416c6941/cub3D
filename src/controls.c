/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:59:28 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 15:05:35 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <controls.h>
#include <cub3D.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <utils.h>

int	ft_handle_keysyms(int keycode, struct s_data *data)
{
	if (keycode == XKB_KEY_Escape)
		(void)ft_mlx_exit(data);
	return (0);
}
