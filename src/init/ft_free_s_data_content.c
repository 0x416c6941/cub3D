/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_s_data_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:55:03 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/22 14:03:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <cub3D.h>
#include <stddef.h>
#include <mlx.h>
#include <stdlib.h>

void	ft_free_s_data_content(struct s_data *to_free)
{
	int	i;

	if (to_free->win != NULL)
	{
		mlx_destroy_window(to_free->conn, to_free->win);
		to_free->win = NULL;
	}
	i = 0;
	while (i < TEXTURES_SIZE)
	{
		if (to_free->textures[i] != NULL)
		{
			mlx_destroy_image(to_free->conn, to_free->textures[i]);
			to_free->textures[i] = NULL;
		}
		i++;
	}
	if (to_free->conn != NULL)
	{
		mlx_destroy_display(to_free->conn);
		free(to_free->conn);
		to_free->conn = NULL;
	}
}
