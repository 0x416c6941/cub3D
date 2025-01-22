/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_t_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:21:16 by root              #+#    #+#             */
/*   Updated: 2025/01/22 20:22:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <utils.h>

/**
 * @brief Prints the contents of the `t_args` structure for debugging.
 *
 * This function iterates over the textures, colors, and map stored in the
 * `t_args` structure and prints their values to the console.
 *
 * @param args Pointer to the `t_args` structure to print (non-NULL).
 */
void	ft_print_t_args(const t_args *args)
{
	int		i;
	t_list	*current;

	if (!args)
	{
		ft_printf("t_args is NULL\n");
		return ;
	}
	// Print textures
	ft_printf("Textures:\n");
	for (i = 0; i < TEXTURES_SIZE; i++)
	{
		ft_printf("  [%d]: %s\n", i,
			args->textures[i] ? args->textures[i] : "(null)");
	}
	// Print colors
	ft_printf("Colors:\n");
	for (i = 0; i < COLORS_SIZE; i++)
	{
		ft_printf("  [%d]: R=%d, G=%d, B=%d, Set=%s\n", i, args->colors[i].r,
			args->colors[i].g, args->colors[i].b,
			args->colors[i].setted ? "true" : "false");
	}
	// Print map
	ft_printf("Map:\n");
	current = args->map;
	if (!current)
	{
		ft_printf("  (empty map)\n");
	}
	while (current)
	{
		ft_printf("  %s\n", (char *)current->content);
		current = current->next;
	}
}
