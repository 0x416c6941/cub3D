/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:00 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/26 02:54:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * "Destructors" are stored here.
 */

#include <init.h>
#include <cub3D.h>
#include <stdlib.h>
#include <stddef.h>
#include <libft.h>
#include <mlx.h>

void	ft_free_s_args_content(struct s_args *to_free)
{
	int	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		free(to_free->textures[i]);
		to_free->textures[i++] = NULL;
	}
	ft_lstclear(&to_free->map, free);
}

/**
 * Yep, you got it right, it's a continuation of ft_free_s_data_content()
 * to bypass Norminette!
 * @param	to_free	cub3D's data to free().
 */
static void	ft_free_s_data_content_norminette(struct s_data *to_free)
{
	if (to_free->conn != NULL)
	{
		mlx_destroy_display(to_free->conn);
		free(to_free->conn);
		to_free->conn = NULL;
	}
	ft_lstclear(&to_free->map, free);
}

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
		if (to_free->textures[i].img != NULL)
		{
			mlx_destroy_image(to_free->conn, to_free->textures[i].img);
			to_free->textures[i].img = NULL;
			to_free->textures[i].img_pixels = NULL;
		}
		i++;
	}
	if (to_free->buffer.img != NULL)
	{
		mlx_destroy_image(to_free->conn, to_free->buffer.img);
		to_free->buffer.img = NULL;
		to_free->buffer.img_pixels = NULL;
	}
	ft_free_s_data_content_norminette(to_free);
}
