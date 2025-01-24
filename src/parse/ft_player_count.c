/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:37:34 by root              #+#    #+#             */
/*   Updated: 2025/01/24 01:14:49 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>

/**
 * Return the number of player characters in the map.
 * Ensures that the map contains exactly one player character
 * (characters 'N', 'S', 'E' or 'W').
 * @warning	It's your responsibility to make sure \p map isn't NULL.
 * @param	map	Pointer to the head of the map linked list.
 * @return	Number of player characters.
 */
int	ft_player_count(t_list *map)
{
	t_list	*current;
	char	*line;
	int		player_count;
	int		i;

	player_count = 0;
	current = map;
	while (current != NULL)
	{
		line = (char *)current->content;
		i = 0;
		while (line[i] != NULL)
		{
			if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
				player_count++;
			i++;
		}
		current = current->next;
	}
	return (player_count);
}
