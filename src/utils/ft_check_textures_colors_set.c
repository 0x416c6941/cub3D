/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_textures_colors_set.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:29:26 by root              #+#    #+#             */
/*   Updated: 2025/01/22 19:30:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <stdbool.h>
#include <stddef.h>
#include <utils.h>

/**
 * @brief Checks if all textures and colors in the `t_args` structure are set.
 *
 * This function verifies that each entry in the `textures` array is non-NULL
 * and each `t_rgb` color in the `colors` array has `setted` set to true.
 *
 * @param args Pointer to the `t_args` structure to check.
 * @return (true if all textures and colors are set); false otherwise.
 */
bool	check_textures_and_colors_set(t_args *args)
{
	int	i;

	i = 0;
	while (i < TEXTURES_SIZE)
	{
		if (args->textures[i] == NULL)
			return (false);
		i++;
	}
	i = 0;
	while (i < COLORS_SIZE)
	{
		if (!args->colors[i].setted)
			return (false);
		i++;
	}
	return (true);
}
