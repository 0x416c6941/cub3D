/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyshchu <hlyshchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:37:34 by root              #+#    #+#             */
/*   Updated: 2025/01/24 18:43:36 by hlyshchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <parse.h>

/**
 * @brief Counts the number of player starting positions in a map.
 *
 * This function iterates through a linked list (`t_list`) of strings 
 * representing the map. It counts the occurrences of characters 'N', 'S', 'E', 
 * and 'W', which denote valid player starting positions.
 * 
 * @param map A pointer to the head of the linked list of strings representing
 * the map.
 * @return int Returns the total count of player starting positions in the map.
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
		while (line[i] != '\0')
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
