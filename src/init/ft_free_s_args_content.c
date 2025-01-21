/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_s_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:00 by asagymba          #+#    #+#             */
/*   Updated: 2025/01/21 15:40:37 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <stdlib.h>
#include <stddef.h>
#include <libft.h>

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
